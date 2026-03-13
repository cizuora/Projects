/**
 * @file DataFileHeader.cpp
 * @brief Implementation of DataFileHeader class
 * @author CSCI 331 Team 2
 * @date 03/13/2026
 */

#include "DataFileHeader.h"

/**
 * @brief Default constructor implementation
 * @pre None
 * @post All fields are initialized to default values as specified in header
 */
DataFileHeader::DataFileHeader() 
    : fileStructureType("ZIPCODE_V2")
    , version(2)
    , headerSize(0)
    , recordSizeIntegerBytes(4)
    , sizeFormatType("binary")
    , sizeOfSizes(4)
    , sizeInclusionFlag(false)
    , primaryKeyIndexFileName("")
    , recordCount(0)
    , fieldCount(0)
    , primaryKeyFieldIndex(-1) {
}

/**
 * @brief Parameterized constructor implementation
 * @param structType File structure type
 * @param ver Version number
 * @pre structType is a non-empty string, ver > 0
 * @post File structure type and version are set, other fields have default values
 */
DataFileHeader::DataFileHeader(const std::string& structType, int ver)
    : fileStructureType(structType)
    , version(ver)
    , headerSize(0)
    , recordSizeIntegerBytes(4)
    , sizeFormatType("binary")
    , sizeOfSizes(4)
    , sizeInclusionFlag(false)
    , primaryKeyIndexFileName("")
    , recordCount(0)
    , fieldCount(0)
    , primaryKeyFieldIndex(-1) {
}

/**
 * @brief Calculate the packed size of the header
 * @pre None
 * @post Size is calculated based on current field values
 * @return Total size needed to pack this header in bytes
 */
size_t DataFileHeader::getPackedSize() const {
    size_t size = 0;
    
    // Integer fields (7 integers)
    size += sizeof(int) * 7;
    
    // Boolean field
    size += sizeof(bool);
    
    // Strings with null terminators
    size += fileStructureType.length() + 1;
    size += sizeFormatType.length() + 1;
    size += primaryKeyIndexFileName.length() + 1;
    
    // Fields data
    for (const auto& field : fields) {
        size += field.name.length() + 1;
        size += field.typeSchema.length() + 1;
        size += sizeof(bool); // isPrimaryKey
    }
    
    return size;
}

/**
 * @brief Pack header into a byte buffer
 * @param buffer Output buffer
 * @pre buffer is a valid pointer to memory of at least getPackedSize() bytes
 * @post Header data is written to buffer in binary format
 * @return Number of bytes written to buffer
 */
size_t DataFileHeader::pack(char* buffer) const {
    char* ptr = buffer;
    
    // Pack integer fields
    memcpy(ptr, &version, sizeof(version));
    ptr += sizeof(version);
    
    memcpy(ptr, &headerSize, sizeof(headerSize));
    ptr += sizeof(headerSize);
    
    memcpy(ptr, &recordSizeIntegerBytes, sizeof(recordSizeIntegerBytes));
    ptr += sizeof(recordSizeIntegerBytes);
    
    memcpy(ptr, &sizeOfSizes, sizeof(sizeOfSizes));
    ptr += sizeof(sizeOfSizes);
    
    memcpy(ptr, &recordCount, sizeof(recordCount));
    ptr += sizeof(recordCount);
    
    memcpy(ptr, &fieldCount, sizeof(fieldCount));
    ptr += sizeof(fieldCount);
    
    memcpy(ptr, &primaryKeyFieldIndex, sizeof(primaryKeyFieldIndex));
    ptr += sizeof(primaryKeyFieldIndex);
    
    // Pack boolean
    memcpy(ptr, &sizeInclusionFlag, sizeof(sizeInclusionFlag));
    ptr += sizeof(sizeInclusionFlag);
    
    // Pack strings
    strcpy(ptr, fileStructureType.c_str());
    ptr += fileStructureType.length() + 1;
    
    strcpy(ptr, sizeFormatType.c_str());
    ptr += sizeFormatType.length() + 1;
    
    strcpy(ptr, primaryKeyIndexFileName.c_str());
    ptr += primaryKeyIndexFileName.length() + 1;
    
    // Pack fields
    for (const auto& field : fields) {
        strcpy(ptr, field.name.c_str());
        ptr += field.name.length() + 1;
        
        strcpy(ptr, field.typeSchema.c_str());
        ptr += field.typeSchema.length() + 1;
        
        memcpy(ptr, &field.isPrimaryKey, sizeof(field.isPrimaryKey));
        ptr += sizeof(field.isPrimaryKey);
    }
    
    return ptr - buffer;
}

/**
 * @brief Unpack header from a byte buffer
 * @param buffer Input buffer containing packed header data
 * @pre buffer contains valid packed header data
 * @post Header fields are populated from buffer data
 * @return Number of bytes read from buffer
 */
size_t DataFileHeader::unpack(const char* buffer) {
    const char* ptr = buffer;
    
    // Unpack integer fields
    memcpy(&version, ptr, sizeof(version));
    ptr += sizeof(version);
    
    memcpy(&headerSize, ptr, sizeof(headerSize));
    ptr += sizeof(headerSize);
    
    memcpy(&recordSizeIntegerBytes, ptr, sizeof(recordSizeIntegerBytes));
    ptr += sizeof(recordSizeIntegerBytes);
    
    memcpy(&sizeOfSizes, ptr, sizeof(sizeOfSizes));
    ptr += sizeof(sizeOfSizes);
    
    memcpy(&recordCount, ptr, sizeof(recordCount));
    ptr += sizeof(recordCount);
    
    memcpy(&fieldCount, ptr, sizeof(fieldCount));
    ptr += sizeof(fieldCount);
    
    memcpy(&primaryKeyFieldIndex, ptr, sizeof(primaryKeyFieldIndex));
    ptr += sizeof(primaryKeyFieldIndex);
    
    // Unpack boolean
    memcpy(&sizeInclusionFlag, ptr, sizeof(sizeInclusionFlag));
    ptr += sizeof(sizeInclusionFlag);
    
    // Unpack strings
    fileStructureType = ptr;
    ptr += fileStructureType.length() + 1;
    
    sizeFormatType = ptr;
    ptr += sizeFormatType.length() + 1;
    
    primaryKeyIndexFileName = ptr;
    ptr += primaryKeyIndexFileName.length() + 1;
    
    // Unpack fields
    fields.clear();
    for (int i = 0; i < fieldCount; i++) {
        FieldDescriptor field;
        
        field.name = ptr;
        ptr += field.name.length() + 1;
        
        field.typeSchema = ptr;
        ptr += field.typeSchema.length() + 1;
        
        memcpy(&field.isPrimaryKey, ptr, sizeof(field.isPrimaryKey));
        ptr += sizeof(field.isPrimaryKey);
        
        fields.push_back(field);
        
        if (field.isPrimaryKey) {
            primaryKeyFieldIndex = i;
        }
    }
    
    return ptr - buffer;
}

/**
 * @brief Add a field descriptor to the header
 * @param name Field name
 * @param typeSchema Field type
 * @param isPrimaryKey True if primary key
 * @pre name and typeSchema are valid non-empty strings
 * @post Field is added to fields vector, fieldCount is incremented, 
 *       primaryKeyFieldIndex is updated if isPrimaryKey is true
 * @return None
 */
void DataFileHeader::addField(const std::string& name, const std::string& typeSchema, bool isPrimaryKey) {
    fields.push_back(FieldDescriptor(name, typeSchema, isPrimaryKey));
    fieldCount = fields.size();
    
    if (isPrimaryKey) {
        primaryKeyFieldIndex = fields.size() - 1;
    }
}

/**
 * @brief Write header to a file
 * @param filename Output filename
 * @pre filename is a valid file path with write permissions
 * @post Header is written to specified file in binary format
 * @return true if successful, false if file cannot be opened or write fails
 */
bool DataFileHeader::writeToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot write header to " << filename << std::endl;
        return false;
    }
    
    size_t size = getPackedSize();
    char* buffer = new char[size];
    size_t written = pack(buffer);
    
    file.write(buffer, written);
    delete[] buffer;
    
    return file.good();
}

/**
 * @brief Read header from a file
 * @param filename Input filename
 * @pre filename is a valid file path containing a valid header
 * @post Header fields are populated from file data
 * @return true if successful, false if file cannot be opened or read fails
 */
bool DataFileHeader::readFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot read header from " << filename << std::endl;
        return false;
    }
    
    // Get file size
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    char* buffer = new char[size];
    file.read(buffer, size);
    
    size_t read = unpack(buffer);
    delete[] buffer;
    
    return file.good() && read > 0;
}

/**
 * @brief Display header information
 * @pre None
 * @post Header contents are printed to standard output in a formatted way
 * @return None
 */
void DataFileHeader::display() const {
    std::cout << "==========================================" << std::endl;
    std::cout << "Data File Header Information" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "File Structure Type: " << fileStructureType << std::endl;
    std::cout << "Version: " << version << std::endl;
    std::cout << "Header Size: " << headerSize << " bytes" << std::endl;
    std::cout << "Record Size Integer Bytes: " << recordSizeIntegerBytes << std::endl;
    std::cout << "Size Format Type: " << sizeFormatType << std::endl;
    std::cout << "Size of Sizes: " << sizeOfSizes << std::endl;
    std::cout << "Size Inclusion Flag: " << (sizeInclusionFlag ? "true" : "false") << std::endl;
    std::cout << "Primary Key Index File: " << primaryKeyIndexFileName << std::endl;
    std::cout << "Record Count: " << recordCount << std::endl;
    std::cout << "Field Count: " << fieldCount << std::endl;
    std::cout << "Primary Key Field Index: " << primaryKeyFieldIndex << std::endl;
    
    std::cout << "\nFields:" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    for (size_t i = 0; i < fields.size(); i++) {
        std::cout << "  [" << i << "] " << std::left << std::setw(15) << fields[i].name 
                  << " (" << std::setw(8) << fields[i].typeSchema << ")" 
                  << (fields[i].isPrimaryKey ? " [PRIMARY KEY]" : "") << std::endl;
    }
    std::cout << "==========================================" << std::endl;
}