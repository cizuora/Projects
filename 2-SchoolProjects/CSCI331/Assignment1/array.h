
/**
 * @file array.h
 * @brief Header file for the Array class
 * @author Chidera Izuora
 * @date 01/28/2026
 * @version 1.0
 *
 * @class Array
 * @brief Class representing a dynamic integer array with bounds checking
 *
 * Array class: like an int array (retains all functionality) but also
 * includes additional features:
 *   -- allows input and output of the whole array
 *   -- allows for comparison of 2 arrays, element by element
 *   -- allows for assignment of 2 arrays
 *   -- size is part of the class (so no longer needs to be passed)
 *   -- includes range checking, program terminates for out-of-bound subscripts
 *
 * Implementation and assumptions:
 *   -- size defaults to a fixed size of 10 if size is not specified
 *   -- array elements are initialized to zero
 *   -- user must enter valid integers when using >>
 *   -- in <<, integers are displayed 10 per line
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

class Array
{
    /**
     * @brief Overloaded input operator for class Array
     * @param[in,out] input Input stream
     * @param[in,out] a Array to read into
     * @pre a.ptr must point to an array with size at least a.size
     * @post The first a.size elements of a.ptr are filled from the input stream
     * @return Reference to the input stream
     */
    friend istream &operator>>(istream &, Array &);

    /**
     * @brief Overloaded output operator for class Array
     * @param[in,out] output Output stream
     * @param[in] a Array to write to the output stream
     * @pre a.ptr must point to an array with size at least a.size
     * @post The first a.size elements of a.ptr are sent to the output stream 10 per line with  * a trailing endl
     * @return Reference to the output stream
     */
    friend ostream &operator<<(ostream &, const Array &);

public:
    /** 
     * @brief Constructor for the Array class
     * @param[in] s Size of the array (default is 10)
     * @pre s must be a positive integer
     * @post An Array object is created with size s, elements initialized to zero, and
     * arrayCount incremented
     * @return None
     */
    Array(int = 10);

    /**
     * @brief Construct a new Array object  by copying another Array
     * @param[in] other Array to copy from
     * @pre other.ptr must point to an array with size at least other.size
     * @post A new Array object is created as a copy of other, with its own memory allocation
     * and arrayCount incremented
     * @return None
     */
    Array(const Array &);

    /**
     * @brief Destroy the Array object and free allocated memory
     * @param None
     * @pre ptr points to dynamically allocated memory
     * @post The memory allocated for the array is freed and arrayCount decremented
     * @return None
     */
    ~Array();

    /**
     * @brief Get the Size object
     * @param None
     * @pre None
     * @post The size of the array is returned
     * @return int
     */
    int getSize() const;

    /**
     * @brief Overloaded assignment operator for the Array class
     * @param[in] right Array to assign from
     * @pre right.ptr must point to an array with size at least right.size
     * @post The current Array object is assigned the values from right, with proper memory
     * management to avoid memory leaks
     * @return const Array&
     */
    const Array &operator=(const Array &);

    /**
     * @brief  Overloaded equality operator for the Array class
     * @pre ptr and right.ptr point to arrays with size at least size and right.size, respectively
     * @post true is returned if the arrays have the same size and elements, false otherwise
     * @return true
     * @return false
     */
    bool operator==(const Array &) const;

    /**
     * @brief  Overloaded inequality operator for the Array class
     * @pre ptr and right.ptr point to arrays with size at least size and right.size, respectively
     * @post true is returned if the arrays have different sizes or elements, false otherwise
     * @return true
     * @return false
     */
    bool operator!=(const Array &) const;

    /**
     * @brief Overloaded subscript operator for non-const Array objects
     * @param[in] index Index of the element to access
     * @pre 0 <= index < size
     * @post A reference to the element at the specified index is returned
     * @return int&
     */
    int &operator[](int);

    /**
     * @brief Overloaded subscript operator for const Array objects
     * @param[in] index Index of the element to access
     * @pre 0 <= index < size
     * @post A copy of the element at the specified index is returned
     * @return int
     */
    static int getArrayCount();

private:
    /**
     * @brief Pointer to the first element of the array
     * @pre None
     * @post ptr points to a dynamically allocated array of integers
     * @return None
     */
    int *ptr;

    /**
     * @brief  Size of the array
     * @pre None
     * @post size holds the number of elements in the array
     * @return None
     */
    int size;

    /** 
     * @brief Count of Array objects created
     * @pre None
     * @post arrayCount holds the number of Array instances currently in existence
     * @return None
     */
    static int arrayCount;
};

#endif
