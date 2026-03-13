/**
 * @file openbigdata.cpp
 * @brief BCI Dataset Augmentation Tool -- Open Data #349
 *
 * Full pipeline program covering all spec requirements:
 *
 *   DATA PREPARATION
 *     2) Unify Thoughts       -- rename files to <category>_<group>_<person>_<n>.ext
 *     3) Remove 8-Channel Data -- strip last 8 CSV columns
 *     4) Run File Shuffler    -- shuffle data rows in every CSV
 *
 *   DATA GENERATION
 *     5) Generate Augmented Data -- replicate files evenly across 6 categories
 *                                  until dataset grows by +60%, then move clones
 *                                  to their category directories and print report
 *
 *   CLEANUP
 *     6) Cleanup -- create access_data.txt and remove brainwave files
 *
 * Real folder structure:
 *   Data_clean/
 *     G01/ G03/ G04/            <- semesters
 *       person01/ … person10/   <- participants
 *         forward/ backward/    <- 6 thought categories
 *         left/    right/
 *         landing/ takeoff/
 *           *.csv  *.txt        <- EEG data files
 *
 * IMPORTANT: Brain-wave files must NOT be published online or shared without
 *            going through proper protocols and authorization first.
 *
 * Build:
 *   g++ -std=c++17 -pthread -O2 -o openbigdata openbigdata.cpp
 *
 * Usage:
 *   ./openbigdata
 *
 * @author  Group 2
 * @date    Feburary 25, 2026
 */

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#ifndef _WIN32
#include <sys/time.h>
#else
#include <windows.h>  // SetFileTime(), FILETIME, CreateFileW
#endif

/**
 * @brief Filesystem support with C++17 std::filesystem if available, otherwise
 *       fallback to std::experimental::filesystem.
 *       If neither is available, compilation will fail with an error.
 *      Note: C++14 does not have std::filesystem, but some compilers may provide
 *      std::experimental::filesystem as an extension.  We check for both and
 *     use whichever is available, but require C++17 for guaranteed support.
 *
 */
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "No filesystem header found. Compile with -std=c++17."
#endif

/**
 * @brief  Canonical category names used in the dataset and throughout the program.
 *       These are the 6 thought categories we expect to find in the dataset, and       the only valid categories for file naming and augmentation.
 *
 */
const std::vector<std::string> CATEGORIES = {
    "forward", "backward", "left", "right", "landing", "takeoff"};

/**
 * @brief  Augmentation target -- stop once dataset has grown by this fraction.
 *         This value is set to 60% as per spec requirement.
 *
 */
constexpr double AUGMENT_RATIO = 0.60;

/** Log a checkpoint every this many new files per category. */
constexpr int CHECKPOINT = 50;

/** Temporary subdirectory name used to stage clones before moving. */
const std::string CLONE_SUBDIR = "augmented_temp";

/** access_data.txt message required by the spec. */
const std::string ACCESS_MSG =
    "GITHUB DOES NOT ALLOW UPLOADING BIG DATA OR LARGE FILES. "
    "TO ACCESS OUR OPEN DATABUCKET THROUGH DELTA LAKE, PLEASE CONTACT US. "
    "SOURCE: GitHub [GitHub Free and Pro: Up to 2 GB] "
    "https://docs.github.com/en/repositories/working-with-files/"
    "managing-large-files/about-large-files-on-github\n";

// ---------------------------------------------------------------------------
// Helper functions
// ---------------------------------------------------------------------------
/**
 * @brief Converts a string to lowercase.
 * takes a copy of the input string, transforms it to lowercase, and returns the new string.
 * @param s  Input string.
 * @return   Lowercase copy.
 */
static std::string toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return s;
}

/**
 * @brief Returns the total size (bytes) of all regular files under @p root.
 *   Walks the directory tree recursively and sums the sizes of all regular files.
      Note: This function does not follow symbolic links to avoid cycles.
 * @param root  Directory to measure recursively.
 * @return      Total size in bytes.
 */
static uintmax_t directorySize(const fs::path &root)
{
    uintmax_t total = 0;
    for (const auto &e : fs::recursive_directory_iterator(root))
        if (e.is_regular_file())
            total += e.file_size();
    return total;
}

/**
 * @brief Formats a byte count as a human-readable string.
 * @param bytes  Raw byte count.
 * @return       Formatted string, e.g. "2.20 GB".
 */
static std::string formatSize(uintmax_t bytes)
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    if (bytes >= 1'000'000'000ULL)
        ss << bytes / 1e9 << " GB";
    else if (bytes >= 1'000'000ULL)
        ss << bytes / 1e6 << " MB";
    else if (bytes >= 1'000ULL)
        ss << bytes / 1e3 << " KB";
    else
        ss << bytes << " B";
    return ss.str();
}

/**
 * @brief Maps a messy folder name to one of the 6 canonical category names.
 *
 * Handles real-world inconsistencies in the dataset such as:
 *   "Foreward", "Fowward", "OpenBCISession_forward_2" -> "forward"
 *   "B ackward", "backard"                            -> "backward"
 *   "TakOff", "take off", "TakOff__3"                -> "takeoff"
 *
 * @param folderName  Raw folder name from the filesystem.
 * @return            Canonical category string, or "" if unrecognized.
 */
static std::string normalizeCategory(const std::string &folderName)
{
    std::string low = toLower(folderName);
    low.erase(std::remove(low.begin(), low.end(), ' '), low.end());

    if (low.find("forward") != std::string::npos ||
        low.find("foreward") != std::string::npos ||
        low.find("fowward") != std::string::npos)
        return "forward";

    if (low.find("backward") != std::string::npos ||
        low.find("backard") != std::string::npos)
        return "backward";

    if (low.find("left") != std::string::npos)
        return "left";
    if (low.find("right") != std::string::npos)
        return "right";
    if (low.find("landing") != std::string::npos)
        return "landing";

    if (low.find("takeoff") != std::string::npos ||
        low.find("takoff") != std::string::npos ||
        low.find("takof") != std::string::npos)
        return "takeoff";

    return "";
}

/**
 * @brief Sets the last-write timestamp of a file to January 1, Year 3001.
 *
 * Cross-platform implementation:
 *  - Windows    : uses SetFileTime() with FILETIME (100-ns ticks since
 *                 1601-01-01), which supports dates well past year 2262.
 *  - macOS/Linux: uses utimes() (POSIX); time_t is 64-bit on all modern
 *                 64-bit systems so 32 503 680 000 fits without overflow.
 *
 * Falls back to prefixing the filename with "3001_" if the OS call fails.
 *
 * @param p  Path to the file to update.
 */
static void setTimestamp3001(const fs::path &p)
{
#ifdef _WIN32
    // -------------------------------------------------------------------
    // Windows: FILETIME counts 100-nanosecond intervals since 1601-01-01.
    // -------------------------------------------------------------------
    // 100-ns ticks from 1601-01-01 to 1970-01-01 (Unix epoch offset).
    constexpr unsigned long long EPOCH_DIFF = 116444736000000000ULL;
    // Seconds from Unix epoch to 3001-01-01: 32 503 680 000 s.
    // Convert to 100-ns ticks and add the 1601 epoch offset.
    constexpr unsigned long long TARGET_100NS =
        32503680000ULL * 10000000ULL + EPOCH_DIFF;

    FILETIME ft;
    ft.dwLowDateTime  = static_cast<DWORD>(TARGET_100NS & 0xFFFFFFFFULL);
    ft.dwHighDateTime = static_cast<DWORD>(TARGET_100NS >> 32);

    HANDLE hFile = CreateFileW(
        p.wstring().c_str(),
        FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        nullptr);

    if (hFile == INVALID_HANDLE_VALUE || !SetFileTime(hFile, &ft, &ft, &ft))
    {
        if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
        std::error_code ec;
        fs::path renamed = p.parent_path() / ("3001_" + p.filename().string());
        fs::rename(p, renamed, ec);
        return;
    }
    CloseHandle(hFile);

#else
    // -------------------------------------------------------------------
    // macOS / Linux: utimes() -- time_t is 64-bit on 64-bit POSIX systems.
    // -------------------------------------------------------------------
    constexpr long long TARGET_SEC = 32503680000LL; // 3001-01-01 UTC

    struct timeval times[2];
    times[0].tv_sec  = static_cast<time_t>(TARGET_SEC);
    times[0].tv_usec = 0;
    times[1].tv_sec  = static_cast<time_t>(TARGET_SEC);
    times[1].tv_usec = 0;

    if (utimes(p.c_str(), times) != 0)
    {
        std::error_code ec;
        fs::path renamed = p.parent_path() / ("3001_" + p.filename().string());
        fs::rename(p, renamed, ec);
    }
#endif
}

// ---------------------------------------------------------------------------
// DataSanitizer
// ---------------------------------------------------------------------------

/**
 * @class DataSanitizer
 * @brief Sanitizes brain-wave EEG data across the 3-level folder hierarchy.
 *
 * Walks: root -> group (G01/G03/G04) -> person (person01..10)
 *             -> category folder     -> files
 *
 * Methods map to menu options:
 *   unifyThoughts()      -> option 2
 *   remove8ChannelData() -> option 3
 *   runFileShuffler()    -> option 4
 */
class DataSanitizer
{
public:
    /**
     * @brief Constructs a DataSanitizer for the given dataset root.
     * @param dataRoot  Path to Data_clean (top-level folder).
     */
    explicit DataSanitizer(const fs::path &dataRoot)
        : m_root(dataRoot), m_processedCount(0) {}

    /**
     * @brief Step 1 -- Unify Thoughts.
     *
     * Renames every file to <category>_<group>_<person>_<index><ext>
     * so no filename can be traced back to a recording session or subject.
     *
     * @return  Summary string for the terminal log.
     */
    std::string unifyThoughts()
    {
        int renamed = 0, skipped = 0;

        // Walk the directory tree with nested loops for group -> person -> category.
        for (const auto &groupEntry : fs::directory_iterator(m_root))
        {
            if (!groupEntry.is_directory())
                continue;
            std::string groupName = groupEntry.path().filename().string();

            for (const auto &personEntry : fs::directory_iterator(groupEntry.path()))
            {
                if (!personEntry.is_directory())
                    continue;
                std::string personName = personEntry.path().filename().string();

                std::vector<fs::path> catDirs;
                collectCategoryDirs(personEntry.path(), catDirs);

                for (const fs::path &catDir : catDirs)
                {
                    std::string category = normalizeCategory(
                        catDir.filename().string());
                    if (category.empty())
                    {
                        ++skipped;
                        continue;
                    }

                    int idx = 0;
                    for (const auto &f : fs::directory_iterator(catDir))
                    {
                        if (!f.is_regular_file())
                            continue;
                        std::string newName = category + "_" + groupName + "_" + personName + "_" + std::to_string(idx++) + f.path().extension().string();
                        fs::path newPath = catDir / newName;
                        if (f.path().filename() != newName)
                            fs::rename(f.path(), newPath);

                        std::lock_guard<std::mutex> lock(m_mutex);
                        ++m_processedCount;
                        ++renamed;
                    }
                }
            }
        }
        return "Unify Thoughts complete -- " + std::to_string(renamed) + " file(s) renamed, " + std::to_string(skipped) + " unrecognized folder(s) skipped.";
    }

    std::string remove8ChannelData()
    {
        // EXG Channel columns to REMOVE (columns 1-8, zero-indexed).
        //
        // CSV layout (TAB-delimited, no header, 24 columns):
        //   Col 0 : Sample Index          <- KEEP
        //   Col 1 : EXG Channel 0         <- REMOVE
        //   Col 2 : EXG Channel 1         <- REMOVE
        //   Col 3 : EXG Channel 2         <- REMOVE
        //   Col 4 : EXG Channel 3         <- REMOVE
        //   Col 5 : EXG Channel 4         <- REMOVE
        //   Col 6 : EXG Channel 5         <- REMOVE
        //   Col 7 : EXG Channel 6         <- REMOVE
        //   Col 8 : EXG Channel 7         <- REMOVE
        //   Col 9+: Accel, Digital, etc.  <- KEEP
        //
        // TXT layout (comma-delimited, % comment lines at top, then header row):
        //   Same column positions -- remove cols 1-8 from data rows only.
        //   Comment lines (%) and the header row are preserved unchanged.
        const std::set<int> DROP_COLS = {1, 2, 3, 4, 5, 6, 7, 8};
        constexpr int MIN_COLS = 9; // Must have at least 9 cols to safely drop 1-8.

        int filesEdited  = 0;
        int filesSkipped = 0;
        int filesError   = 0;

        for (const auto& entry : fs::recursive_directory_iterator(m_root))
        {
            if (!entry.is_regular_file()) continue;

            const std::string ext = toLower(entry.path().extension().string());
            if (ext != ".csv" && ext != ".txt") continue;

            // CSV = TAB-delimited, no header.
            // TXT = comma-delimited, has % comment lines + one header row.
            const bool isCsv  = (ext == ".csv");
            const char DELIM  = isCsv ? '\t' : ',';

            std::ifstream in(entry.path());
            if (!in.is_open()) { ++filesError; continue; }

            std::vector<std::string> lines;
            std::string line;
            while (std::getline(in, line))
            {
                // Strip Windows carriage return if present.
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();
                lines.push_back(line);
            }
            in.close();

            if (lines.empty()) continue;

            // ---------------------------------------------------------------
            // Safety check: find the first real data row and count its columns.
            // For TXT files, skip % comment lines and the header row.
            // ---------------------------------------------------------------
            bool safeToProcess = false;
            for (const auto& l : lines)
            {
                if (l.empty()) continue;
                if (!isCsv && l[0] == '%') continue;  // TXT comment line.
                // TXT header row starts with "Sample Index" (alphabetic).
                if (!isCsv && std::isalpha(static_cast<unsigned char>(l[0]))) continue;

                // Count columns in this data row.
                int cols = 1;
                if (isCsv)
                {
                    // TAB-delimited: count tabs.
                    cols = static_cast<int>(
                        std::count(l.begin(), l.end(), '\t') + 1);
                }
                else
                {
                    // Comma-delimited: count commas.
                    cols = static_cast<int>(
                        std::count(l.begin(), l.end(), ',') + 1);
                }

                if (cols >= MIN_COLS) { safeToProcess = true; break; }
            }

            if (!safeToProcess)
            {
                std::cout << "    [SKIP] " << entry.path().filename().string()
                          << " -- fewer than " << MIN_COLS
                          << " data columns found, file unchanged.\n";
                ++filesSkipped;
                continue;
            }

            // ---------------------------------------------------------------
            // Build output: remove EXG columns from data rows only.
            // ---------------------------------------------------------------
            std::vector<std::string> outLines;
            bool headerSeen = false; // Used for TXT to track if header passed.

            for (const auto& l : lines)
            {
                // Empty lines pass through unchanged.
                if (l.empty()) { outLines.push_back(l); continue; }

                // TXT: preserve % comment lines unchanged.
                if (!isCsv && l[0] == '%')
                {
                    outLines.push_back(l);
                    continue;
                }

                // TXT: preserve the header row (first non-comment line) unchanged.
                if (!isCsv && !headerSeen &&
                    std::isalpha(static_cast<unsigned char>(l[0])))
                {
                    outLines.push_back(l);
                    headerSeen = true;
                    continue;
                }

                // Data row -- split by the correct delimiter and drop cols 1-8.
                std::vector<std::string> tokens;
                std::istringstream ss(l);
                std::string tok;
                while (std::getline(ss, tok, DELIM))
                    tokens.push_back(tok);

                std::string outLine;
                for (int i = 0; i < static_cast<int>(tokens.size()); ++i)
                {
                    if (DROP_COLS.count(i)) continue; // Drop EXG columns 1-8.
                    if (!outLine.empty()) outLine += DELIM;
                    outLine += tokens[i];
                }
                outLines.push_back(outLine);
            }

            // ---------------------------------------------------------------
            // Write to a temp file first -- never truncate the original until
            // the write is confirmed to have content.
            // ---------------------------------------------------------------
            fs::path tmpPath = entry.path().string() + ".tmp";
            {
                std::ofstream out(tmpPath);
                if (!out.is_open()) { ++filesError; continue; }
                for (const auto& l : outLines) out << l << '\n';
            }

            if (!fs::exists(tmpPath) || fs::file_size(tmpPath) == 0)
            {
                fs::remove(tmpPath);
                std::cerr << "    [ERROR] Temp file empty, original preserved: "
                          << entry.path().filename().string() << "\n";
                ++filesError;
                continue;
            }

            fs::rename(tmpPath, entry.path());
            ++filesEdited;

            if (filesEdited % 50 == 0)
                std::cout << "    Progress: " << filesEdited << " file(s) processed...\n";
        }

        std::ostringstream result;
        result << "Remove 8-Channel Data complete -- "
               << filesEdited << " file(s) trimmed (EXG cols 1-8 removed), "
               << filesSkipped << " skipped, "
               << filesError << " error(s).";
        return result.str();
    }
    /**
     * @brief Step 3 -- Run File Shuffler.
     *
     * Randomly permutes data rows (excluding the header) in every CSV to
     * break temporal ordering that could re-link records to a participant.
     *
     * @return  Summary string for the terminal log.
     */
    std::string runFileShuffler()
    {
        std::mt19937 rng(std::random_device{}());
        int filesShuffled = 0;

        for (const auto &entry : fs::recursive_directory_iterator(m_root))
        {
            if (!entry.is_regular_file())
                continue;
            const std::string ext = toLower(entry.path().extension().string());
            if (ext != ".csv" && ext != ".txt")
                continue;

            std::ifstream in(entry.path());
            if (!in.is_open())
                continue;

            std::vector<std::string> lines;
            std::string line;
            while (std::getline(in, line))
            {
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();
                lines.push_back(line);
            }
            in.close();

            // Find the first real data row to shuffle from.
            // CSV (TAB-delimited): no header -- shuffle all rows from index 0.
            // TXT (comma-delimited): has % comment lines then a header row --
            //   preserve those and shuffle only the data rows after them.
            size_t dataStart = 0;
            if (ext == ".txt")
            {
                for (size_t i = 0; i < lines.size(); ++i)
                {
                    if (!lines[i].empty() && lines[i][0] == '%') continue;
                    // First non-comment line is the header -- data starts after.
                    dataStart = i + 1;
                    break;
                }
            }

            // Need at least 2 data rows to be worth shuffling.
            if (lines.size() <= dataStart + 1)
                continue;

            std::shuffle(lines.begin() + dataStart + 1, lines.end(), rng);

            // Write to temp file first -- never truncate original until safe.
            fs::path tmpPath = entry.path();
            tmpPath += ".tmp";

            {
                std::ofstream out(tmpPath);
                if (!out.is_open())
                    continue;
                for (const auto &l : lines)
                    out << l << '\n';
            }

            // Only replace if temp file has content.
            if (fs::file_size(tmpPath) == 0)
            {
                fs::remove(tmpPath);
                continue;
            }

            fs::rename(tmpPath, entry.path());

            std::lock_guard<std::mutex> lock(m_mutex);
            ++filesShuffled;
        }
        return "Run File Shuffler complete -- " + std::to_string(filesShuffled) + " CSV file(s) shuffled.";
    }

    /**
     * @brief Finds all category-level directories under a person folder.
     *
     * Handles two layouts:
     *   person01/forward/          (direct)
     *   person01/SessionName/forward/  (intermediate session folder)
     *
     * @param personDir  Path to a single person folder.
     * @param result     Vector to append found category-level paths into.
     */
    void collectCategoryDirs(const fs::path &personDir,
                             std::vector<fs::path> &result)
    {
        for (const auto &entry : fs::directory_iterator(personDir))
        {
            if (!entry.is_directory())
                continue;
            std::string cat = normalizeCategory(entry.path().filename().string());

            if (!cat.empty())
            {
                result.push_back(entry.path());
            }
            else
            {
                // Could be an intermediate session folder -- go one level deeper.
                for (const auto &inner : fs::directory_iterator(entry.path()))
                {
                    if (!inner.is_directory())
                        continue;
                    if (!normalizeCategory(inner.path().filename().string()).empty())
                        result.push_back(inner.path());
                }
            }
        }
    }

private:
    fs::path m_root;
    std::mutex m_mutex;
    int m_processedCount; ///< Running total of files touched.
};

// ---------------------------------------------------------------------------
// DataAugmenter
// ---------------------------------------------------------------------------

/**
 * @class DataAugmenter
 * @brief Replicates files per participant per category until dataset hits +60%.
 *
 * Algorithm:
 *  For each participant, for each of the 6 categories (in order):
 *    - Count files currently in that participant's category folder.
 *    - Add 60% more files (rounded up), copying from that same folder.
 *    - Each source file is used only once per round; reset when exhausted.
 *    - Log progress every CHECKPOINT total new files.
 *    - If +60% total size reached, finish ALL remaining categories for
 *      the current participant so counts stay even, then stop.
 *  After all copying: set timestamps to 3001-01-01, print final report.
 */
class DataAugmenter
{
public:
    /**
     * @brief Constructs a DataAugmenter.
     * @param dataRoot     Path to Data_clean.
     * @param originalSize Dataset size in bytes before augmentation.
     */
    DataAugmenter(const fs::path& dataRoot, uintmax_t originalSize)
        : m_root(dataRoot)
        , m_originalSize(originalSize)
        , m_targetIncrease(static_cast<uintmax_t>(originalSize * AUGMENT_RATIO))
        , m_totalNewBytes(0)
        , m_totalNewFiles(0)
        , m_totalOrigFiles(0)
    {}

    /**
     * @brief Runs the full augmentation pipeline and prints the final report.
     */
    void run()
    {
        std::cout << "\n  Original size   : " << formatSize(m_originalSize) << "\n";
        std::cout << "  Target increase : " << formatSize(m_targetIncrease) << "\n\n";

        augment();
        setAllTimestamps();
        printReport();
    }

private:
    fs::path  m_root;
    uintmax_t m_originalSize;
    uintmax_t m_targetIncrease;
    uintmax_t m_totalNewBytes;   ///< Bytes added across all categories.
    int       m_totalNewFiles;   ///< Files added across all categories.
    int       m_totalOrigFiles;  ///< Original file count before augmentation.

    /// Per canonical category: total new files added (for final report).
    std::map<std::string, int> m_newFilesPerCat;

    // -----------------------------------------------------------------------
    // Core augmentation loop
    // -----------------------------------------------------------------------

    /**
     * @brief Main loop: per participant, per category, add ~60% more files.
     *
     * Walks group -> participant -> category (in sorted order).
     * For each category folder:
     *   1. Collect ONLY original source files (exclude aug_ clones already staged).
     *   2. toAdd = ceil(origCount * 0.60).
     *   3. Copy into catDir/augmented_temp/ -- each source used once per round;
     *      reset + reshuffle when pool is exhausted.
     *   4. Log progress every CHECKPOINT total new files.
     *   5. After each category: if +60% byte threshold hit, finish all remaining
     *      categories for this participant (so counts stay even), then stop.
     *
     * When +60% is reached (or all participants done):
     *   Move every staged clone from augmented_temp/ into its parent catDir.
     */
    void augment()
    {
        std::mt19937 rng(std::random_device{}());
        bool thresholdReached = false;

        // Count original files before any augmentation so the report is accurate.
        for (const auto& entry : fs::recursive_directory_iterator(m_root))
            if (entry.is_regular_file()) ++m_totalOrigFiles;
        std::cout << "  Original file count : " << m_totalOrigFiles << "\n\n";

        DataSanitizer helper{m_root};

        // Collect and sort groups.
        std::vector<fs::path> groups;
        for (const auto& g : fs::directory_iterator(m_root))
            if (g.is_directory()) groups.push_back(g.path());
        std::sort(groups.begin(), groups.end());

        for (const fs::path& groupDir : groups)
        {
            std::vector<fs::path> persons;
            for (const auto& p : fs::directory_iterator(groupDir))
                if (p.is_directory()) persons.push_back(p.path());
            std::sort(persons.begin(), persons.end());

            for (const fs::path& personDir : persons)
            {
                std::vector<fs::path> catDirs;
                helper.collectCategoryDirs(personDir, catDirs);

                // Sort by canonical category order.
                std::sort(catDirs.begin(), catDirs.end(),
                    [](const fs::path& a, const fs::path& b)
                    {
                        auto idxOf = [](const fs::path& p) -> int {
                            std::string cat = normalizeCategory(p.filename().string());
                            for (int i = 0; i < (int)CATEGORIES.size(); ++i)
                                if (CATEGORIES[i] == cat) return i;
                            return 999;
                        };
                        return idxOf(a) < idxOf(b);
                    });

                for (const fs::path& catDir : catDirs)
                {
                    std::string cat = normalizeCategory(catDir.filename().string());
                    if (cat.empty()) continue;

                    // Stage clones in a subdirectory so originals are never
                    // mixed with copies until the threshold is confirmed.
                    fs::path stageDir = catDir / CLONE_SUBDIR;
                    fs::create_directories(stageDir);

                    // Collect ONLY original source files (not aug_ clones).
                    std::vector<fs::path> sources;
                    for (const auto& f : fs::directory_iterator(catDir))
                    {
                        if (!f.is_regular_file()) continue;
                        // Skip the staging subdirectory itself and any
                        // previously staged clones (names start with "aug_").
                        std::string fname = f.path().filename().string();
                        if (fname.substr(0, 4) == "aug_") continue;
                        sources.push_back(f.path());
                    }

                    if (sources.empty()) continue;

                    int origCount = static_cast<int>(sources.size());
                    int toAdd     = static_cast<int>(std::ceil(origCount * 0.60));

                    std::cout << "  " << personDir.filename().string()
                              << "/" << cat
                              << " : " << origCount << " files -> adding "
                              << toAdd << " (staged in " << CLONE_SUBDIR << ")\n";

                    // Copy toAdd files -- each source used only once per round.
                    std::vector<fs::path> pool = sources;
                    std::shuffle(pool.begin(), pool.end(), rng);
                    std::set<std::string> usedThisRound;
                    int poolIdx = 0;

                    for (int i = 0; i < toAdd; ++i)
                    {
                        // Reset round when all sources have been used once.
                        if (usedThisRound.size() >= pool.size())
                        {
                            usedThisRound.clear();
                            std::shuffle(pool.begin(), pool.end(), rng);
                            poolIdx = 0;
                        }

                        // Advance to next unused source.
                        while (usedThisRound.count(
                                pool[poolIdx].filename().string()))
                            poolIdx = (poolIdx + 1) % (int)pool.size();

                        const fs::path& src = pool[poolIdx];
                        usedThisRound.insert(src.filename().string());

                        // Name the clone uniquely inside the staging dir.
                        std::string destName = "aug_" + cat
                            + "_" + std::to_string(m_totalNewFiles + i)
                            + src.extension().string();
                        fs::path dest = stageDir / destName;

                        int col = 0;
                        while (fs::exists(dest))
                            dest = stageDir / ("aug_" + cat + "_"
                                + std::to_string(m_totalNewFiles + i)
                                + "_v" + std::to_string(++col)
                                + src.extension().string());

                        try
                        {
                            fs::copy_file(src, dest,
                                fs::copy_options::overwrite_existing);
                        }
                        catch (const std::exception& ex)
                        {
                            std::cerr << "    [ERROR] copy failed: "
                                      << ex.what() << "\n";
                            continue;
                        }

                        m_totalNewBytes += fs::file_size(dest);
                        m_newFilesPerCat[cat]++;
                    }

                    m_totalNewFiles += toAdd;

                    // Log every CHECKPOINT total new files.
                    if ((m_totalNewFiles / CHECKPOINT) >
                        ((m_totalNewFiles - toAdd) / CHECKPOINT))
                    {
                        std::cout << "  [Progress] " << m_totalNewFiles
                                  << " staged | "
                                  << formatSize(m_totalNewBytes)
                                  << " added so far\n";
                    }

                    // Check threshold after finishing this category.
                    if (m_totalNewBytes >= m_targetIncrease && !thresholdReached)
                    {
                        thresholdReached = true;
                        std::cout << "\n  [+60% reached] Finishing remaining "
                                     "categories for current participant...\n";
                    }
                }

                // Finished all categories for this participant.
                // If threshold reached, stop walking further participants.
                if (thresholdReached) goto done;
            }
        }

        done:
        // Move all staged clones from augmented_temp/ into their category dirs.
        std::cout << "\n  Moving staged clones to category directories...\n";
        int moved = 0;
        for (const auto& entry : fs::recursive_directory_iterator(m_root))
        {
            if (!entry.is_directory()) continue;
            if (entry.path().filename().string() != CLONE_SUBDIR) continue;

            fs::path catDir = entry.path().parent_path();
            for (const auto& clone : fs::directory_iterator(entry.path()))
            {
                if (!clone.is_regular_file()) continue;
                fs::path dest = catDir / clone.path().filename();

                // Resolve name collisions.
                int col = 0;
                while (fs::exists(dest))
                    dest = catDir / (clone.path().stem().string()
                        + "_v" + std::to_string(++col)
                        + clone.path().extension().string());

                try
                {
                    fs::rename(clone.path(), dest);
                    ++moved;
                }
                catch (const std::exception& ex)
                {
                    std::cerr << "    [ERROR] move failed: " << ex.what() << "\n";
                }
            }
            // Remove the now-empty staging subdirectory.
            std::error_code ec;
            fs::remove(entry.path(), ec);
        }
        std::cout << "  " << moved << " clone(s) moved to category directories.\n";
        std::cout << "\n  Augmentation complete.\n";
    }

    // -----------------------------------------------------------------------
    // Post-augmentation helpers
    // -----------------------------------------------------------------------

    /**
     * @brief Sets the last-write timestamp of every file to January 1, 3001.
     */
    void setAllTimestamps()
    {
        std::cout << "\n  Setting all file timestamps to 3001-01-01...\n";
        int count = 0;
        for (const auto& entry : fs::recursive_directory_iterator(m_root))
            if (entry.is_regular_file())
            {
                setTimestamp3001(entry.path());
                ++count;
            }
        std::cout << "  Timestamps set on " << count << " file(s).\n";
    }

    /**
     * @brief Prints the final report as required by the spec:
     *   - Total size of the new dataset
     *   - Number of replicated files per category
     *   - Total number of new files (original + augmented)
     */
    void printReport()
    {
        uintmax_t finalSize = directorySize(m_root);

        std::cout << "\n========== FINAL REPORT ==========\n";
        std::cout << "Original dataset size  : " << formatSize(m_originalSize) << "\n";
        std::cout << "New dataset size       : " << formatSize(finalSize)      << "\n";
        std::cout << "Bytes added            : " << formatSize(m_totalNewBytes) << "\n";
        std::cout << "Actual increase        : "
                  << std::fixed << std::setprecision(1)
                  << (100.0 * m_totalNewBytes / m_originalSize) << " %\n\n";

        std::cout << "Replicated files per category:\n";
        int totalAugmented = 0;
        for (const auto& cat : CATEGORIES)
        {
            int n = m_newFilesPerCat.count(cat) ? m_newFilesPerCat.at(cat) : 0;
            totalAugmented += n;
            std::cout << "  " << std::left << std::setw(12) << cat
                      << ": " << n << " new file(s)\n";
        }

        // m_totalOrigFiles is counted before augmentation starts.
        std::cout << "\nOriginal file count    : " << m_totalOrigFiles << "\n";
        std::cout << "Augmented files added  : " << totalAugmented    << "\n";
        std::cout << "Total files in dataset : " << (m_totalOrigFiles + totalAugmented) << "\n";
        std::cout << "\nFile timestamps        : January 1, Year 3001 (all files)\n";
        std::cout << "===================================\n";
    }
};

        // ---------------------------------------------------------------------------
        // Cleanup
        // ---------------------------------------------------------------------------

        /**
         * @brief Performs post-processing cleanup as required by the spec:
         *
         *  1. Creates Avatar/openbigdata/brainwaves/access_data.txt with the
         *     GitHub large-file warning message.
         *  2. Removes all brainwave (.csv / .txt) files from the Avatar directories
         *     so that only the access_data.txt pointer file remains.
         *
         * @param dataRoot   Path to the dataset root (Data_clean).
         * @param avatarRoot Path to the Avatar/openbigdata/brainwaves directory.
         */
        static void runCleanup(const fs::path &dataRoot, const fs::path &avatarRoot)
        {
            // -----------------------------------------------------------------------
            // 1. Create access_data.txt
            // -----------------------------------------------------------------------
            fs::create_directories(avatarRoot);
            fs::path accessFile = avatarRoot / "access_data.txt";

            std::ofstream ofs(accessFile);
            if (!ofs.is_open())
            {
                std::cerr << "  [ERROR] Could not create " << accessFile << "\n";
                return;
            }
            ofs << ACCESS_MSG;
            ofs.close();
            std::cout << "  Created: " << accessFile << "\n";

            // -----------------------------------------------------------------------
            // 2. Remove brainwave files from Avatar directories (keep access_data.txt).
            // -----------------------------------------------------------------------
            int removed = 0;
            for (const auto &entry : fs::recursive_directory_iterator(avatarRoot))
            {
                if (!entry.is_regular_file())
                    continue;
                std::string ext = toLower(entry.path().extension().string());
                if (ext == ".csv" || ext == ".txt")
                {
                    // Never remove the access file itself.
                    if (entry.path().filename() == "access_data.txt")
                        continue;
                    fs::remove(entry.path());
                    ++removed;
                }
            }
            std::cout << "  Removed " << removed << " brainwave file(s) from Avatar directories.\n";
            std::cout << "  Cleanup complete.\n";
        }

        // ---------------------------------------------------------------------------
        // Terminal menu
        // ---------------------------------------------------------------------------

        /**
         * @brief Prints the interactive menu to stdout.
         * @param currentFolder  Currently selected folder path, or empty if none.
         */
        static void printMenu(const std::string &currentFolder)
        {
            std::cout << "\n==========================================\n";
            std::cout << "  BCI Dataset Augmentation -- Open Data #349\n";
            std::cout << "==========================================\n";

            if (currentFolder.empty())
                std::cout << "  Folder : (none selected)\n";
            else
                std::cout << "  Folder : " << currentFolder << "\n";

            std::cout << "------------------------------------------\n";
            std::cout << "  --- Data Preparation ---\n";
            std::cout << "  1) Select / change folder\n";
            std::cout << "  2) Unify Thoughts\n";
            std::cout << "  3) Remove 8-Channel Data\n";
            std::cout << "  4) Run File Shuffler\n";
            std::cout << "  --- Data Generation ---\n";
            std::cout << "  5) Generate Augmented Data (+60%)\n";
            std::cout << "  --- Cleanup ---\n";
            std::cout << "  6) Cleanup (create access_data.txt)\n";
            std::cout << "  ---\n";
            std::cout << "  7) Exit\n";
            std::cout << "------------------------------------------\n";
            std::cout << "  Choice: ";
        }

        /**
         * @brief Prompts the user for a folder path and validates it.
         * @return  Validated path string, or "" if cancelled.
         */
        static std::string promptForFolder()
        {
            std::cout << "\nEnter path to Data_clean folder (or 'q' to cancel):\n> ";
            std::string input;
            std::getline(std::cin, input);
            if (input == "q" || input == "Q")
                return "";

            fs::path p{input};
            if (!fs::exists(p) || !fs::is_directory(p))
            {
                std::cout << "  [!] Path not found: " << input << "\n";
                return "";
            }

            try
            {
                std::cout << "  Folder size: " << formatSize(directorySize(p)) << "\n";
            }
            catch (...)
            {
            }

            return input;
        }

        // ---------------------------------------------------------------------------
        // main
        // ---------------------------------------------------------------------------

        /**
         * @brief Application entry point.
         *
         * Runs the interactive terminal menu.  Steps 2-6 require a folder to be
         * selected first via option 1.
         *
         * @return  0 on normal exit.
         */
        int main()
        {
#ifdef _WIN32
            // Set Windows console to UTF-8 so all characters display correctly.
            SetConsoleOutputCP(65001);
#endif
            std::cout << "\nIMPORTANT: Brain-wave data must NOT be shared or published\n"
                      << "           without proper protocols and authorization.\n";

            std::string folderPath;
            bool running = true;

            while (running)
            {
                printMenu(folderPath);

                std::string input;
                std::getline(std::cin, input);
                if (input.empty())
                    continue;

                int choice = 0;
                try
                {
                    choice = std::stoi(input);
                }
                catch (...)
                {
                    std::cout << "  [!] Please enter a number 1-7.\n";
                    continue;
                }

                // Guard used by options 2-6.
                auto requireFolder = [&]() -> bool
                {
                    if (folderPath.empty())
                    {
                        std::cout << "  [!] No folder selected. Choose option 1 first.\n";
                        return false;
                    }
                    return true;
                };

                switch (choice)
                {
                // ----------------------------------------------------------------
                // 1 -- Select folder
                // ----------------------------------------------------------------
                case 1:
                {
                    std::string p = promptForFolder();
                    if (!p.empty())
                    {
                        folderPath = p;
                        std::cout << "  Folder set.\n";
                    }
                    break;
                }

                // ----------------------------------------------------------------
                // 2 -- Unify Thoughts
                // ----------------------------------------------------------------
                case 2:
                {
                    if (!requireFolder())
                        break;
                    std::cout << "\n  Running: Unify Thoughts...\n";
                    try
                    {
                        fs::path p{folderPath};
                        DataSanitizer san{p};
                        std::cout << "  " << san.unifyThoughts() << "\n";
                    }
                    catch (const std::exception &ex)
                    {
                        std::cerr << "  [ERROR] " << ex.what() << "\n";
                    }
                    break;
                }

                // ----------------------------------------------------------------
                // 3 -- Remove 8-Channel Data
                // ----------------------------------------------------------------
                case 3:
                {
                    if (!requireFolder())
                        break;
                    std::cout << "\n  Running: Remove 8-Channel Data...\n";
                    try
                    {
                        fs::path p{folderPath};
                        DataSanitizer san{p};
                        std::cout << "  " << san.remove8ChannelData() << "\n";
                    }
                    catch (const std::exception &ex)
                    {
                        std::cerr << "  [ERROR] " << ex.what() << "\n";
                    }
                    break;
                }

                // ----------------------------------------------------------------
                // 4 -- Run File Shuffler
                // ----------------------------------------------------------------
                case 4:
                {
                    if (!requireFolder())
                        break;
                    std::cout << "\n  Running: Run File Shuffler...\n";
                    try
                    {
                        fs::path p{folderPath};
                        DataSanitizer san{p};
                        std::cout << "  " << san.runFileShuffler() << "\n";
                    }
                    catch (const std::exception &ex)
                    {
                        std::cerr << "  [ERROR] " << ex.what() << "\n";
                    }
                    break;
                }

                // ----------------------------------------------------------------
                // 5 -- Generate Augmented Data
                // ----------------------------------------------------------------
                case 5:
                {
                    if (!requireFolder())
                        break;
                    std::cout << "\n  Running: Data Generation (+60%)...\n";
                    std::cout << "  Note: run steps 2, 3, 4 before this step.\n\n";
                    try
                    {
                        fs::path p{folderPath};
                        uintmax_t origSize = directorySize(p);
                        DataAugmenter aug{p, origSize};
                        aug.run();
                    }
                    catch (const std::exception &ex)
                    {
                        std::cerr << "  [ERROR] " << ex.what() << "\n";
                    }
                    break;
                }

                // ----------------------------------------------------------------
                // 6 -- Cleanup
                // ----------------------------------------------------------------
                case 6:
                {
                    if (!requireFolder())
                        break;

                    // Ask for the Avatar/openbigdata/brainwaves output path.
                    std::cout << "\nEnter path to Avatar/openbigdata/brainwaves output dir:\n"
                              << "(press Enter to use Data_clean/brainwaves)\n> ";
                    std::string avatarInput;
                    std::getline(std::cin, avatarInput);

                    fs::path avatarPath = avatarInput.empty()
                                              ? fs::path{folderPath} / "brainwaves"
                                              : fs::path{avatarInput};

                    std::cout << "\n  Running: Cleanup...\n";
                    try
                    {
                        runCleanup(fs::path{folderPath}, avatarPath);
                    }
                    catch (const std::exception &ex)
                    {
                        std::cerr << "  [ERROR] " << ex.what() << "\n";
                    }
                    break;
                }

                // ----------------------------------------------------------------
                // 7 -- Exit
                // ----------------------------------------------------------------
                case 7:
                    std::cout << "\n  Goodbye.\n\n";
                    running = false;
                    break;

                default:
                    std::cout << "  [!] Invalid choice. Enter 1-7.\n";
                    break;
                }
            }

            return 0;
        }
