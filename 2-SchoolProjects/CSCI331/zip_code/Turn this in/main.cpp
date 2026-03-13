/**
 * @file main.cpp
 * @brief Application to find extreme ZIP codes by state
 * @author CSCI 331 Team 2
 * @date 02/12/2026
 * 
 * @class ZipCodeRecord
 * @brief Represents a single ZIP code record with associated data
 * This program reads a CSV file containing US postal code data and generates
 * a report showing the easternmost, westernmost, northernmost, and southernmost
 * ZIP codes for each state. The results are presented in alphabetical order
 * by state abbreviation.
 * 
 * Geographic extremes are determined by:
 * - Easternmost: Least (most negative) longitude value
 * - Westernmost: Greatest (least negative) longitude value
 * - Northernmost: Greatest latitude value
 * - Southernmost: Least latitude value
 * 
 * @note In the US, longitude values are negative (west of Prime Meridian)
 *       so "least longitude" means "furthest east"
 */

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <limits>
#include "ZipCodeBuffer.h"
#include "ZipCodeRecord.h"

/**
 * @struct StateExtremes
 * @brief Holds the extreme ZIP codes for a single state
 * @pre All fields must be properly initialized before use
 * @post Instances of StateExtremes can be used to track and update extreme ZIP codes for a state
 * 
 * @note This structure maintains the four geographic extreme ZIP codes for a state:
 * @note easternmost, westernmost, northernmost, and southernmost. It updates these
 * @note values as records are processed.
 */
struct StateExtremes {
    ZipCodeRecord easternmost;  /**< ZIP code with least (most negative) longitude */
    ZipCodeRecord westernmost;  /**< ZIP code with greatest (least negative) longitude */
    ZipCodeRecord northernmost; /**< ZIP code with greatest latitude */
    ZipCodeRecord southernmost; /**< ZIP code with least latitude */
    bool initialized;           /**< Flag indicating if any data has been set */
    
    /**
     * @brief Default constructor
     * @param None
     * @pre None
     * @post All fields are initialized to default values  
     * @return An instance of StateExtremes with default values
     * 
     * Initializes the structure with sentinel values that will be replaced
     * by the first actual record encountered.
     */
    StateExtremes() : initialized(false) {
        // Initialize with extreme values that will be replaced
        easternmost.longitude = std::numeric_limits<double>::max();    // Want minimum
        westernmost.longitude = std::numeric_limits<double>::lowest(); // Want maximum
        northernmost.latitude = std::numeric_limits<double>::lowest(); // Want maximum
        southernmost.latitude = std::numeric_limits<double>::max();    // Want minimum
    }
    
    /**
     * @brief Update extreme values with a new record
     * @param record The ZIP code record to consider
     * @pre record must contain valid ZIP code data
     * @post Extreme values are updated if the record represents a new extreme in any direction
     * @return None
     * 
     * Compares the provided record's coordinates with current extremes
     * and updates if the record represents a new extreme in any direction.
     * 
     * @note For longitude in the US (negative values):
     *       - Easternmost has the LEAST (most negative) value
     *       - Westernmost has the GREATEST (least negative) value
     */
    void update(const ZipCodeRecord& record) {
        if (!initialized) {
            // First record for this state - initialize all extremes
            easternmost = westernmost = northernmost = southernmost = record;
            initialized = true;
        } else {
            // Update easternmost (least/most negative longitude)
            if (record.longitude < easternmost.longitude) {
                easternmost = record;
            }
            
            // Update westernmost (greatest/least negative longitude)
            if (record.longitude > westernmost.longitude) {
                westernmost = record;
            }
            
            // Update northernmost (greatest latitude)
            if (record.latitude > northernmost.latitude) {
                northernmost = record;
            }
            
            // Update southernmost (least latitude)
            if (record.latitude < southernmost.latitude) {
                southernmost = record;
            }
        }
    }
};

/**
 * @brief Print a formatted table header
 * @pre None
 * @post Column headers are printed to standard output
 * @return None
 * Prints column headers for the extreme ZIP codes report.
 * Headers are formatted to align with data columns.
 */
void printTableHeader() {
    std::cout << std::left
              << std::setw(6) << "State"
              << std::setw(12) << "Easternmost"
              << std::setw(12) << "Westernmost"
              << std::setw(12) << "Northernmost"
              << std::setw(12) << "Southernmost"
              << std::endl;
    std::cout << std::string(54, '-') << std::endl;
}

/**
 * @brief Print extreme ZIP codes for a single state
 * @param state Two-character state abbreviation
 * @param extremes StateExtremes structure containing the extreme values
 * @pre state is a valid state abbreviation and extremes contains valid data
 * @post A formatted row of extreme ZIP codes is printed to standard output
 * @return None
 * 
 * Prints one row of the report showing the four extreme ZIP codes
 * for the specified state. All ZIP codes are right-aligned.
 */
void printStateRow(const std::string& state, const StateExtremes& extremes) {
    std::cout << std::left << std::setw(6) << state
              << std::right
              << std::setw(12) << extremes.easternmost.zipCode
              << std::setw(12) << extremes.westernmost.zipCode
              << std::setw(12) << extremes.northernmost.zipCode
              << std::setw(12) << extremes.southernmost.zipCode
              << std::endl;
}

/**
 * @brief Process CSV file and generate extreme ZIP codes report
 * @param filename Path to the CSV file containing ZIP code data
 * @pre filename is a valid path to a CSV file with the expected format
 * @post The CSV file is read and a report of extreme ZIP codes by state is printed
 * @return 0 on success, non-zero on error
 * 
 * This function:
 * 1. Opens the CSV file using ZipCodeBuffer
 * 2. Reads all records and tracks extremes for each state
 * 3. Prints a formatted report of results
 * 
 * The report lists states alphabetically and shows the four extreme
 * ZIP codes (east, west, north, south) for each state.
 */
int processZipCodeFile(const std::string& filename) {
    // Create buffer for reading CSV file
    ZipCodeBuffer buffer(filename);
    
    // Open the file
    if (!buffer.open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }
    
    std::cout << "Processing file: " << filename << std::endl;
    std::cout << std::endl;
    
    // Map to store extreme values for each state
    // Key: State abbreviation (2 characters)
    // Value: StateExtremes structure with extreme ZIP codes
    std::map<std::string, StateExtremes> stateExtremes;
    
    // Read all records and track extremes
    ZipCodeRecord record;
    while (buffer.getNextRecord(record)) {
        // Update extremes for this state
        stateExtremes[record.state].update(record);
    }
    
    // Close the file
    buffer.close();
    
    // Print summary statistics
    std::cout << "Total records processed: " << buffer.getRecordCount() << std::endl;
    std::cout << "Total states found: " << stateExtremes.size() << std::endl;
    std::cout << std::endl;
    
    // Print table header
    printTableHeader();
    
    // Print results for each state in alphabetical order
    // std::map automatically maintains keys in sorted order
    for (const auto& pair : stateExtremes) {
        const std::string& state = pair.first;
        const StateExtremes& extremes = pair.second;
        
        // Only print if state has valid data
        if (extremes.initialized) {
            printStateRow(state, extremes);
        }
    }
    
    std::cout << std::endl;
    return 0;
}

/**
 * @brief Main entry point of the application
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @pre None
 * @post The program processes the specified CSV file and generates a report
 * @return 0 on success, 1 on error
 * 
 * The program expects one command-line argument: the path to the CSV file.
 * If no argument is provided, it uses a default filename.
 * 
 * Usage: ./zipcode_extremes <csv_filename>
 * 
 * The program reads the CSV file and generates a report showing the
 * easternmost, westernmost, northernmost, and southernmost ZIP codes
 * for each state, listed in alphabetical order by state.
 */
int main(int argc, char* argv[]) {
    std::cout << "======================================================" << std::endl;
    std::cout << "   US Postal Code Geographic Extremes by State" << std::endl;
    std::cout << "======================================================" << std::endl;
    std::cout << std::endl;
    
    // Determine which CSV file to process
    std::string filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        // Default filename if none provided
        filename = "us_postal_codes_by_zipcode.csv";
        std::cout << "No filename provided. Using default: " << filename << std::endl;
        std::cout << std::endl;
    }
    
    // Process the file and generate report
    int result = processZipCodeFile(filename);
    
    if (result == 0) {
        std::cout << "Processing completed successfully." << std::endl;
    } else {
        std::cout << "Processing failed with error code: " << result << std::endl;
    }
    
    return result;
}
