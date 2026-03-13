/**
 * @file LengthIndicatedBuffer.h
 * @brief Buffer class for length-indicated ZIP code files
 * @author CSCI 331 Team 2
 * @date 03/13/2026
 * @version 2.0
 *
 * @class LengthIndicatedBuffer
 * @brief Buffered reader/writer for length-indicated ZIP code files
 *
 * This class handles reading and writing ZIP code records in a length-indicated
 * format. Each record is preceded by a 4-byte integer indicating its length.
 * The file begins with a header that describes the file structure.
 */

#ifndef LENGTHINDICATEDBUFFER_H
#define LENGTHINDICATEDBUFFER_H

#include <fstream>
#include <string>
#include "ZipCodeRecord.h"
#include "DataFileHeader.h"

/**
 * @class LengthIndicatedBuffer
 * @brief Buffered reader/writer for length-indicated ZIP code files
 *
 * Assumptions:
 *   - The file follows the length-indicated format with header
 *   - Records are stored sequentially after the header
 *   - Each record is preceded by a 4-byte length field
 *   - The header contains all necessary metadata
 */
class LengthIndicatedBuffer
{
private:
    std::fstream dataFile; /**< Data file stream */
    std::string filename;  /**< Name of the data file */
    bool fileIsOpen;       /**< Flag indicating if file is open */
    bool isReadMode;       /**< True if opened for reading, false for writing */
    DataFileHeader header; /**< File header */
    long recordCount;      /**< Number of records processed */
    long currentPosition;  /**< Current read/write position */

    /**
     * @brief Read the next record from file
     * @param record Reference to record to populate
     * @pre File is open in read mode and positioned at a valid record
     * @post record is populated with data from the next record, file position advanced
     * @return true if record read successfully, false on error or EOF
     */
    bool readNextRecord(ZipCodeRecord &record);

    /**
     * @brief Write a record to file at current position
     * @param record Record to write
     * @pre File is open in write mode
     * @post Record is written to file with length prefix, file position advanced
     * @return true if successful, false on error
     */
    bool writeRecord(const ZipCodeRecord &record);

    /**
     * @brief Pack a record into a byte buffer
     * @param record Record to pack
     * @param buffer Output buffer
     * @pre buffer is large enough to hold packed record (use record.getPackedSize())
     * @post Record data is written to buffer in binary format
     * @return Number of bytes written to buffer
     */
    size_t packRecord(const ZipCodeRecord &record, char *buffer) const;

    /**
     * @brief Unpack a record from a byte buffer
     * @param buffer Input buffer containing packed record data
     * @param record Reference to record to populate
     * @pre buffer contains valid packed record data
     * @post record is populated with data from buffer
     * @return true if successful, false on error
     */
    bool unpackRecord(const char *buffer, ZipCodeRecord &record) const;

public:
    /**
     * @brief Constructor
     * @param dataFilename Path to the data file
     * @pre dataFilename is a valid file path string
     * @post LengthIndicatedBuffer is initialized but file is not opened
     * @return An instance of LengthIndicatedBuffer
     */
    explicit LengthIndicatedBuffer(const std::string &dataFilename);

    /**
     * @brief Destructor
     * @pre None
     * @post File is closed if it was open, any pending writes are finalized
     * @return None
     */
    ~LengthIndicatedBuffer();

    /**
     * @brief Open the data file for reading
     * @pre File is not already open
     * @post File is opened, header is read and validated, ready for reading records
     * @return true if file opened and header read successfully, false otherwise
     */
    bool openForRead();

    /**
     * @brief Open the data file for writing
     * @pre File is not already open
     * @post File is created/truncated, header is written, ready for writing records
     * @return true if file created and header written successfully, false otherwise
     */
    bool openForWrite();

    /**
     * @brief Close the data file
     * @pre None
     * @post File is closed, header is updated with final record count if in write mode
     * @return None
     */
    void close();

    /**
     * @brief Get next record from file (reading mode)
     * @param record Reference to record to populate
     * @pre File is open in read mode
     * @post record is populated with next record's data, recordCount incremented
     * @return true if record read successfully, false if EOF or error
     */
    bool getNextRecord(ZipCodeRecord &record);

    /**
     * @brief Add a record to the file (writing mode)
     * @param record Record to add
     * @pre File is open in write mode
     * @post Record is appended to file with length prefix, recordCount incremented
     * @return true if successful, false on error
     */
    bool addRecord(const ZipCodeRecord &record);

    /**
     * @brief Get record at specific position
     * @param record Reference to record to populate
     * @param position Position in file (0-based)
     * @pre File is open in read mode, position is valid
     * @post record is populated with data from specified position
     * @return true if record read successfully, false on error
     */
    bool getRecordAt(ZipCodeRecord &record, long position);

    /**
     * @brief Check if file is open
     * @pre None
     * @post Returns current file open status
     * @return true if file is open, false otherwise
     */
    bool isOpen() const { return fileIsOpen; }

    /**
     * @brief Get filename
     * @pre None
     * @post Returns the name of the data file
     * @return Filename string
     */
    std::string getFilename() const { return filename; }

    /**
     * @brief Get record count
     * @pre None
     * @post Returns number of records read/written so far
     * @return Number of records processed
     */
    long getRecordCount() const { return recordCount; }

    /**
     * @brief Get header (mutable reference)
     * @pre None
     * @post Returns reference to header for modification
     * @return Reference to DataFileHeader
     */
    DataFileHeader &getHeader() { return header; }

    /**
     * @brief Get header (const reference)
     * @pre None
     * @post Returns const reference to header
     * @return Const reference to DataFileHeader
     */
    const DataFileHeader &getHeader() const { return header; }

    /**
     * @brief Reset to beginning of file (reading mode)
     * @pre File is open in read mode
     * @post File position is reset to first record after header, recordCount set to 0
     * @return true if successful, false on error
     */
    bool reset();
};

#endif // LENGTHINDICATEDBUFFER_H