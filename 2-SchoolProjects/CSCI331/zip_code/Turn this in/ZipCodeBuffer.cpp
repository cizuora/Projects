/**
 * @file ZipCodeBuffer.cpp
 * @brief Implementation of the ZipCodeBuffer class
 * @author CSCI 331 Team 2
 * @date 02/12/2026
 * 
 * @class ZipCodeBuffer
 * @brief A class to manage a buffer of zip codes
 * Assumptions:
 * - The CSV file is well-formed with the expected columns in the correct order.
 * - The file uses UTF-8 encoding and standard CSV formatting (commas as delimiters, quotes for fields containing commas).
 * - The class is responsible for managing the file stream and parsing the CSV data into ZipCodeRecord structures.
 * - The class does not handle concurrent access or multi-threading scenarios; it is intended for single-threaded use.
 * - The class assumes that the CSV file is not modified externally while it is being read, and does not implement file change detection.
 * 
 */

#include "ZipCodeBuffer.h"
#include <sstream>
#include <iostream>
#include <algorithm>

/**
 * @brief Construct a new Zip Code Buffer:: Zip Code Buffer object  
 * @pre csvFilename is a valid file path
 * @param csvFilename 
 * @post ZipCodeBuffer is initialized but file is not opened
 * @return An instance of ZipCodeBuffer
 * @note File will be opened using open() method 
 */
ZipCodeBuffer::ZipCodeBuffer(const std::string& csvFilename)
    : filename(csvFilename), fileIsOpen(false), headerSkipped(false), recordCount(0) {
    /* Constructor body - initialization is done in initializer list */
}


/**
 * @brief Destroy the Zip Code Buffer:: Zip Code Buffer object
 * @pre File is opened
 * @post File is closed if it was open
 * @return None
 * @note Calls close() if file is still open
 */
ZipCodeBuffer::~ZipCodeBuffer() {
    close();  // Safe to call even if already closed
}

/**
 * @brief Open the CSV file for reading
 * @return true if file opened successfully
 * @pre File is not already open  
 * @post File is opened and ready for reading
 * @note Handles file not found or access errors
 * 
 */
bool ZipCodeBuffer::open() {
    // Close any previously opened file
    close();
    
    // Open the file
    inputFile.open(filename);
    
    // Check if open was successful
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        fileIsOpen = false;
        return false;
    }
    
    fileIsOpen = true;
    headerSkipped = false;  // Reset header flag
    recordCount = 0;        // Reset record counter
    return true;
}

/**
 * @brief Close the CSV file
 * @pre File is open
 * @post File is closed
 * @return None
 * @note Safe to call even if file is already closed
 * 
 */
void ZipCodeBuffer::close() {
    if (fileIsOpen && inputFile.is_open()) {
        inputFile.close();
    }
    fileIsOpen = false;
}

/**
 * @brief Read the next record from the file
 * @param record Reference to ZipCodeRecord to populate
 * @return true if record read successfully, false if EOF or error
 * @pre File is open and ready for reading
 * @post record is populated with the next record's data
 *       elements true is return otherwise
 * @return true if arrays are not equal, false otherwise
 * @remark Uses operator== for implementation
 */
bool ZipCodeBuffer::getNextRecord(ZipCodeRecord& record) {
    // Ensure file is open
    if (!fileIsOpen || !inputFile.is_open()) {
        return false;
    }
    
    // Skip header row on first read
    if (!headerSkipped) {
        std::string headerLine;
        if (!std::getline(inputFile, headerLine)) {
            return false;  // File is empty
        }
        headerSkipped = true;
    }
    
    // Read next line
    std::string line;
    while (std::getline(inputFile, line)) {
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }
        
        // Try to parse the line
        if (parseCsvLine(line, record)) {
            recordCount++;
            return true;
        } else {
            // Parsing failed - log warning and continue to next line
            std::cerr << "Warning: Could not parse line " << (recordCount + 1) 
                      << ": " << line.substr(0, 50) << "..." << std::endl;
        }
    }
    
    // End of file reached
    return false;
}

/**
 * @brief Parse a CSV line into a ZipCodeRecord
 * @param line The CSV line to parse
 * @param record Reference to record to populate
 * @pre line is a valid CSV formatted string
 * @post record is populated with parsed data
 * @return true if parsing successful
 * @note Handles conversion of string fields to appropriate types
 */
bool ZipCodeBuffer::parseCsvLine(const std::string& line, ZipCodeRecord& record) {
    try {
        size_t pos = 0;
        
        // Extract ZIP code (field 0)
        std::string zipStr = extractField(line, pos);
        record.zipCode = std::stoi(zipStr);
        
        // Extract place name (field 1)
        record.placeName = extractField(line, pos);
        
        // Extract state (field 2)
        record.state = extractField(line, pos);
        
        // Extract county (field 3)
        record.county = extractField(line, pos);
        
        // Extract latitude (field 4)
        std::string latStr = extractField(line, pos);
        record.latitude = std::stod(latStr);
        
        // Extract longitude (field 5)
        std::string lonStr = extractField(line, pos);
        record.longitude = std::stod(lonStr);
        
        return true;
        
    } catch (const std::exception& e) {
        // Conversion or parsing error occurred
        std::cerr << "Parse error: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Extract a field from a CSV line
 * @param line The CSV line
 * @param startPos Position to start extraction
 * @pre startPos is within the bounds of line
 * @post startPos is updated to the position after the extracted field
 * @return Extracted field as a string
 * @note Handles quoted fields and commas within quotes
 */
std::string ZipCodeBuffer::extractField(const std::string& line, size_t& pos) {
    std::string field;
    bool inQuotes = false;
    
    // Skip leading whitespace
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) {
        pos++;
    }
    
    // Check for quoted field
    if (pos < line.length() && line[pos] == '"') {
        inQuotes = true;
        pos++; // Skip opening quote
    }
    
    // Extract field content
    while (pos < line.length()) {
        char c = line[pos];
        
        if (inQuotes) {
            if (c == '"') {
                // Check for escaped quote (two quotes in a row)
                if (pos + 1 < line.length() && line[pos + 1] == '"') {
                    field += '"';
                    pos += 2;
                } else {
                    // End of quoted field
                    pos++;
                    inQuotes = false;
                    break;
                }
            } else {
                field += c;
                pos++;
            }
        } else {
            if (c == ',') {
                // End of field
                pos++;
                break;
            } else {
                field += c;
                pos++;
            }
        }
    }
    
    // Skip trailing comma if present
    if (pos < line.length() && line[pos] == ',') {
        pos++;
    }
    
    return trim(field);
}

/**
 * @brief Trim whitespace from both ends of a string
 * @param str The string to trim
 * @pre str is a valid string
 * @post Leading and trailing whitespace is removed
 * @return Trimmed string
 * @note Uses standard library functions for trimming
 */
std::string ZipCodeBuffer::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";  // String is all whitespace
    }
    
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

/**
 * @brief Check if the file is currently open
 * @return true if file is open, false otherwise
 * @pre None
 * @post None
 * @return true if file is open, false otherwise
 */
bool ZipCodeBuffer::isOpen() const {
    return fileIsOpen;
}

/**
 * @brief Get the number of records read so far
 * @return Number of records read
 * @pre None
 * @post None
 * @return Number of records read
 */
long ZipCodeBuffer::getRecordCount() const {
    return recordCount;
}

/**
 * @brief Get the filename of the CSV file being read
 * @return Filename as a string
 * @pre None
 * @post None
 * @return Filename as a string
 */
std::string ZipCodeBuffer::getFilename() const {
    return filename;
}

/**
 * @brief Reset the buffer to the beginning of the file
 * @return true if reset successful, false otherwise
 * @pre File is open
 * @post File is reset to the beginning and ready for reading
 * @note Closes and reopens the file to reset state
 */
bool ZipCodeBuffer::reset() {
    close();
    return open();
}