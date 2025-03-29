package lab6;
/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-29-2025
Course     : CS2001
Purpose    : Lab 6
=================================*/
public class BookEqualsTest {
	public static void main(String[] args) {
        Book b1 = new Book("Java Basics", "John Doe", 39.99);
        Book b2 = new Book("Java Basics", "John Doe", 39.99);

        System.out.println("b1 == b2: " + (b1 == b2)); // Should print false
        System.out.println("b1.equals(b2): " + b1.equals(b2)); // Should print true
        
        Book b = new Book("AI", "Jane Smith", 50.00);
        b.setPrice(45.00).setPrice(40.00);
        System.out.println(b.toString());

    }
}
