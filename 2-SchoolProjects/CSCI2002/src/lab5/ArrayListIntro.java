package lab5;

import java.util.ArrayList;
import java.util.Collections;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2001
Purpose    : Lab 5
=================================*/

public class ArrayListIntro {
 public static void main(String[] args) {
 // Task 1: Create and populate an ArrayList
 ArrayList<Integer> numbers = new ArrayList<>();
 numbers.add(10);
 numbers.add(20);
 numbers.add(30);
 numbers.add(40);
 numbers.add(50);
 // add other numbers
 System.out.println("Original ArrayList: " + numbers);

 // Task 2: Update and Remove Elements
 numbers.set(1, 25);  // Update index 1 (second element)
 numbers.remove(numbers.size() - 1); // Remove last element

 System.out.println("Updated ArrayList: " + numbers);
 
 
 // Task 3: Iterate Over the ArrayList
//Regular for loop
System.out.print("Elements: ");
for (int i = 0; i < numbers.size(); i++) {
  System.out.print(numbers.get(i) + " ");
}
System.out.println();

//Enhanced for loop for sum calculation
int sum = 0;
for (int num : numbers) {
  sum += num;
}
System.out.println("Sum of elements: " + sum);
 
 // Task 4: Sorting and Searching
//Sorting in ascending order
Collections.sort(numbers);
System.out.println("Sorted ArrayList: " + numbers);

//Searching for 25
boolean exists = numbers.contains(25);
System.out.println("Does 25 exist? " + exists);
 }
}

