package lab3;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-02-2025
Course     : CS2001
Purpose    : Lab 3 
=================================*/
public class AreaCalculator {

    // Method to calculate the area of a circle
    public double calculateArea(double radius) {
        return 3.14 * radius * radius;
    }

    // Method to calculate the area of a rectangle
    public double calculateArea(double length, double breadth) {
        return length * breadth;
    }

    // Method to calculate the area of a square
    public int calculateArea(int side) {
        return side * side;
    }

    public static void main(String[] args) {
        AreaCalculator areaCalc = new AreaCalculator();

        // Testing overloaded methods
        System.out.println("Area of Circle: " + areaCalc.calculateArea(5.0));
        System.out.println("Area of Rectangle: " + areaCalc.calculateArea(4.0, 5.0));
        System.out.println("Area of Square: " + areaCalc.calculateArea(4));
    }
}

