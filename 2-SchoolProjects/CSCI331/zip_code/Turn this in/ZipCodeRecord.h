/**
 * @file ZipCodeRecord.h
 * @brief Data structure for US Postal Code records
 * @author CSCI 331 Team 2
 * @date 02/12/2026
 * @version 1.0
 * 
 * @class ZipCodeRecord
 * @brief Structure to hold information for a single ZIP code
 * This header file defines the ZipCodeRecord structure, which is used to store information about US postal codes. Each record includes the ZIP code, place name, state, county, and geographic coordinates (latitude and longitude). This structure serves as the fundamental data unit for managing and processing ZIP code information in our application.
 */

#ifndef ZIPCODERECORD_H
#define ZIPCODERECORD_H

#include <string>

/**
 * @struct ZipCodeRecord
 * @brief Structure to hold information for a single ZIP code
 * @pre All fields must be properly initialized before use
 * @post Instances of ZipCodeRecord can be used to store and retrieve ZIP code information
 * @note This structure contains all fields from the US Postal Code database:
 * @note - ZIP code (5-digit postal code)
 * @note - Place name (city/town name)
 * @note - State (2-character state abbreviation)
 * @note - County name
 * @note - Geographic coordinates (latitude and longitude)
 * @note Longitude values are negative for locations west of the Prime Meridian
 * @note Latitude values are positive for locations north of the Equator
 */
struct ZipCodeRecord {
    int zipCode;              /**< 5-digit ZIP code */
    std::string placeName;    /**< City or town name */
    std::string state;        /**< 2-character state abbreviation */
    std::string county;       /**< County name */
    double latitude;          /**< Latitude in decimal degrees (positive for north of equator) */
    double longitude;         /**< Longitude in decimal degrees (negative for west of prime meridian) */
    
    /**
     * @brief Default constructor
     * @pre None
     * @post All fields are initialized to default values
     * @return An instance of ZipCodeRecord with default values
     * @note Initializes all numeric fields to zero and string fields to empty strings.
     */
    ZipCodeRecord() : zipCode(0), latitude(0.0), longitude(0.0) {}

    /**
     * @brief Parameterized constructor
     * @param zip ZIP code value
     * @param place Place name
     * @param st State abbreviation
     * @param cnty County name
     * @param lat Latitude coordinate
     * @param lon Longitude coordinate
     * @pre All parameters must be provided with valid values
     * @post An instance of ZipCodeRecord is created with the provided values
     * @return An instance of ZipCodeRecord initialized with specified values
     * @note This constructor allows for convenient initialization of all fields in one step.
     * @note The caller is responsible for ensuring that the provided values are valid (e.g., zip code is 5 digits, state is 2 characters, etc.).
     */
    ZipCodeRecord(int zip, const std::string& place, const std::string& st,
                  const std::string& cnty, double lat, double lon)
        : zipCode(zip), placeName(place), state(st), county(cnty), latitude(lat), longitude(lon) {} 
};

#endif // ZIPCODERECORD_H
