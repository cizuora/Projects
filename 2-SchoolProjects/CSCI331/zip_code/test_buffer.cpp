/**
 * @file test_buffer.cpp
 * @brief Test program for ZipCodeBuffer class
 * @author [Your Name]
 * @date [Date]
 */

#include <iostream>
#include <iomanip>
#include "ZipCodeBuffer.h"

using namespace std;

int main() {
    cout << "=====================================" << endl;
    cout << "  ZipCodeBuffer Class Test Program  " << endl;
    cout << "=====================================" << endl;
    cout << endl;
    
    // TODO: Change this to your CSV filename
    string filename = "us_postal_codes_by_zipcode.csv";
    
    cout << "Opening file: " << filename << endl;
    
    // Create buffer object
    ZipCodeBuffer buffer(filename);
    
    // Try to open the file
    if (!buffer.open()) {
        cerr << "ERROR: Failed to open file!" << endl;
        return 1;
    }
    
    cout << "File opened successfully!" << endl;
    cout << endl;
    
    // Read and display first 10 records
    cout << "Reading first 10 records..." << endl;
    cout << "------------------------------------------------------------" << endl;
    
    ZipCodeRecord record;
    int count = 0;
    int maxRecords = 10; // Change this to read more/fewer records
    
    while (buffer.getNextRecord(record) && count < maxRecords) {
        cout << "Record #" << (count + 1) << ":" << endl;
        cout << "  ZIP Code:   " << record.zipCode << endl;
        cout << "  Place:      " << record.placeName << endl;
        cout << "  State:      " << record.state << endl;
        cout << "  County:     " << record.county << endl;
        cout << "  Latitude:   " << fixed << setprecision(4) << record.latitude << endl;
        cout << "  Longitude:  " << fixed << setprecision(4) << record.longitude << endl;
        cout << endl;
        count++;
    }
    
    cout << "------------------------------------------------------------" << endl;
    cout << "Successfully read " << count << " records!" << endl;
    
    // Close the file
    buffer.close();
    cout << "File closed." << endl;
    
    // Optional: Test reading the entire file
    cout << endl;
    cout << "Would you like to count all records in the file? (y/n): ";
    char response;
    cin >> response;
    
    if (response == 'y' || response == 'Y') {
        if (buffer.open()) {
            int totalCount = 0;
            while (buffer.getNextRecord(record)) {
                totalCount++;
            }
            cout << "Total records in file: " << totalCount << endl;
            buffer.close();
        }
    }
    
    cout << endl;
    cout << "Test completed!" << endl;
    
    return 0;
}
