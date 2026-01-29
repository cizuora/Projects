/**
 * @file arraydriver.cpp
 * @brief Driver program to test the Array class
 * @date 01/28/2026
 * @author Chidera Izuora
 * @version 1.0
 *
 * @class Array
 * @brief Driver program for the Array class
 * This program tests the functionality of the Array class including:
 * - Construction and destruction
 * - Input and output operators
 * - Comparison operators (== and !=)
 * - Assignment operator
 * - Subscript operator with bounds checking
 * - Static member function for counting instances
 * 
 * @note Ensure to provide valid integer input when prompted
 * @test Comprehensive test of Array class features
 */

#include "array.h"

/**
 * @brief Main function to test Array class
 * @pre None
 * @post Tests all Array class functionality
 * @return 0 on successful execution
 * @test Comprehensive test of Array class features
 */
int main() {
   // no objects yet
   cout << "# of arrays instantiated = "
        << Array::getArrayCount() << endl;

   // create two arrays and print Array count
   Array integers1(7), integers2;
   cout << "# of arrays instantiated = "
        << Array::getArrayCount() << endl << endl;

   // print integers1 size and contents
   cout << "Size of array integers1 is " << integers1.getSize() << endl
        << "Array after initialization:" << endl << integers1 << endl;

   // print integers2 size and contents
   cout << "Size of array integers2 is " << integers2.getSize() << endl
        << "Array after initialization:" << endl << integers2 << endl;

   // input and print integers1 and integers2
   cout << "Input 17 integers:" << endl;
   cin >> integers1 >> integers2;
   cout << "After input, the arrays contain:" << endl
        << "integers1: " << integers1
        << "integers2: " << integers2 << endl;

   // use overloaded inequality (!=) operator
   cout << "Evaluating: integers1 != integers2" << endl;
   if (integers1 != integers2)
      cout << "They are not equal" << endl;

   // create array integers3 using integers1 as an
   // initializer; print size and contents
   Array integers3(integers1);

   cout << endl << "Size of array integers3 is " << integers3.getSize() << endl
        << "Array after initialization:" << endl << integers3 << endl;

   // use overloaded assignment (=) operator
   cout << "Assigning integers2 to integers1:" << endl;
   integers1 = integers2;
   cout << "integers1: " << integers1
        << "integers2: " << integers2 << endl;

   // use overloaded equality (==) operator
   cout << "Evaluating: integers1 == integers2" << endl;
   if (integers1 == integers2)
      cout << "They are equal" << endl << endl;

   // use overloaded subscript operator to create rvalue
   cout << "integers1[5] is " << integers1[5] << endl;

   // use overloaded subscript operator to create lvalue
   cout << "Assigning 1000 to integers1[5]" << endl;
   integers1[5] = 1000;
   cout << "integers1: " << integers1 << endl;

   // attempt to use out of range subscript
   cout << endl << "Attempt to assign 1000 to integers1[15]" << endl;
   integers1[15] = 1000;                           // ERROR: out of range

   return 0;
}