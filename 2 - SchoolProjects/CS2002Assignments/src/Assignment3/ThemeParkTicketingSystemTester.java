package Assignment3;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2002
Purpose    : Assignment 3
=================================*/

public class ThemeParkTicketingSystemTester {

	public static void main(String[] args) {
		int totalPoints = 0;
		int maxPoints = 25;
		TicketStack ticketStack = new TicketStack();
		RideQueue rideQueue = new RideQueue();

		System.out.println("--- Starting Theme Park Ticketing System Tests ---\n");

		try {
			// Test 1: Selling tickets
			System.out.println("Test 1: Selling Tickets...");
			ticketStack.sellTicket("Alice");
			ticketStack.sellTicket("Bob");
			ticketStack.sellTicket("Charlie");
			ticketStack.displayTickets();
			if (ticketStack.isValidTicket("TICKET1") && ticketStack.isValidTicket("TICKET3")) {
				System.out.println("Test 1 Passed! (+5 points)");
				totalPoints += 5;
			} else {
				System.out.println("Test 1 Failed.");
			}

			// Test 2: Returning a ticket
			System.out.println("\nTest 2: Returning the Most Recent Ticket...");
			ticketStack.returnTicket();
			ticketStack.displayTickets();
			if (!ticketStack.isValidTicket("TICKET3")) {
				System.out.println("Test 2 Passed! (+5 points)");
				totalPoints += 5;
			} else {
				System.out.println("Test 2 Failed.");
			}

			// Test 3: Adding customers to the ride queue
			System.out.println("\nTest 3: Adding Customers to Ride Queue...");
			ticketStack.sellTicket("Diana");
			rideQueue.addToQueue(ticketStack.getTicketByID("TICKET1")); // Alice
			rideQueue.addToQueue(ticketStack.getTicketByID("TICKET2")); // Bob
			rideQueue.addToQueue(ticketStack.getTicketByID("TICKET4")); // Diana
			rideQueue.displayQueue();
			if (rideQueue != null && rideQueue.toString().contains("Alice") && rideQueue.toString().contains("Diana")) {
				System.out.println("Test 3 Passed! (+5 points)");
				totalPoints += 5;
			} else {
				System.out.println("Test 3 Failed.");
			}

			// Test 4: Removing customers from the ride queue
			System.out.println("\nTest 4: Removing Customers from Ride Queue...");
			rideQueue.removeFromQueue(); // Alice should be removed
			rideQueue.displayQueue();
			rideQueue.removeFromQueue(); // Bob should be removed
			rideQueue.displayQueue();
			if (rideQueue != null && !rideQueue.toString().contains("Alice")) {
				System.out.println("Test 4 Passed! (+5 points)");
				totalPoints += 5;
			} else {
				System.out.println("Test 4 Failed.");
			}

			// Test 5: Checking behavior with empty queues and stacks
			System.out.println("\nTest 5: Handling Empty Data Structures...");
			ticketStack.returnTicket(); // Should handle gracefully
			rideQueue.removeFromQueue(); // Should handle gracefully
			if (ticketStack != null && rideQueue != null) {
				System.out.println("Test 5 Passed! (+5 points)");
				totalPoints += 5;
			} else {
				System.out.println("Test 5 Failed.");
			}

		} catch (Exception e) {
			System.out.println("An error occurred during testing: " + e.getMessage());
		}

		System.out.println("\n--- Testing Complete ---");
		System.out.println("Total Points: " + totalPoints + "/" + maxPoints);
	}
}
