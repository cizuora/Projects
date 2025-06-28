package Assignment3;

import java.util.Stack;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2002
Purpose    : Assignment 3
=================================*/

public class TicketStack {
    private Stack<Ticket> stack;
    private int ticketCounter;

    public TicketStack() {
        stack = new Stack<>();
        ticketCounter = 1;
    }

    public void sellTicket(String customerName) {
        String ticketID = "TICKET" + ticketCounter;
        Ticket newTicket = new Ticket(ticketID, customerName);
        stack.push(newTicket);
        System.out.println("Ticket sold: " + ticketID);
        ticketCounter++;
    }

    public void returnTicket() {
        if (stack.isEmpty()) {
            System.out.println("No tickets to return.");
            return;
        }
        Ticket returned = stack.pop();
        System.out.println("Returned ticket: " + returned);
    }

    public void displayTickets() {
        if (stack.isEmpty()) {
            System.out.println("No tickets in the stack.");
            return;
        }
        System.out.println("Current tickets in the stack:");
        for (Ticket ticket : stack) {
            System.out.println(ticket);
        }
    }

    public boolean isValidTicket(String ticketID) {
        for (Ticket ticket : stack) {
            if (ticket.getTicketID().equals(ticketID)) {
                return true;
            }
        }
        return false;
    }

    public Ticket getTicketByID(String ticketID) {
        for (Ticket ticket : stack) {
            if (ticket.getTicketID().equals(ticketID)) {
                return ticket;
            }
        }
        return null;
    }
}

