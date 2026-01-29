/*================================
 Author     : Chidera Izuora
 Class Name : Introduction
 File Name  : Introduction.java
 Date       : 07/10/2023
 Version    : 1.0
 Purpose    : Project for Chapter 1 of "Starting Out With Java"
             : This program collects personal information and displays it in a formatted manner.
=================================*/
import java.util.Scanner;
import java.util.ArrayList;

public class Introduction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean running = true;
        
        while (running) {
            // Header box
            printBox("PERSONAL INTRODUCTION PROGRAM");
            
            // Get user input
            System.out.print("Enter your name: ");
            String name = scanner.nextLine();
            
            System.out.print("Enter your age: ");
            int age = scanner.nextInt();
            scanner.nextLine(); // Clear buffer
            
            System.out.print("Enter your dream job: ");
            String job = scanner.nextLine();
            
            System.out.print("Enter your favorite food: ");
            String food = scanner.nextLine();
            
            // Get multiple hobbies
            ArrayList<String> hobbies = new ArrayList<>();
            System.out.println("Enter your hobbies (type 'done' when finished):");
            while (true) {
                String hobby = scanner.nextLine();
                if (hobby.equalsIgnoreCase("done")) break;
                hobbies.add(hobby);
            }
            
            // Print formatted output
            printBox("YOUR INTRODUCTION");
            System.out.println("* Name: " + name);
            System.out.println("* Age: " + age + " - " + (age < 18 ? "Young and energetic!" : "Wise and experienced!"));
            System.out.println("* Dream Job: " + job);
            System.out.println("* Favorite Food: " + food);
            System.out.print("* Hobbies: ");
            System.out.println(String.join(", ", hobbies));
            printBox("");
            
            // Ask to continue
            System.out.print("Create another introduction? (yes/no): ");
            String choice = scanner.nextLine();
            if (!choice.equalsIgnoreCase("yes")) {
                running = false;
                printBox("THANK YOU FOR USING THE PROGRAM!");
            }
        }
        scanner.close();
    }
    
    // Helper method to print boxes
    private static void printBox(String text) {
        String border = "************************************";
        System.out.println(border);
        if (!text.isEmpty()) {
            System.out.println("* " + text + " *");
            System.out.println(border);
        }
    }
}