/*================================
 Author     : Chidera Izuora
 Class Name : BankingAssistant
    File Name  : BankingAssistant.java
 Date       : 07/10/2023
 Version    : 1.0
Purpose   : A banking assistant program that provides account management features
             including balance evaluation, loan eligibility, and transaction processing.
             It supports both console and GUI modes for user interaction.
             
Features:
 - Account type selection (Savings, Checking, Student)
=================================*/

import java.util.Scanner;
import javax.swing.JOptionPane;
import java.util.Random;

public class BankingAssistant {
    // Constants
    private static final double SAVINGS_RATE = 0.03;
    private static final double CHECKING_FEE = 10.00;
    private static final double LOAN_THRESHOLD = 5000.00;
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Random rand = new Random();
        
        System.out.println("=== SMART BANKING ASSISTANT ===");
        System.out.println("1. Console Version");
        System.out.println("2. GUI Version");
        System.out.print("Choose mode: ");
        
        int mode = input.nextInt();
        input.nextLine(); // Consume newline
        
        if (mode == 1) {
            consoleVersion(input, rand);
        } else if (mode == 2) {
            guiVersion();
        } else {
            System.out.println("Invalid choice!");
        }
        
        input.close();
    }
    
    private static void consoleVersion(Scanner input, Random rand) {
        // Account Selection
        System.out.println("\nACCOUNT TYPES:");
        System.out.println("1. Savings");
        System.out.println("2. Checking");
        System.out.println("3. Student");
        System.out.print("Select account type (1-3): ");
        
        int accountType = input.nextInt();
        input.nextLine(); // Consume newline
        
        String accountName = "";
        double interestRate = 0;
        boolean hasFee = false;
        
        // Switch for account type
        switch(accountType) {
            case 1:
                accountName = "Savings";
                interestRate = SAVINGS_RATE;
                break;
            case 2:
                accountName = "Checking";
                hasFee = true;
                break;
            case 3:
                accountName = "Student";
                interestRate = SAVINGS_RATE * 1.5; // 50% bonus
                break;
            default:
                System.out.println("Invalid account type!");
                return;
        }
        
        // Balance Input
        System.out.print("Enter current balance: $");
        double balance = input.nextDouble();
        input.nextLine(); // Consume newline
        
        // Balance Evaluation
        String balanceStatus;
        if (balance < 0) {
            balanceStatus = "OVERDRAWN";
        } else if (balance < 100) {
            balanceStatus = "LOW";
        } else if (balance < 1000) {
            balanceStatus = "MEDIUM";
        } else {
            balanceStatus = "HIGH";
        }
        
        // Loan Eligibility (using logical operators)
        boolean loanEligible = (balance >= LOAN_THRESHOLD) && 
                              (accountType != 3) && 
                              (!balanceStatus.equals("OVERDRAWN"));
        
        // Generate random transaction
        double transaction = (rand.nextDouble() * 200) - 100; // -100 to +100
        double newBalance = balance + transaction;
        
        // Format receipt
        System.out.println("\n=== BANKING RECEIPT ===");
        System.out.printf("Account Type: %s%n", accountName);
        System.out.printf("Current Balance: $%,.2f%n", balance);
        System.out.printf("Balance Status: %s%n", balanceStatus);
        
        if (accountType != 2) {
            System.out.printf("Interest Rate: %.1f%%%n", interestRate * 100);
        }
        
        System.out.printf("%nTransaction Amount: %+,.2f%n", transaction);
        System.out.printf("New Balance: $%,.2f%n", newBalance);
        
        if (hasFee) {
            System.out.printf("Monthly Fee: $%.2f%n", CHECKING_FEE);
        }
        
        System.out.printf("%nLoan Eligible: %s%n", 
            loanEligible ? "YES" : "NO");
        
        // Special messages
        if (newBalance < 0) {
            System.out.println("\nALERT: Your account is overdrawn!");
        } else if (transaction > 50) {
            System.out.println("\nBonus: Large deposit received!");
        }
    }
    
    private static void guiVersion() {
        // Account selection
        String[] accountTypes = {"Savings", "Checking", "Student"};
        int accountChoice = JOptionPane.showOptionDialog(
            null, 
            "Select account type:", 
            "Banking Assistant", 
            JOptionPane.DEFAULT_OPTION, 
            JOptionPane.QUESTION_MESSAGE, 
            null, 
            accountTypes, 
            accountTypes[0]
        );
        
        if (accountChoice == JOptionPane.CLOSED_OPTION) return;
        
        String accountName = accountTypes[accountChoice];
        double interestRate = 0;
        boolean hasFee = false;
        
        switch(accountChoice) {
            case 0: // Savings
                interestRate = SAVINGS_RATE;
                break;
            case 1: // Checking
                hasFee = true;
                break;
            case 2: // Student
                interestRate = SAVINGS_RATE * 1.5;
                break;
        }
        
        // Balance input
        String balanceStr = JOptionPane.showInputDialog("Enter current balance:");
        if (balanceStr == null) return;
        
        double balance;
        try {
            balance = Double.parseDouble(balanceStr);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(null, "Invalid balance amount!");
            return;
        }
        
        // Balance evaluation
        String balanceStatus;
        if (balance < 0) {
            balanceStatus = "OVERDRAWN";
        } else if (balance < 100) {
            balanceStatus = "LOW";
        } else if (balance < 1000) {
            balanceStatus = "MEDIUM";
        } else {
            balanceStatus = "HIGH";
        }
        
        // Loan eligibility
        boolean loanEligible = (balance >= LOAN_THRESHOLD) && 
                              (accountChoice != 2) && 
                              (!balanceStatus.equals("OVERDRAWN"));
        
        // Generate receipt
        Random rand = new Random();
        double transaction = (rand.nextDouble() * 200) - 100;
        double newBalance = balance + transaction;
        
        StringBuilder receipt = new StringBuilder();
        receipt.append(String.format("=== %s ACCOUNT ===%n", accountName));
        receipt.append(String.format("Current Balance: $%,.2f%n", balance));
        receipt.append(String.format("Status: %s%n", balanceStatus));
        
        if (accountChoice != 1) {
            receipt.append(String.format("Interest Rate: %.1f%%%n", interestRate * 100));
        }
        
        receipt.append(String.format("%nTransaction: %+,.2f%n", transaction));
        receipt.append(String.format("New Balance: $%,.2f%n", newBalance));
        
        if (hasFee) {
            receipt.append(String.format("Monthly Fee: $%.2f%n", CHECKING_FEE));
        }
        
        receipt.append(String.format("%nLoan Eligible: %s", 
            loanEligible ? "YES" : "NO"));
        
        if (newBalance < 0) {
            receipt.append("\n\nALERT: Account overdrawn!");
        } else if (transaction > 50) {
            receipt.append("\n\nBonus: Large deposit received!");
        }
        
        JOptionPane.showMessageDialog(null, receipt.toString());
    }
}