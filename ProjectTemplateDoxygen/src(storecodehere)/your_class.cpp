/**
 * @file your_class.cpp
 * @brief Implementation of YourClass
 * @author Your Name
 * @date YYYY-MM-DD
 * @version 1.0
 * 
 * @details
 * Detailed implementation notes and assumptions.
 */

#include "your_class.h"

// Initialize static members
int YourClass::count = 0;

//---------------------------------------------------------------------------
/**
 * @brief Default constructor
 * @param[in] param Initial value
 * @pre None
 * @post Object is initialized with given value, count is incremented
 */
YourClass::YourClass(int param) : value(param) {
    ++count;
}

//---------------------------------------------------------------------------
/**
 * @brief Copy constructor
 * @param[in] other Object to copy from
 * @pre None
 * @post New object is copy of other, count is incremented
 */
YourClass::YourClass(const YourClass& other) : value(other.value) {
    ++count;
}

//---------------------------------------------------------------------------
/**
 * @brief Destructor
 * @pre Object exists
 * @post Object is destroyed, count is decremented
 */
YourClass::~YourClass() {
    --count;
}

//---------------------------------------------------------------------------
/**
 * @brief Get current value
 * @pre None
 * @post Returns current value
 * @return Current integer value
 */
int YourClass::getValue() const {
    return value;
}

//---------------------------------------------------------------------------
/**
 * @brief Set new value
 * @param[in] newValue New value to set
 * @pre None
 * @post Value is updated to newValue
 */
void YourClass::setValue(int newValue) {
    value = newValue;
}

//---------------------------------------------------------------------------
/**
 * @brief Equality operator
 * @param[in] rhs Right-hand side object
 * @pre None
 * @post Returns true if values are equal
 * @return True if equal, false otherwise
 */
bool YourClass::operator==(const YourClass& rhs) const {
    return value == rhs.value;
}