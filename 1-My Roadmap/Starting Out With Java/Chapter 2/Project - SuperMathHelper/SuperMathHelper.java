/*================================
 Author     : Chidera Izuora
 Class Name : MathHelper
 File Name  : MathHelper.java
 Date       : 07/10/2023
 Version    : 1.0
 Purpose    : A comprehensive math helper application that includes various features such as a basic calculator, tax calculator, integer operations, unit converter, math quiz, and a GUI version.
 Features   :  
              1. Basic Calculator
              2. Tax Calculator
              3. Integer Operations
              4. Unit Converter
              5. Math Quiz
              6. GUI Version
=================================*/

import java.util.Scanner;
import javax.swing.JOptionPane;

public class SuperMathHelper {
    // Constants
    private static final double TAX_RATE = 0.08;
    private static final double KM_PER_MILE = 1.60934;
    private static final String APP_TITLE = "SUPER MATH HELPER";

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        boolean running = true;
        
        while (running) {
            System.out.println("\n***** " + APP_TITLE + " *****");
            System.out.println("1. Basic Calculator");
            System.out.println("2. Tax Calculator");
            System.out.println("3. Integer Operations");
            System.out.println("4. Unit Converter");
            System.out.println("5. Math Quiz");
            System.out.println("6. GUI Version");
            System.out.println("0. Exit");
            System.out.print("Choose an option: ");
            
            int choice = input.nextInt();
            
            switch (choice) {
                case 1 -> basicCalculator(input);
                case 2 -> taxCalculator(input);
                case 3 -> integerOperations(input);
                case 4 -> unitConverter(input);
                case 5 -> mathQuiz(input);
                case 6 -> guiVersion();
                case 0 -> running = false;
                default -> System.out.println("Invalid choice!");
            }
        }
        
        input.close();
        System.out.println("Thank you for using " + APP_TITLE + "!");
    }

    // Feature 1: Basic Calculator
    private static void basicCalculator(Scanner input) {
        System.out.println("\n--- BASIC CALCULATOR ---");
        System.out.print("Enter first number: ");
        double num1 = input.nextDouble();
        System.out.print("Enter second number: ");
        double num2 = input.nextDouble();
        
        System.out.println("\nResults:");
        System.out.printf("%.2f + %.2f = %.2f%n", num1, num2, num1 + num2);
        System.out.printf("%.2f - %.2f = %.2f%n", num1, num2, num1 - num2);
        System.out.printf("%.2f * %.2f = %.2f%n", num1, num2, num1 * num2);
        
        if (num2 != 0) {
            System.out.printf("%.2f / %.2f = %.2f%n", num1, num2, num1 / num2);
            System.out.printf("%.2f %% %.2f = %.2f%n", num1, num2, num1 % num2);
        } else {
            System.out.println("Cannot divide by zero!");
        }
    }

    // Feature 2: Tax Calculator
    private static void taxCalculator(Scanner input) {
        System.out.println("\n--- TAX CALCULATOR ---");
        System.out.print("Enter item price: $");
        double price = input.nextDouble();
        double tax = price * TAX_RATE;
        System.out.printf("Tax (%.0f%%): $%.2f%n", TAX_RATE * 100, tax);
        System.out.printf("Total: $%.2f%n", price + tax);
    }

    // Feature 3: Integer Operations
    private static void integerOperations(Scanner input) {
        System.out.println("\n--- INTEGER OPERATIONS ---");
        System.out.print("Enter a whole number: ");
        int num = input.nextInt();
        System.out.println(num + " squared = " + (num * num));
        System.out.println(num + " cubed = " + (num * num * num));
        System.out.println(num + " is " + (num % 2 == 0 ? "even" : "odd"));
    }

    // Feature 4: Unit Converter
    private static void unitConverter(Scanner input) {
        System.out.println("\n--- UNIT CONVERTER ---");
        System.out.println("1. Miles to Kilometers");
        System.out.println("2. Kilometers to Miles");
        System.out.print("Choose conversion: ");
        
        int convChoice = input.nextInt();
        System.out.print("Enter value: ");
        double value = input.nextDouble();
        
        if (convChoice == 1) {
            System.out.printf("%.2f miles = %.2f kilometers%n", value, value * KM_PER_MILE);
        } else if (convChoice == 2) {
            System.out.printf("%.2f kilometers = %.2f miles%n", value, value / KM_PER_MILE);
        } else {
            System.out.println("Invalid choice!");
        }
    }

    // Feature 5: Math Quiz
    private static void mathQuiz(Scanner input) {
        System.out.println("\n--- MATH QUIZ ---");
        int num1 = (int)(Math.random() * 10) + 1;
        int num2 = (int)(Math.random() * 10) + 1;
        int operation = (int)(Math.random() * 3); // 0=+, 1=-, 2=*
        
        String operator = "";
        int correctAnswer = 0;
        
        switch (operation) {
            case 0 -> {
                operator = "+";
                correctAnswer = num1 + num2;
            }
            case 1 -> {
                operator = "-";
                correctAnswer = num1 - num2;
            }
            case 2 -> {
                operator = "*";
                correctAnswer = num1 * num2;
            }
        }
        
        System.out.printf("What is %d %s %d? ", num1, operator, num2);
        int userAnswer = input.nextInt();
        
        if (userAnswer == correctAnswer) {
            System.out.println("Correct! 🎉");
        } else {
            System.out.println("Wrong! The answer was " + correctAnswer);
        }
    }

    // Feature 6: GUI Version
    private static void guiVersion() {
        String[] options = {"Basic Calc", "Tax Calc", "Unit Conv", "Quiz", "Exit"};
        
        while (true) {
            int choice = JOptionPane.showOptionDialog(
                null,
                "Welcome to " + APP_TITLE,
                APP_TITLE,
                JOptionPane.DEFAULT_OPTION,
                JOptionPane.PLAIN_MESSAGE,
                null,
                options,
                options[0]
            );
            
            switch (choice) {
                case 0 -> basicCalcGUI();
                case 1 -> taxCalcGUI();
                case 2 -> unitConvGUI();
                case 3 -> quizGUI();
                case 4, JOptionPane.CLOSED_OPTION -> {
                    JOptionPane.showMessageDialog(null, "Thanks for using " + APP_TITLE + "!");
                    return;
                }
            }
        }
    }

    private static void basicCalcGUI() {
        try {
            double num1 = Double.parseDouble(JOptionPane.showInputDialog("Enter first number:"));
            double num2 = Double.parseDouble(JOptionPane.showInputDialog("Enter second number:"));
            
            String result = String.format(
                "%.2f + %.2f = %.2f%n" +
                "%.2f - %.2f = %.2f%n" +
                "%.2f * %.2f = %.2f%n",
                num1, num2, num1 + num2,
                num1, num2, num1 - num2,
                num1, num2, num1 * num2
            );
            
            if (num2 != 0) {
                result += String.format(
                    "%.2f / %.2f = %.2f%n" +
                    "%.2f %% %.2f = %.2f",
                    num1, num2, num1 / num2,
                    num1, num2, num1 % num2
                );
            } else {
                result += "Cannot divide by zero!";
            }
            
            JOptionPane.showMessageDialog(null, result);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(null, "Invalid input! Please enter numbers.");
        }
    }

    private static void taxCalcGUI() {
        try {
            double price = Double.parseDouble(JOptionPane.showInputDialog("Enter item price:"));
            double tax = price * TAX_RATE;
            String result = String.format(
                "Price: $%.2f%n" +
                "Tax (%.0f%%): $%.2f%n" +
                "Total: $%.2f",
                price, TAX_RATE * 100, tax, price + tax
            );
            JOptionPane.showMessageDialog(null, result);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(null, "Invalid input! Please enter a number.");
        }
    }

    private static void unitConvGUI() {
        String[] options = {"Miles to Km", "Km to Miles"};
        int choice = JOptionPane.showOptionDialog(
            null,
            "Choose conversion:",
            "Unit Converter",
            JOptionPane.DEFAULT_OPTION,
            JOptionPane.PLAIN_MESSAGE,
            null,
            options,
            options[0]
        );
        
        if (choice == JOptionPane.CLOSED_OPTION) return;
        
        try {
            String input = JOptionPane.showInputDialog("Enter value:");
            if (input == null) return;
            
            double value = Double.parseDouble(input);
            String result;
            
            if (choice == 0) {
                result = String.format("%.2f miles = %.2f kilometers", value, value * KM_PER_MILE);
            } else {
                result = String.format("%.2f kilometers = %.2f miles", value, value / KM_PER_MILE);
            }
            
            JOptionPane.showMessageDialog(null, result);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(null, "Invalid input! Please enter a number.");
        }
    }

    private static void quizGUI() {
        int num1 = (int)(Math.random() * 10) + 1;
        int num2 = (int)(Math.random() * 10) + 1;
        int operation = (int)(Math.random() * 3);
        
        String operator = "";
        int correctAnswer = 0;
        
        switch (operation) {
            case 0 -> {
                operator = "+";
                correctAnswer = num1 + num2;
            }
            case 1 -> {
                operator = "-";
                correctAnswer = num1 - num2;
            }
            case 2 -> {
                operator = "*";
                correctAnswer = num1 * num2;
            }
        }
        
        String answer = JOptionPane.showInputDialog(
            "What is " + num1 + " " + operator + " " + num2 + "?"
        );
        
        if (answer == null) return;
        
        try {
            int userAnswer = Integer.parseInt(answer);
            if (userAnswer == correctAnswer) {
                JOptionPane.showMessageDialog(null, "Correct! 🎉");
            } else {
                JOptionPane.showMessageDialog(null, "Wrong! The answer was " + correctAnswer);
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(null, "Please enter a whole number!");
        }
    }
}