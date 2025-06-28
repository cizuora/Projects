package lab2;

/*================================
Author     : Chidera Izuora
Class Name : Student
Date       : 02-02-2025
Course     : CS2001
Purpose    : Lab 2 
=================================*/

public class Student {

   // for representing the name of the Student
   private String name;

   // for representing the email of the Student
   private String email;

   // for representing the marks of the Student
   private double marks;

   /**
    * Default Constructor For Student Class
    */
   public Student() {
   }

   /**
    * Overloaded Constructor For Student Class
    */
   public Student(String a_name, String a_email, double a_marks) {
       name = a_name;
       email = a_email;
       marks = a_marks;
   }

   /**
    * Set method for the variable name
    */
   public void setName(String a_name) {
       name = a_name;
   }

   /**
    * Set method for the variable email
    */
   public void setEmail(String a_email) {
       email = a_email;
   }

   /**
    * Set method for the variable marks
    */
   public void setMarks(double a_marks) {
       marks = a_marks;
   }

   /**
    * Get method for the variable name
    */
   public String getName() {
       return name;
   }

   /**
    * Get method for the variable email
    */
   public String getEmail() {
       return email;
   }

   /**
    * Get method for the variable marks
    */
   public double getMarks() {
       return marks;
   }

   /**
    * Returns the String representation of Student object
    */
   @Override
   public String toString() {
       String temp = "name = " + name + "\nemail = " + email + "\nmarks = " + marks;
       return temp;
   }

   /**
    * main( ) method for Student Class
    */
   public static void main(String args[]) {
       Student student_1 = new Student();
       student_1.setName("John Doe");
       student_1.setEmail("johndoe@example.com");
       student_1.setMarks(95);
       System.out.println("Printing student_1 instance details:");
       System.out.println(student_1);

       Student student_2 = new Student("Jane Smith", "janesmith@example.com", 89);
       System.out.println("\n\nPrinting student_2 instance details:");
       System.out.println(student_2);
   }
}


