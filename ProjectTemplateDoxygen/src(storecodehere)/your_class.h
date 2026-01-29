/**
 * @file your_class.h
 * @brief Brief description of your class
 * @author Your Name
 * @date YYYY-MM-DD
 * @version 1.0
 * 
 * @class YourClass
 * @brief Detailed description of your class
 * 
 * Longer description explaining what the class does,
 * its features, and any important implementation details.
 * 
 * Assumptions:
 *   -- Assumption 1
 *   -- Assumption 2
 *   -- Assumption 3
 */

#ifndef YOUR_CLASS_H
#define YOUR_CLASS_H

#include <iostream>
using namespace std;

class YourClass {
    // Friend functions (if any)
    
public:
    /**
     * @brief Default constructor
     * @param[in] param Description of parameter
     * @pre Precondition
     * @post Postcondition
     * @note Any important notes
     * @test Test cases
     */
    YourClass(int param = 0);
    
    /**
     * @brief Copy constructor
     * @param[in] other Object to copy from
     */
    YourClass(const YourClass& other);
    
    /**
     * @brief Destructor
     */
    ~YourClass();
    
    /**
     * @brief Getter method
     * @pre Precondition
     * @post Postcondition
     * @return Description of return value
     */
    int getValue() const;
    
    /**
     * @brief Setter method
     * @param[in] newValue New value to set
     * @pre Precondition
     * @post Postcondition
     */
    void setValue(int newValue);
    
    /**
     * @brief Operator overload
     * @param[in] rhs Right-hand side object
     * @return Result of operation
     */
    bool operator==(const YourClass& rhs) const;
    
private:
    int value;              ///< Description of private member
    static int count;       ///< Static counter description
};

#endif