package Assignment2;

import java.util.HashMap;
import java.util.Map;

/**
 * A class of bags whose entries are stored in a fixed-size array.
 * 
/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2002
Purpose    : Assignment 2
=================================*/

public final class ArrayBag<T> implements BagInterface<T> {
	private final T[] bag;
	private int numberOfEntries;
	private boolean integrityOK = false;
	private static final int DEFAULT_CAPACITY = 25;
	private static final int MAX_CAPACITY = 10000;

	/** Creates an empty bag whose initial capacity is 25. */
	public ArrayBag() {
		this(DEFAULT_CAPACITY);
	} // end default constructor

	/**
	 * Creates an empty bag having a given capacity.
	 * 
	 * @param desiredCapacity The integer capacity desired.
	 */
	public ArrayBag(int desiredCapacity) {
		if (desiredCapacity <= MAX_CAPACITY) {
			// The cast is safe because the new array contains null entries
			@SuppressWarnings("unchecked")
			T[] tempBag = (T[]) new Object[desiredCapacity]; // Unchecked cast
			bag = tempBag;
			numberOfEntries = 0;
			integrityOK = true;
			// Test that contents are nulls - OK
			// for (int index = 0; index < desiredCapacity; index++)
			// System.out.print(bag[index] + " ");
			// System.out.println();
		} else {
			throw new IllegalStateException(
					"Attempt to create a bag " + "whose capacity exceeds " + "allowed maximum.");
		}
	} // end constructor

	/**
	 * Adds a new entry to this bag.
	 * 
	 * @param newEntry The object to be added as a new entry.
	 * @return True if the addition is successful, or false if not.
	 */
	@Override
	public boolean add(T newEntry) {
		checkIntegrity();
		boolean result = true;
		if (isArrayFull()) {
			result = false;
		} else { // Assertion: result is true here
			bag[numberOfEntries] = newEntry;
			numberOfEntries++;
		} // end if

		return result;
	} // end add

	/**
	 * Retrieves all entries that are in this bag.
	 * 
	 * @return A newly allocated array of all the entries in this bag.
	 */
	// public <T> T[] toArray() //OK
	@Override
	public T[] toArray() // OK
	{
		checkIntegrity();

		// The cast is safe because the new array contains null entries.
		@SuppressWarnings("unchecked")
		T[] result = (T[]) new Object[numberOfEntries]; // Unchecked cast

		for (int index = 0; index < numberOfEntries; index++) {
			result[index] = bag[index];
		} // end for
		return result;
		// Note: The body of this method could consist of one return statement,
		// if you call Arrays.copyOf
	} // end toArray

	/**
	 * Sees whether this bag is empty.
	 * 
	 * @return True if this bag is empty, or false if not.
	 */
	@Override
	public boolean isEmpty() {
		return numberOfEntries == 0;
	} // end isEmpty

	/**
	 * Gets the current number of entries in this bag.
	 * 
	 * @return The integer number of entries currently in this bag.
	 */
	@Override
	public int getCurrentSize() {
		return numberOfEntries;
	} // end getCurrentSize

	/**
	 * Counts the number of times a given entry appears in this bag.
	 * 
	 * @param anEntry The entry to be counted.
	 * @return The number of times anEntry appears in this ba.
	 */
	@Override
	public int getFrequencyOf(T anEntry) {
		checkIntegrity();
		int counter = 0;

		for (int index = 0; index < numberOfEntries; index++) {
			if (anEntry.equals(bag[index])) {
				counter++;
			} // end if
		} // end for

		return counter;
	} // end getFrequencyOf

	/**
	 * Tests whether this bag contains a given entry.
	 * 
	 * @param anEntry The entry to locate.
	 * @return True if this bag contains anEntry, or false otherwise.
	 */
	@Override
	public boolean contains(T anEntry) {
		checkIntegrity();
		return getIndexOf(anEntry) > -1; // or >= 0
	} // end contains

	/** Removes all entries from this bag. */
	@Override
	public void clear() {
		while (!isEmpty()) {
			remove();
		}
	} // end clear

	/**
	 * Removes one unspecified entry from this bag, if possible.
	 * 
	 * @return Either the removed entry, if the removal was successful, or null.
	 */
	@Override
	public T remove() {
		checkIntegrity();
		T result = removeEntry(numberOfEntries - 1);
		return result;
	} // end remove

	/**
	 * Removes one occurrence of a given entry from this bag.
	 * 
	 * @param anEntry The entry to be removed.
	 * @return True if the removal was successful, or false if not.
	 */
	@Override
	public boolean remove(T anEntry) {
		checkIntegrity();
		int index = getIndexOf(anEntry);
		T result = removeEntry(index);
		return anEntry.equals(result);
	} // end remove

	// Returns true if the array bag is full, or false if not.
	private boolean isArrayFull() {
		return numberOfEntries >= bag.length;
	} // end isArrayFull

	// Locates a given entry within the array bag.
	// Returns the index of the entry, if located,
	// or -1 otherwise.
	// Precondition: checkIntegrity has been called.
	private int getIndexOf(T anEntry) {
		int where = -1;
		boolean found = false;
		int index = 0;

		while (!found && (index < numberOfEntries)) {
			if (anEntry.equals(bag[index])) {
				found = true;
				where = index;
			} // end if
			index++;
		} // end while

		// Assertion: If where > -1, anEntry is in the array bag, and it
		// equals bag[where]; otherwise, anEntry is not in the array.

		return where;
	} // end getIndexOf

	// Removes and returns the entry at a given index within the array.
	// If no such entry exists, returns null.
	// Precondition: 0 <= givenIndex < numberOfEntries.
	// Precondition: checkIntegrity has been called.
	private T removeEntry(int givenIndex) {
		T result = null;

		if (!isEmpty() && (givenIndex >= 0)) {
			result = bag[givenIndex]; // Entry to remove
			int lastIndex = numberOfEntries - 1;
			bag[givenIndex] = bag[lastIndex]; // Replace entry to remove with last entry
			bag[lastIndex] = null; // Remove reference to last entry
			numberOfEntries--;
		} // end if

		return result;
	} // end removeEntry

	// Throws an exception if this object is not initialized.
	private void checkIntegrity() {
		if (!integrityOK) {
			throw new SecurityException("ArrayBag object is corrupt.");
		}
	} // end checkIntegrity

	// =================== New methods ======================================
	/**
	 * Combines all elements from this bag and another bag into a new bag.
	 *
	 * @param otherBag The other bag to combine with this bag.
	 * @return A new ArrayBag containing all elements from both bags.
	 */

	public ArrayBag<T> union(ArrayBag<T> otherBag) {
		// Create a new bag with enough capacity to hold both bags’ items.
        ArrayBag<T> result = new ArrayBag<>(this.getCurrentSize() + otherBag.getCurrentSize());
        
        // Add items from the current bag.
        for (T item : this.toArray()) {
            result.add(item);
        }
        // Add items from the other bag.
        for (T item : otherBag.toArray()) {
            result.add(item);
        }
        return result;
	}

	/**
	 * Finds common elements between this bag and another bag.
	 *
	 * @param otherBag The other bag to intersect with.
	 * @return A new ArrayBag containing the intersection of both bags.
	 */
	public ArrayBag<T> intersection(ArrayBag<T> otherBag) {
		// The maximum possible size is the smaller of the two bags.
        ArrayBag<T> result = new ArrayBag<>(Math.min(this.getCurrentSize(), otherBag.getCurrentSize()));
        
        // Create a copy of the other bag to "remove" items as we match them.
        ArrayBag<T> copyOfOther = new ArrayBag<>(otherBag.getCurrentSize());
        for (T item : otherBag.toArray()) {
            copyOfOther.add(item);
        }
        
        // For each item in this bag, if it appears in copyOfOther, add it to the result
        // and remove one occurrence from copyOfOther.
        for (T item : this.toArray()) {
            if (copyOfOther.remove(item)) {
                result.add(item);
            }
        }
        return result;
	}

	/**
	 * Finds the difference between this bag and another bag.
	 *
	 * @param otherBag The other bag to subtract from this bag.
	 * @return A new ArrayBag containing the difference.
	 */
	public ArrayBag<T> difference(ArrayBag<T> otherBag) {
		// Start by copying all items from the current bag.
        ArrayBag<T> result = new ArrayBag<>(this.getCurrentSize());
        for (T item : this.toArray()) {
            result.add(item);
        }
        // For each item in the other bag, remove one occurrence from result.
        for (T item : otherBag.toArray()) {
            result.remove(item);
        }
        return result;
	}

	/**
	 * Replaces a specific element in this bag with another element.
	 *
	 * @param oldEntry The element to be replaced.
	 * @param newEntry The element to replace with.
	 * @return True if the replacement is successful, false otherwise.
	 */
	public boolean replace(T oldEntry, T newEntry) {
		int index = getIndexOf(oldEntry); // Find the index of oldEntry in the bag
	    if (index > -1) {                 // If found (index is not -1)
	        bag[index] = newEntry;        // Replace oldEntry with newEntry
	        return true;                  // Indicate that the replacement was successful
	    }
	    return false;                     // Return false if oldEntry is not found
	}

	/**
	 * Converts this bag into a set by removing duplicates.
	 *
	 * @return A new ArrayBag containing only unique elements from this bag.
	 */
	public ArrayBag<T> toSet() {
		// Create a new bag with capacity equal to the current bag's size
	    ArrayBag<T> setBag = new ArrayBag<>(this.getCurrentSize());
	    
	    // Iterate through all items in the current bag
	    for (T item : this.toArray()) {
	        // Only add the item if it's not already in the setBag
	        if (!setBag.contains(item)) {
	            setBag.add(item);
	        }
	    }
	    
	    return setBag;
	}

	/**
	 * Finds the most frequent element in this bag.
	 *
	 * @return The most frequent element, or null if the bag is empty.
	 */

	public T getMostFrequentItem() {
		if (isEmpty()) { // If the bag is empty, return null.
	        return null;
	    }
	    
	    // Create a HashMap to count the frequency of each element.
	    HashMap<T, Integer> frequencyMap = new HashMap<>();
	    for (T item : toArray()) {
	        frequencyMap.put(item, frequencyMap.getOrDefault(item, 0) + 1);
	    }
	    
	    // Determine the most frequent item.
	    T mostFrequent = null;
	    int highestFrequency = 0;
	    for (Map.Entry<T, Integer> entry : frequencyMap.entrySet()) {
	        if (entry.getValue() > highestFrequency) {
	            highestFrequency = entry.getValue();
	            mostFrequent = entry.getKey();
	        }
	    }
	    
	    return mostFrequent;
	}

	/**
	 * Checks if this bag is a subset of another bag.
	 *
	 * @param otherBag The other bag to compare with.
	 * @return True if this bag is a subset of the other bag, false otherwise.
	 */
	public boolean isSubsetOf(ArrayBag<T> otherBag) {
		// Get only unique items from the current bag
	    ArrayBag<T> uniqueItems = this.toSet();
	    
	    // For each unique element, check if its frequency in this bag
	    // is less than or equal to its frequency in otherBag.
	    for (T item : uniqueItems.toArray()) {
	        if (this.getFrequencyOf(item) > otherBag.getFrequencyOf(item)) {
	            return false; // Found an element that doesn't meet the subset condition
	        }
	    }
	    return true; // All elements satisfy the subset condition
	}

	/**
	 * Checks if this bag is equal to another bag. Two bags are equal if they
	 * contain the same elements with the same frequencies, regardless of order.
	 *
	 * @param otherBag The other bag to compare with.
	 * @return True if both bags are equal, false otherwise.
	 */

	public boolean areEqual(ArrayBag<T> otherBag) {
		// First, if the total number of items differ, the bags can't be equal.
	    if (this.getCurrentSize() != otherBag.getCurrentSize()) {
	        return false;
	    }
	    
	    // Use the unique elements in the current bag.
	    ArrayBag<T> uniqueItems = this.toSet();
	    
	    // For each unique element, check if its frequency in both bags is the same.
	    for (T item : uniqueItems.toArray()) {
	        if (this.getFrequencyOf(item) != otherBag.getFrequencyOf(item)) {
	            return false;
	        }
	    }
	    
	    return true;
	}

	/**
	 * Returns a string representation of this bag.
	 *
	 * @return A string representation of the bag's contents.
	 */
	@Override
	public String toString() {
		StringBuilder result = new StringBuilder("[ ");
		for (int i = 0; i < numberOfEntries; i++) {
			result.append(bag[i]);
			if (i < numberOfEntries - 1) {
				result.append(", ");
			}
		}
		result.append(" ]");
		return result.toString();
	}

} // end ArrayBag

