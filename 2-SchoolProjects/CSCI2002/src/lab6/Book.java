package lab6;
/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-29-2025
Course     : CS2001
Purpose    : Lab 6
=================================*/
public class Book {
	 private String title;
	    private String author;
	    private double price;

	    // Constructor using 'this' keyword
	    public Book(String title, String author, double price) {
	        this.title = title;
	        this.author = author;
	        this.price = price;
	    }

	    // Override toString() method
	    @Override
	    public String toString() {
	        return "Book[title=" + title + ", author=" + author + ", price=" + price + "]";
	    }

	    // Method for method chaining (used in Task 3)
	    public Book setPrice(double price) {
	        this.price = price;
	        return this;
	    }

	    // Override equals() method (used in Task 2)
	    @Override
	    public boolean equals(Object obj) {
	        if (this == obj) return true;
	        if (obj == null || getClass() != obj.getClass()) return false;
	        Book book = (Book) obj;
	        return Double.compare(book.price, price) == 0 &&
	               title.equals(book.title) &&
	               author.equals(book.author);
	    }
}
