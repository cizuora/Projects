package Assignment3;

import java.util.LinkedList;
import java.util.Queue;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2002
Purpose    : Assignment 3
=================================*/

public class RideQueue {
    private Queue<Ticket> queue;

    public RideQueue() {
        queue = new LinkedList<>();
    }

    public void addToQueue(Ticket ticket) {
        queue.add(ticket);
    }

    public void removeFromQueue() {
        if (queue.isEmpty()) {
            System.out.println("Cannot remove from an empty queue.");
            return;
        }
        queue.remove();
    }

    public void displayQueue() {
        if (queue.isEmpty()) {
            System.out.println("The ride queue is currently empty.");
            return;
        }
        System.out.println("Current Ride Queue:");
        for (Ticket ticket : queue) {
            System.out.println(ticket);
        }
    }

    @Override
    public String toString() {
        return queue.toString();
    }
}
