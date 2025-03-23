package lab3;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-02-2025
Course     : CS2001
Purpose    : Lab 3 
=================================*/

public class MathOperations {

    // Method to multiply two integers
    public int multiply(int a, int b) {
        return a * b;
    }

    // Method to multiply two doubles
    public double multiply(double a, double b) {
        return a * b;
    }

    // Method to multiply three integers
    public int multiply(int a, int b, int c) {
        return a * b * c;
    }

    public static void main(String[] args) {
        MathOperations math = new MathOperations();

        // Testing overloaded methods
        System.out.println("Product of two integers: " + math.multiply(4, 5));
        System.out.println("Product of two doubles: " + math.multiply(3.5, 3.5));
        System.out.println("Product of three integers: " + math.multiply(3, 4, 5));
    }
}


