/**
 * @file array.cpp
 * @brief Member function definitions for class Array
 * @author Chidera Izuora
 * @date 01/28/2026
 * @version 1.0
 *
 * @details
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

/**
 * @brief Static member to keep track of the number of Array objects
 * @param None
 * @pre None
 * @post arrayCount is incremented/decremented in constructors/destructor
 * @return int
 */

int Array::arrayCount = 0;

/**
 * @brief Construct a new Array:: Array object
 * @param arraySize
 * @pre arraySize must be a positive integer
 * @post An Array object is created with size arraySize, elements initialized to zero, and
 * arrayCount incremented
 * @return None
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

/**
 * @brief Construct a new Array:: Array object  (copy constructor)
 * @param init
 * @pre init.ptr points to an array of size at least init.size
 * @post A new Array object is created as a copy of init, and arrayCount is incremented
 * @return None
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

/**
 * @brief Destroy the Array:: Array object
 * @param None
 * @pre None
 * @post arrayCount is decremented and dynamic memory allocated for ptr is deallocated
 * @return None
 */
Array::~Array()
{
    --arrayCount;
    delete[] ptr;
}

/**
 * @brief Get the Size object
 * @param None
 * @pre None
 * @post Returns the size of the array
 * @return int
 */
int Array::getSize() const { return size; }

/**
 * @brief
 * @param right
 * @pre right.ptr points to an array of size at least right.size
 * @post The current Array object is assigned the values of right, with dynamic memory
 * @return const Array&
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

/**
 * @brief  Determine if two arrays are equal.
 * @param right
 * @pre   ptr and right.ptr point to arrays with size at least
 *          size and right.size, respectively
 * @post  true is returned if the arrays have the same size and
 *          elements false is return otherwise
 * @return true
 * @return false
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

/**
 * @brief  Determine if two arrays are not equal.
 * @param right
 * @pre   ptr and right.ptr point to arrays with size at least
 *          size and right.size, respectively
 * @post  true is returned if the arrays differ in size or
 *          elements false is return otherwise
 * @return true
 * @return false
 */
bool Array::operator!=(const Array &right) const
{
    return !(*this == right);
}

/**
 * @brief  Subscript operator for class Array
 * @param subscript
 * @pre   0 <= subscript < size
 * @post  Returns a reference to the indexed element of the array
 * @return int&
 */
int &Array::operator[](int subscript)
{
    assert(0 <= subscript && subscript < size);
    return ptr[subscript];
}

/**
 * @brief Get the Array Count object
 * @param None
 * @pre None
 * @post Returns the current number of Array objects
 * @return int
 */
int Array::getArrayCount() { return arrayCount; }

/**
 * @brief
 * @param input
 * @param a
 * @pre   a.ptr must point to an array with size at least a.size
 * @post  The first a.size elements of a.ptr are filled from the input istream
 * @return istream&
 */
istream &operator>>(istream &input, Array &a)
{
    for (int i = 0; i < a.size; i++)
        input >> a.ptr[i];
    return input;
}

/**
 * @brief
 * @param output
 * @param a
 * @pre   a.ptr must point to an array with size at least a.size
 * @post  The elements of a.ptr are sent to the output istream, 10 per line
 * @return ostream&
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
