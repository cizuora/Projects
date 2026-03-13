/**
 * @file ZipCodeBuffer.h
 * @brief Buffer class for reading ZIP code records from CSV files
 * @author CSCI 331 Team 2
 * @date 3/13/2026
 * @version 2.0
 */

#ifndef ZIPCODEBUFFER_H
#define ZIPCODEBUFFER_H

#include <fstream>
#include <string>
#include "ZipCodeRecord.h"

/**
 * @class ZipCodeBuffer
 * @brief Buffered reader for ZIP code CSV files
 * This class provides functionality to read ZIP code records from a CSV file, parse them into ZipCodeRecord structures, and manage the file stream. It handles opening and closing the file, reading records sequentially, and keeping track of the number of records read.
 * @pre The specified CSV file must exist and be in the correct format with a header line followed by data lines.
 * @post Instances of ZipCodeBuffer can be used to read and process ZIP code records from the specified CSV file, providing access to individual records and file management functions.
 * @note The CSV file is expected to have the following columns in order: ZIP code, Place name, State, County name, Latitude, Longitude. The first line of the file is assumed to be a header and will be skipped during reading.
 */
class ZipCodeBuffer
{
private:
    std::ifstream inputFile;
    std::string filename;
    bool fileIsOpen;
    bool headerSkipped;
    int recordCount;

    /**
     * @brief   Parse a line of CSV data into a ZipCodeRecord structure
     *
     * @param line The CSV line to parse
     * @param record The ZipCodeRecord to populate
     * @return true if parsing was successful, false otherwise
     */
    bool parseCsvLine(const std::string &line, ZipCodeRecord &record);

    /**
     * @brief  Extract a field from a CSV line, handling quoted fields and trimming whitespace
     *
     * @param line The CSV line to extract the field from
     * @param startPos The starting position in the line
     * @return std::string The extracted field
     */
    std::string extractField(const std::string &line, size_t &startPos);

    /**
     * @brief Trim leading and trailing whitespace from a string
     * @param str The input string to be trimmed
     * @return A new string with leading and trailing whitespace removed
     * @note This function is used to clean up fields extracted from the CSV line, ensuring that any extra spaces do not affect data processing.
     */
    std::string trim(const std::string &str);

public:
    /**
     * @brief Constructor for ZipCodeBuffer
     * @param csvFilename The name of the CSV file to read from
     * @pre The specified CSV file must exist and be in the correct format.
     * @post A ZipCodeBuffer instance is created and initialized with the specified filename, but the file is not opened until open() is called.
     */
    explicit ZipCodeBuffer(const std::string &csvFilename);

    /**
     * @brief Destructor for ZipCodeBuffer
     * @pre None
     * @post The file stream is closed if it is open, and any resources are released.
     */
    ~ZipCodeBuffer();

    /**
     * @brief Open the CSV file for reading
     * @return true if the file was opened successfully, false otherwise
     * @pre The ZipCodeBuffer instance must have been initialized with a valid filename.
     * @post The file stream is opened and ready for reading. If the file cannot be opened, an error message is printed and the function returns false.
     */
    bool open();

    /**
     * @brief Close the CSV file
     * @pre The file stream must be open.
     * @post The file stream is closed and the ZipCodeBuffer instance is reset to a state where it can be opened again if needed.
     */
    void close();

    /**
     * @brief Get the Next Record object
     * @pre The file stream must be open and positioned at the beginning of a record (after the header line).
     * @post If a record is successfully read and parsed, the provided ZipCodeRecord reference is populated with the data from the next line of the CSV file. If the end of the file is reached or an error occurs during reading or parsing, the function returns false.
     * @param record A reference to a ZipCodeRecord structure that will be populated with the next record from the CSV file
     * @return true if a record was successfully retrieved, false otherwise
     * @return false
     */
    bool getNextRecord(ZipCodeRecord &record);

    /**
     * @brief Check if the CSV file is open
     * @pre None
     * @post Returns true if the file stream is open, false otherwise
     * @return true if the file is open, false otherwise
     */
    bool isOpen() const;

    /**
     * @brief Get the name of the CSV file being read
     * @pre None
     * @post Returns the filename that was specified when the ZipCodeBuffer instance was created
     * @return The name of the CSV file being read
     */
    std::string getFilename() const;

    /**
     * @brief Get the number of records read from the CSV file
     * @pre None
     * @post Returns the count of records that have been successfully read and parsed from the CSV file since it was opened or last reset.
     * @return The number of records read from the CSV file
     */
    long getRecordCount() const;

    /**
     * @brief Reset the ZipCodeBuffer to its initial state
     * @pre None
     * @post The file stream is closed if it is open, the record count is reset to zero, and the headerSkipped flag is reset to false. This allows the ZipCodeBuffer instance to be reused for reading from the same or a different CSV file.
     * @return true if the buffer was successfully reset, false otherwise
     */
    bool reset();
};

#endif // ZIPCODEBUFFER_H