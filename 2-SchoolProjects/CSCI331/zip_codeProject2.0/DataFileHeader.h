/**
 * @file DataFileHeader.h
 * @brief Header record structure for length-indicated data files
 * @author CSCI 331 Team 2
 * @date 03/13/2026
 * @version 2.0
 *
 * Header Architecture as specified:
 * - file structure type
 * - version
 * - header record size in bytes
 * - count of bytes for each record size integer
 * - size format type {ASCII or binary}
 * - size of sizes
 * - size inclusion flag
 * - primary key index file name
 * - record count
 * - count of fields per record
 * - for each field: name, type schema
 * - primary key field index
 */

#ifndef DATAFILEHEADER_H
#define DATAFILEHEADER_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

/**
 * @struct FieldDescriptor
 * @brief Describes a single field in the data file
 *
 * @pre None
 * @post FieldDescriptor object is created with specified values
 */
struct FieldDescriptor
{
    std::string name;       /**< Field name or ID */
    std::string typeSchema; /**< Type schema (format to read or write) */
    bool isPrimaryKey;      /**< Indicates if this field is the primary key */

    /**
     * @brief Default constructor
     * @pre None
     * @post FieldDescriptor is initialized with default values (empty strings, isPrimaryKey = false)
     * @return A FieldDescriptor instance with default values
     */
    FieldDescriptor() : isPrimaryKey(false) {}

    /**
     * @brief Parameterized constructor
     * @param n Field name
     * @param t Type schema
     * @param pk Primary key flag (default false)
     * @pre n and t are valid strings
     * @post FieldDescriptor is initialized with provided values
     * @return A FieldDescriptor instance with specified values
     */
    FieldDescriptor(const std::string &n, const std::string &t, bool pk = false)
        : name(n), typeSchema(t), isPrimaryKey(pk) {}
};

/**
 * @class DataFileHeader
 * @brief Manages the header record for length-indicated data files
 *
 * This class implements the required header architecture:
 * - file structure type
 * - version
 * - header record size in bytes
 * - count of bytes for each record size integer
 * - size format type {ASCII or binary}
 * - size of sizes
 * - size inclusion flag
 * - primary key index file name
 * - record count
 * - count of fields per record
 * - for each field: name, type schema
 * - primary key field index
 */
class DataFileHeader
{
private:
    // Required header fields
    std::string fileStructureType;       /**< Type identifier for file structure */
    int version;                         /**< Version number */
    int headerSize;                      /**< Size of header in bytes */
    int recordSizeIntegerBytes;          /**< Bytes used for record size field */
    std::string sizeFormatType;          /**< "ASCII" or "binary" */
    int sizeOfSizes;                     /**< Bytes to represent size */
    bool sizeInclusionFlag;              /**< True if size includes itself */
    std::string primaryKeyIndexFileName; /**< Name of associated index file */
    int recordCount;                     /**< Number of records in file */
    int fieldCount;                      /**< Number of fields per record */
    std::vector<FieldDescriptor> fields; /**< Field descriptors */
    int primaryKeyFieldIndex;            /**< Index of primary key field (-1 if none) */

public:
    /**
     * @brief Default constructor
     * @pre None
     * @post DataFileHeader is initialized with default values:
     *       - fileStructureType = "ZIPCODE_V2"
     *       - version = 2
     *       - headerSize = 0
     *       - recordSizeIntegerBytes = 4
     *       - sizeFormatType = "binary"
     *       - sizeOfSizes = 4
     *       - sizeInclusionFlag = false
     *       - primaryKeyIndexFileName = ""
     *       - recordCount = 0
     *       - fieldCount = 0
     *       - primaryKeyFieldIndex = -1
     * @return A DataFileHeader instance with default values
     */
    DataFileHeader();

    /**
     * @brief Parameterized constructor
     * @param structType File structure type
     * @param ver Version number
     * @pre structType is a non-empty string, ver > 0
     * @post DataFileHeader is initialized with specified values and defaults for other fields
     * @return A DataFileHeader instance with specified file structure type and version
     */
    DataFileHeader(const std::string &structType, int ver);

    /**
     * @brief Pack header into a byte buffer
     * @param buffer Output buffer (must be large enough to hold packed header)
     * @pre buffer is a valid pointer to memory of at least getPackedSize() bytes
     * @post Header data is written to buffer in binary format
     * @return Number of bytes written to buffer
     */
    size_t pack(char *buffer) const;

    /**
     * @brief Unpack header from a byte buffer
     * @param buffer Input buffer containing packed header data
     * @pre buffer contains valid packed header data
     * @post Header fields are populated from buffer data
     * @return Number of bytes read from buffer
     */
    size_t unpack(const char *buffer);

    /**
     * @brief Get the size of the packed header
     * @pre None
     * @post Returns the total size needed to pack this header
     * @return Header size in bytes
     */
    size_t getPackedSize() const;

    /**
     * @brief Add a field descriptor
     * @param name Field name
     * @param typeSchema Field type
     * @param isPrimaryKey True if primary key
     * @pre name and typeSchema are valid strings
     * @post Field is added to fields vector, fieldCount is updated, primaryKeyFieldIndex updated if isPrimaryKey true
     * @return None
     */
    void addField(const std::string &name, const std::string &typeSchema, bool isPrimaryKey = false);

    /**
     * @brief Write header to a file
     * @param filename Output filename
     * @pre filename is a valid file path
     * @post Header is written to specified file in binary format
     * @return true if successful, false otherwise
     */
    bool writeToFile(const std::string &filename) const;

    /**
     * @brief Read header from a file
     * @param filename Input filename
     * @pre filename is a valid file path containing a valid header
     * @post Header fields are populated from file data
     * @return true if successful, false otherwise
     */
    bool readFromFile(const std::string &filename);

    /**
     * @brief Display header information
     * @pre None
     * @post Header contents are printed to standard output
     * @return None
     */
    void display() const;

    // Getters and setters with Doxygen comments

    /**
     * @brief Set file structure type
     * @param type File structure type string
     * @pre type is a non-empty string
     * @post fileStructureType is set to type
     * @return None
     */
    void setFileStructureType(const std::string &type) { fileStructureType = type; }

    /**
     * @brief Get file structure type
     * @pre None
     * @post Returns current fileStructureType
     * @return File structure type string
     */
    std::string getFileStructureType() const { return fileStructureType; }

    /**
     * @brief Set version
     * @param v Version number
     * @pre v > 0
     * @post version is set to v
     * @return None
     */
    void setVersion(int v) { version = v; }

    /**
     * @brief Get version
     * @pre None
     * @post Returns current version
     * @return Version number
     */
    int getVersion() const { return version; }

    /**
     * @brief Set header size
     * @param size Header size in bytes
     * @pre size > 0
     * @post headerSize is set to size
     * @return None
     */
    void setHeaderSize(int size) { headerSize = size; }

    /**
     * @brief Get header size
     * @pre None
     * @post Returns current headerSize
     * @return Header size in bytes
     */
    int getHeaderSize() const { return headerSize; }

    /**
     * @brief Set record size integer bytes
     * @param bytes Number of bytes for record size field
     * @pre bytes > 0
     * @post recordSizeIntegerBytes is set to bytes
     * @return None
     */
    void setRecordSizeIntegerBytes(int bytes) { recordSizeIntegerBytes = bytes; }

    /**
     * @brief Get record size integer bytes
     * @pre None
     * @post Returns current recordSizeIntegerBytes
     * @return Number of bytes for record size field
     */
    int getRecordSizeIntegerBytes() const { return recordSizeIntegerBytes; }

    /**
     * @brief Set size format type
     * @param type Size format type ("ASCII" or "binary")
     * @pre type is either "ASCII" or "binary"
     * @post sizeFormatType is set to type
     * @return None
     */
    void setSizeFormatType(const std::string &type) { sizeFormatType = type; }

    /**
     * @brief Get size format type
     * @pre None
     * @post Returns current sizeFormatType
     * @return Size format type string
     */
    std::string getSizeFormatType() const { return sizeFormatType; }

    /**
     * @brief Set size of sizes
     * @param size Bytes to represent size
     * @pre size > 0
     * @post sizeOfSizes is set to size
     * @return None
     */
    void setSizeOfSizes(int size) { sizeOfSizes = size; }

    /**
     * @brief Get size of sizes
     * @pre None
     * @post Returns current sizeOfSizes
     * @return Bytes to represent size
     */
    int getSizeOfSizes() const { return sizeOfSizes; }

    /**
     * @brief Set size inclusion flag
     * @param flag True if size includes itself
     * @pre None
     * @post sizeInclusionFlag is set to flag
     * @return None
     */
    void setSizeInclusionFlag(bool flag) { sizeInclusionFlag = flag; }

    /**
     * @brief Get size inclusion flag
     * @pre None
     * @post Returns current sizeInclusionFlag
     * @return True if size includes itself
     */
    bool getSizeInclusionFlag() const { return sizeInclusionFlag; }

    /**
     * @brief Set primary key index file name
     * @param name Index file name
     * @pre name is a valid string
     * @post primaryKeyIndexFileName is set to name
     * @return None
     */
    void setPrimaryKeyIndexFileName(const std::string &name) { primaryKeyIndexFileName = name; }

    /**
     * @brief Get primary key index file name
     * @pre None
     * @post Returns current primaryKeyIndexFileName
     * @return Index file name
     */
    std::string getPrimaryKeyIndexFileName() const { return primaryKeyIndexFileName; }

    /**
     * @brief Set record count
     * @param count Number of records
     * @pre count >= 0
     * @post recordCount is set to count
     * @return None
     */
    void setRecordCount(int count) { recordCount = count; }

    /**
     * @brief Get record count
     * @pre None
     * @post Returns current recordCount
     * @return Number of records in file
     */
    int getRecordCount() const { return recordCount; }

    /**
     * @brief Set field count
     * @param count Number of fields per record
     * @pre count >= 0
     * @post fieldCount is set to count
     * @return None
     */
    void setFieldCount(int count) { fieldCount = count; }

    /**
     * @brief Get field count
     * @pre None
     * @post Returns current fieldCount
     * @return Number of fields per record
     */
    int getFieldCount() const { return fieldCount; }

    /**
     * @brief Get fields
     * @pre None
     * @post Returns const reference to fields vector
     * @return Const reference to vector of FieldDescriptor
     */
    const std::vector<FieldDescriptor> &getFields() const { return fields; }

    /**
     * @brief Set primary key field index
     * @param index Index of primary key field
     * @pre index >= -1 and index < fieldCount
     * @post primaryKeyFieldIndex is set to index
     * @return None
     */
    void setPrimaryKeyFieldIndex(int index) { primaryKeyFieldIndex = index; }

    /**
     * @brief Get primary key field index
     * @pre None
     * @post Returns current primaryKeyFieldIndex
     * @return Index of primary key field (-1 if none)
     */
    int getPrimaryKeyFieldIndex() const { return primaryKeyFieldIndex; }
};

#endif // DATAFILEHEADER_H