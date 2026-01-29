package lab2;


/*================================
 Author     : Chidera Izuora
 Class Name : Book
 Date       : 02-02-2025
 Course     : CS2001
 Purpose    : Lab 2 
=================================*/

public class Book {

	// for representing the title of Book
	private String title;

	// for representing the author of the Book
	private String author;

	// for representing the cost of the book
	private double cost;

	/**
	 * Default Constructor For Book Class
	 */
	public Book() {

	};

	/**
	 * Overloaded Constructor For Book Class
	 */
	public Book(String a_title, String a_author, double a_cost) {
		title = a_title;
		author = a_author;
		cost = a_cost;
	}

	/**
	 * Set method for the variable title
	 */
	public void setTitle(String a_title) {
		title = a_title;
	}

	/**
	 * Set method for the variable author
	 */
	public void setAuthor(String a_author) {
		author = a_author;
	}

	/**
	 * Set method for the variable cost
	 */
	public void setCost(double a_cost) {
		cost = a_cost;
	}

	/**
	 * Get method for the variable title
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * Get method for the variable author
	 */
	public String getAuthor() {
		return author;
	}

	/**
	 * Get method for the variable cost
	 */
	public double getCost() {
		return cost;
	}

	/**
	 * Returns the String representation of Book object
	 */
	@Override
	public String toString() {
		String temp = "title = " + title + "\nauthor = " + author + "\ncost = " + cost;

		return temp;
	}

	/**
	 * main( ) method for Book Class
	 */
	public static void main(String args[]) {
		Book book_1 = new Book();
		book_1.setTitle("Starting out with Java");
		book_1.setAuthor("Tony Gaddis");
		book_1.setCost(100);
		System.out.println("Printing book_1 instance details:");
		System.out.println(book_1);

		Book book_2 = new Book("Starting out with Python", "Tony Gaddis", 116);
		System.out.println("\n\nPrinting book_2 instance details:");
		System.out.println(book_2);
	}
}
