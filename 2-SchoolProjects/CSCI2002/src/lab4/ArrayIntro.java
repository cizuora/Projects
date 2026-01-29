package lab4;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2001
Purpose    : Lab 4
=================================*/

public class ArrayIntro {
    public static void main(String[] args) {
        // Task 1: Declare, construct, and initialize
        int[] numbers = {5, 10, 15, 20, 25};

        // Task 2: Access and Modify Array Elements
        System.out.println("First element: " + numbers[0]);
        System.out.println("Last element: " + numbers[numbers.length - 1]);

        // Update the second element to 50
        numbers[1] = 50;

        System.out.println("Updated array:");
        for (int num : numbers) {
            System.out.print(num + " ");
        }
        System.out.println();

        // Task 3: Loop through the array using a for loop
        System.out.println("Array elements:");
        for (int i = 0; i < numbers.length; i++) {
            System.out.println(numbers[i]);
        }

        // Enhanced for loop to compute sum
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        System.out.println("Sum of array elements: " + sum);

        // Task 4: Find the Maximum Value in the Array
        int max = numbers[0];
        for (int num : numbers) {
            if (num > max) {
                max = num;
            }
        }
        System.out.println("Maximum value in array: " + max);
    }
}

