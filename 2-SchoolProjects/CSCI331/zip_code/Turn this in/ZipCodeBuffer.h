/**
 * @file ZipCodeBuffer.h
 * @brief Buffer class for reading ZIP code records from CSV files
 * @author CSCI 331 Team 2
 * @date 2/12/2026
 * @version 1.0
 * 
 * @class ZipCodeBuffer
 * @brief Class to handle buffered reading of ZIP code records from a CSV file
 * Assumptions:
    *   -- The CSV file has a header row that should be skipped
    *  -- Each subsequent row contains valid ZIP code data
    *  -- The buffer reads one record at a time
    *  -- The file is well-formed and accessible
    *  -- Zip codes are represented as integers
    *  -- Latitude and longitude are represented as doubles
    *  -- String fields do not contain commas
    *  -- The class manages its own file stream
    *  -- The user is responsible for checking if the file opened successfully
    *  -- The user is responsible for handling end-of-file conditions
    *  -- The class provides methods to open, close, and read records from the file
    *  -- The class tracks the number of records read
    *  -- The class provides a method to reset the read position to the beginning of the file
    *  -- The class provides methods to check if the file is open and to get the filename
    * -- The class provides a method to get the number of records read so far
    * -- The class provides a method to trim whitespace from strings
    * -- The class provides a method to extract fields from a CSV line
    * -- The class provides a method to parse a CSV line into a ZipCodeRecord
    * 
 */

#ifndef ZIPCODEBUFFER_H
#define ZIPCODEBUFFER_H

#include <fstream>
#include <string>
#include "ZipCodeRecord.h"

/**
 * @class ZipCodeBuffer
 * @brief Buffered reader for ZIP code CSV files
 * 
 */
class ZipCodeBuffer {
private:
    std::ifstream inputFile;    /**< Input file stream for reading CSV data */
    std::string filename;       /**< Name of the CSV file being read */
    bool fileIsOpen;           /**< Flag indicating if the file is currently open */
    bool headerSkipped;        /**< Flag indicating if the header row has been skipped */
    int recordCount;           /**< Number of records read so far */
    
    /**
     * @brief Parse a CSV line into a ZipCodeRecord
     * @param line The CSV line to parse
     * @param record Reference to record to populate
     * @pre line is a valid CSV formatted string
     * @post record is populated with parsed data
     * @return true if parsing successful
     * @note Handles conversion of string fields to appropriate types
     */
    bool parseCsvLine(const std::string& line, ZipCodeRecord& record);
    

    /**
     * @brief Extract a field from a CSV line
     * @param line The CSV line
     * @param startPos Position to start extraction
     * @pre startPos is within the bounds of line
     * @post startPos is updated to the position after the extracted field
     * @return Extracted field as a string
     * @note Handles quoted fields and commas within quotes
     */
    std::string extractField(const std::string& line, size_t& startPos);

    /**
     * @brief Trim whitespace from both ends of a string
     * @param str The string to trim
     * @pre str is a valid string
     * @post Leading and trailing whitespace is removed
     * @return Trimmed string
     * @note Uses standard library functions for trimming
     */
    std::string trim(const std::string& str);

public:
    /**
     * @brief Constructor
     * @param csvFilename Path to the CSV file
     * @pre csvFilename is a valid file path
     * @post ZipCodeBuffer is initialized but file is not opened
     * @return An instance of ZipCodeBuffer
     * @note File will be opened using open() method
     */
    explicit ZipCodeBuffer(const std::string& csvFilename);
    
    /**
     * @brief Destructor
     * @pre File is opened
     * @post File is closed if it was open
     * @return None
     * @note Calls close() if file is still open
     */
    ~ZipCodeBuffer();
    
    /**
     * @brief Open the CSV file for reading
     * @return true if file opened successfully
     * @pre File is not already open  
     * @post File is opened and ready for reading
     * @note Handles file not found or access errors
     * 
     */
    bool open();
    
    /**
     * @brief Close the CSV file
     * @pre File is open
     * @post File is closed
     * @return None
     * @note Safe to call even if file is already closed
     * 
     */
    void close();
    
    /**
     * @brief Read the next record from the file
     * @param record Reference to ZipCodeRecord to populate
     * @return true if record read successfully, false if EOF or error
     * @pre File is open and ready for reading
     * @post record is populated with the next record's data
     * @note Skips header row if not already skipped
     */
    bool getNextRecord(ZipCodeRecord& record);
    
    /**
     * @brief Check if the file is currently open
     * @pre None
     * @post Returns the open status of the file
     * @return true if file is open, false otherwise
     * @note Useful for verifying file state before reading
     */
    bool isOpen() const;
    
    /**
     * @brief Get the Filename object   
     * @pre None
     * @post Returns the name of the CSV file being read
     * @note Useful for logging or error messages
     * @return * std::string 
     */
    std::string getFilename() const;

    /**
     * @brief Get the number of records read so far
     * @pre None
     * @post Returns the count of records read
     * @return Number of records read
     * @note Useful for tracking progress
     */
    long getRecordCount() const;

    /**
     * @brief Reset the buffer to the beginning of the file
     * @pre File is open
     * @post File read position is reset to the beginning, record count set to zero
     * @return true if reset successful
     * @note Skips header row after reset
     */
    bool reset();
};
#endif // ZIPCODEBUFFER_H
