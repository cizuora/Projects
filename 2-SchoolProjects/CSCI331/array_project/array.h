/**
 * @file array.h
 * @brief Header file for the Array class with bounds checking
 * @date 01/28/2026
 * @author Chidera Izuora
 * @version 1.0
 * 
 * @class Array
 * @brief Dynamic integer array class with bounds checking and I/O operators
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

class Array {
    /**
     * @brief Overloaded input operator for class Array
     * @param[in,out] input Input stream
     * @param[in,out] a Array to read into
     * @return Reference to the input stream
     * @pre a.ptr must point to an array with size at least a.size
     * @post The first a.size elements of a.ptr are filled with integers
     * @note Reads exactly a.size integers from the stream
     * @test Test with valid integer input
     */
    friend istream& operator>>(istream &input, Array &a);

    /**
     * @brief Overloaded output operator for class Array
     * @param[in,out] output Output stream
     * @param[in] a Array to output
     * @return Reference to the output stream
     * @pre a.ptr must point to an array with size at least a.size
     * @post The first a.size elements of a.ptr are sent to output stream
     * @note Outputs 10 integers per line with trailing newline
     * @test Test output formatting with various array sizes
     */
    friend ostream& operator<<(ostream &output, const Array &a);

public:
    /**
     * @brief Default constructor for Array class
     * @param[in] arraySize Initial size of the array (defaults to 10)
     * @pre None
     * @post ptr points to array of size arraySize, all elements zero,
     *       arrayCount is incremented
     * @return Newly constructed Array object
     * @note Negative input values result in the default size of 10
     * @test Test with positive, negative, and zero sizes
     * @callgraph
     */
    Array(int arraySize = 10); 

    /**
     * @brief Copy constructor for Array class
     * @param[in] init Array to copy from
     * @pre init.ptr points to an array of size at least init.size
     * @post init is copied into *this, arrayCount is incremented
     * @return Newly constructed Array object as a copy of init
     * @note Creates deep copy of the array
     * @test Test copying arrays of various sizes
     */
    Array(const Array &init); 

    /**
     * @brief Destructor for Array class
     * @pre ptr points to memory on the heap
     * @post Array for ptr is deallocated, arrayCount is decremented
     * @return None
     * @note Automatically called when Array object goes out of scope
     */
    ~Array(); 

    /**
     * @brief Get the size of the array
     * @pre None
     * @post Returns the size of the array
     * @return Current size of the array
     * @test Verify size matches what was specified during construction
     */
    int getSize() const; 

    /**
     * @brief Assignment operator for Array class
     * @param[in] right Array to assign from
     * @pre right.ptr points to an array of size at least right.size
     * @post *this is assigned the same array as right
     * @return Reference to the assigned array
     * @note Self-assignment is checked and handled properly
     * @test Test assignment between arrays of different sizes
     * @callgraph
     */
    const Array& operator=(const Array &right); 

    /**
     * @brief Equality comparison operator
     * @param[in] right Array to compare with
     * @pre ptr and right.ptr point to arrays with size at least
     *      size and right.size, respectively
     * @post true is returned if the arrays have the same size and 
     *       elements, false otherwise
     * @return true if arrays are equal, false otherwise
     * @test Test with equal and unequal arrays
     */
    bool operator==(const Array &right) const; 

    /**
     * @brief Inequality comparison operator
     * @param[in] right Array to compare with
     * @pre ptr and right.ptr point to arrays with size at least
     *      size and right.size, respectively
     * @post false is returned if the arrays have the same size and 
     *       elements, true otherwise
     * @return true if arrays are not equal, false otherwise
     * @test Test with equal and unequal arrays
     * @remark Uses operator== for implementation
     */
    bool operator!=(const Array &right) const;

    /**
     * @brief Subscript operator for array access
     * @param[in] subscript Index to access
     * @pre 0 <= subscript < size
     * @post Returns the array value at position "subscript"
     * @return Reference to array element at given index
     * @note Terminates program if subscript is out of range
     * @test Test valid and invalid indices
     * @callergraph
     */
    int& operator[](int subscript); 

    /**
     * @brief Get the number of Array objects instantiated
     * @pre None
     * @post Returns the number of arrays
     * @return Count of Array objects currently instantiated
     * @note Static member function
     * @test Verify count increases with construction and decreases with destruction
     */
    static int getArrayCount(); 

private:
    int* ptr;                          ///< pointer to first element of array
    int size;                          ///< size of the array
    static int arrayCount;             ///< # of Arrays instantiated (static counter)
};

#endif