/**
 * @file array.cpp
 * @brief Implementation file for the Array class with bounds checking
 * @date 01/28/2026
 * @author Chidera Izuora
 * @version 1.0
 *
 * @class Array
 * @brief Dynamic integer array class with bounds checking and I/O operators
 * Array class: like an int array (retains all functionality) but also
 * includes additional features:
 *   -- allows input and output of the whole array
 *   -- allows for comparison of 2 arrays, element by element
 *   -- allows for assignment of 2 arrays
 *   -- size is part of the class (so no longer needs to be passed)
 *   -- includes range checking, program terminates for out-of-bound subscripts
 *
 * Assumptions:
 *   -- size defaults to a fixed size of 10 if size is not specified
 *   -- array elements are initialized to zero
 *   -- user must enter valid integers when using >>
 *   -- in <<, integers are displayed 10 per line
 */

#include "array.h"
#include <cassert>

// Initialize static data member at file scope
int Array::arrayCount = 0;

//---------------------------------------------------------------------------
/**
 * @brief Default constructor
 * @param[in] arraySize Initial size of the array
 * @pre None
 * @post ptr points to an array of size arraySize and all
 *       elements of the array have been initialized to zero.
 *       arrayCount is incremented.
 *       Negative input values result in the default size of 10
 * @return Newly constructed Array object
 * @note Uses assert to ensure memory allocation succeeds
 * @callgraph
 */
Array::Array(int arraySize)
{
    ++arrayCount;
    size = (arraySize > 0 ? arraySize : 10);
    ptr = new int[size];
    assert(ptr != NULL);

    for (int i = 0; i < size; i++)
        ptr[i] = 0;
}

//---------------------------------------------------------------------------
/**
 * @brief Copy constructor
 * @param[in] init Array to copy from
 * @pre init.ptr points to an array of size at least init.size
 * @post init is copied into *this, arrayCount is incremented
 * @return Newly constructed Array object as a copy of init
 * @note Creates deep copy of the array
 * @callgraph
 */
Array::Array(const Array &init)
{
    ++arrayCount;
    size = init.size;
    ptr = new int[size];
    assert(ptr != NULL);

    for (int i = 0; i < size; i++)
        ptr[i] = init.ptr[i];
}

//---------------------------------------------------------------------------
/**
 * @brief Destructor
 * @pre ptr points to memory on the heap
 * @post Array for ptr is deallocated, arrayCount is decremented
 * @return None
 * @note Automatically called when object goes out of scope
 */
Array::~Array()
{
    --arrayCount;
    delete[] ptr;
}

//----------------------------- getSize -------------------------------------
/**
 * @brief Get the size of the array
 * @pre None
 * @post Returns the size of the array
 * @return Size of the array
 */
int Array::getSize() const { return size; }

//---------------------------------------------------------------------------
/**
 * @brief Assignment operator
 * @param[in] right Array to assign from
 * @pre right.ptr points to an array of size at least right.size
 * @post *this is assigned the same array as right
 * @return Reference to *this
 * @note Handles self-assignment and creates deep copy
 * @callgraph
 */
const Array &Array::operator=(const Array &right)
{
    if (&right != this)
    {
        delete[] ptr;
        size = right.size;
        ptr = new int[size];
        assert(ptr != NULL);

        for (int i = 0; i < size; i++)
            ptr[i] = right.ptr[i];
    }

    return *this;
}

//---------------------------------------------------------------------------
/**
 * @brief Equality operator
 * @param[in] right Array to compare with
 * @pre ptr and right.ptr point to arrays with size at least
 *      size and right.size, respectively
 * @post true is returned if the arrays have the same size and
 *       elements false is return otherwise
 * @return true if arrays are equal, false otherwise
 * @test Test with arrays of different sizes and contents
 */
bool Array::operator==(const Array &right) const
{
    if (size != right.size)
        return false;

    for (int i = 0; i < size; i++)
        if (ptr[i] != right.ptr[i])
            return false;
    return true;
}

//---------------------------------------------------------------------------
/**
 * @brief Inequality operator
 * @param[in] right Array to compare with
 * @pre ptr and right.ptr point to arrays with size at least
 *      size and right.size, respectively
 * @post false is returned if the arrays have the same size and
 *       elements true is return otherwise
 * @return true if arrays are not equal, false otherwise
 * @remark Uses operator== for implementation
 */
bool Array::operator!=(const Array &right) const
{
    return !(*this == right);
}

//---------------------------------------------------------------------------
/**
 * @brief Subscript operator
 * @param[in] subscript Index to access
 * @pre 0 <= subscript < size
 * @post Returns the array value at position "subscript"
 * @return Reference to array element at given index
 * @note Terminates program if subscript out of range
 * @callergraph
 */
int &Array::operator[](int subscript)
{
    assert(0 <= subscript && subscript < size);
    return ptr[subscript];
}

//---------------------------------------------------------------------------
/**
 * @brief Get the number of Array objects instantiated
 * @pre None
 * @post Returns the number of arrays
 * @return Number of Array objects currently instantiated
 * @note Static member function
 */
int Array::getArrayCount() { return arrayCount; }

//---------------------------------------------------------------------------
/**
 * @brief Overloaded input operator for class Array
 * @param[in,out] input Input stream
 * @param[in,out] a Array to read into
 * @pre a.ptr must point to an array with size at least a.size
 * @post The first a.size elements of a.ptr are filled with
 *       integers read from the input istream
 * @return Reference to the input stream
 * @note Reads exactly a.size integers from the stream
 * @relatesalso Array
 */
istream &operator>>(istream &input, Array &a)
{
    for (int i = 0; i < a.size; i++)
        input >> a.ptr[i];
    return input;
}

//---------------------------------------------------------------------------
/**
 * @brief Overloaded output operator for class Array
 * @param[in,out] output Output stream
 * @param[in] a Array to output
 * @pre a.ptr must point to an array with size at least a.size
 * @post The first a.size elements of a.ptr are sent to the
 *       output istream 10 per line with a trailing endl
 * @return Reference to the output stream
 * @note Outputs 10 integers per line
 * @relatesalso Array
 */
ostream &operator<<(ostream &output, const Array &a)
{
    int i;
    for (i = 0; i < a.size; i++)
    {
        output << a.ptr[i] << ' ';
        if ((i + 1) % 10 == 0)
            output << endl;
    }

    if (i % 10 != 0)
        output << endl;
    return output;
}