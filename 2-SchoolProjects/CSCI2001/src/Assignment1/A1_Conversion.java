package Assignment1;

import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2001
Purpose    : Assignment 1
=================================*/

public class A1_Conversion {

    // Method to convert meters to kilometers
    public static void showKilometers(double meters, FileWriter writer) throws IOException {
        double kilometers = meters * 0.001;
        String result = String.format("%.2f meters is %.2f kilometers.%n", meters, kilometers);
        System.out.print(result);
        writer.write(result);
    }

    // Method to convert meters to inches
    public static void showInches(double meters, FileWriter writer) throws IOException {
        double inches = meters * 39.37;
        String result = String.format("%.2f meters is %.2f inches.%n", meters, inches);
        System.out.print(result);
        writer.write(result);
    }

    // Method to convert meters to feet
    public static void showFeet(double meters, FileWriter writer) throws IOException {
        double feet = meters * 3.281;
        String result = String.format("%.2f meters is %.2f feet.%n", meters, feet);
        System.out.print(result);
        writer.write(result);
    }

    // Method to display the menu
    public static void displayMenu(FileWriter writer) throws IOException {
        String menu = "\nConversion Menu:\n" +
                      "1. Convert to kilometers\n" +
                      "2. Convert to inches\n" +
                      "3. Convert to feet\n" +
                      "4. Quit the program\n";
        System.out.print(menu);
        writer.write(menu);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int choice;
        double meters;

        try (FileWriter writer = new FileWriter("A1_Conversion_output.txt")) {
            do {
                // Display the menu
                displayMenu(writer);
                System.out.print("Enter your choice: ");
                writer.write("Enter your choice: ");

                // Get the user's choice
                while (!scanner.hasNextInt()) {
                    String error = "Error: Invalid choice. Please enter a number between 1 and 4.\n";
                    System.out.print(error);
                    writer.write(error);
                    scanner.next(); // Clear invalid input
                    System.out.print("Enter your choice: ");
                    writer.write("Enter your choice: ");
                }
                choice = scanner.nextInt();
                writer.write(choice + "\n");

                // Process the user's choice
                switch (choice) {
                    case 1: // Convert to kilometers
                    case 2: // Convert to inches
                    case 3: // Convert to feet
                        System.out.print("Enter the distance in meters: ");
                        writer.write("Enter the distance in meters: ");

                        while (!scanner.hasNextDouble()) {
                            String error = "Error: Please enter a valid number.\n";
                            System.out.print(error);
                            writer.write(error);
                            scanner.next(); // Clear invalid input
                            System.out.print("Enter the distance in meters: ");
                            writer.write("Enter the distance in meters: ");
                        }
                        meters = scanner.nextDouble();
                        writer.write(meters + "\n");

                        if (meters < 0) {
                            String error = "Error: Distance cannot be negative. Try again.\n";
                            System.out.print(error);
                            writer.write(error);
                        } else {
                            if (choice == 1) {
                                showKilometers(meters, writer);
                            } else if (choice == 2) {
                                showInches(meters, writer);
                            } else if (choice == 3) {
                                showFeet(meters, writer);
                            }
                        }
                        break;

                    case 4: // Quit
                        String exitMessage = "Exiting the program. Goodbye!\n";
                        System.out.print(exitMessage);
                        writer.write(exitMessage);
                        break;

                    default:
                        String error = "Error: Invalid choice. Please select a number between 1 and 4.\n";
                        System.out.print(error);
                        writer.write(error);
                }
            } while (choice != 4);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
        } finally {
            scanner.close();
        }
    }
}
