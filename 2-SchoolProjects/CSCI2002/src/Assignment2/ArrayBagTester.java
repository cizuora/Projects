package Assignment2;

/**
 * ArrayBagTester class to test the implementation of ArrayBag methods. This
 * includes testing the 8 methods implemented in ArrayBag.
 * /*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2002
Purpose    : Assignment 2
=================================*/

public class ArrayBagTester {

	public static void main(String[] args) {
		int score = 0;

		// Create test bags
		ArrayBag<String> bag1 = new ArrayBag<>();
		bag1.add("apple");
		bag1.add("banana");
		bag1.add("apple");

		ArrayBag<String> bag2 = new ArrayBag<>();
		bag2.add("banana");
		bag2.add("cherry");

		ArrayBag<String> bag3 = new ArrayBag<>();
		bag3.add("apple");
		bag3.add("apple");
		bag3.add("banana");

		ArrayBag<String> bag4 = new ArrayBag<>();
		bag4.add("apple");
		bag4.add("apple");
		bag4.add("banana");
		bag4.add("banana");

		ArrayBag<String> bag5 = new ArrayBag<>();
		bag5.add("apple");
		bag5.add("apple");
		bag5.add("banana");
		bag5.add("cherry");
		bag5.add("banana");
		bag5.add("banana");

		ArrayBag<String> bag6 = new ArrayBag<>();
		bag6.add("apple");
		bag6.add("banana");
		bag6.add("apple");
		bag6.add("banana");
		bag6.add("cherry");
		bag6.add("banana");

		// Test union
		ArrayBag<String> unionBag = bag1.union(bag2);
		ArrayBag<String> expectedUnion = new ArrayBag<>();
		expectedUnion.add("apple");
		expectedUnion.add("banana");
		expectedUnion.add("apple");
		expectedUnion.add("banana");
		expectedUnion.add("cherry");
		System.out.println("Union test:");
		System.out.println("Expected: " + expectedUnion);
		System.out.println("Actual: " + unionBag);
		if (unionBag.areEqual(expectedUnion)) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Test intersection
		ArrayBag<String> intersectionBag = bag1.intersection(bag2);
		ArrayBag<String> expectedIntersection = new ArrayBag<>();
		expectedIntersection.add("banana");
		System.out.println("Intersection test:");
		System.out.println("Expected: " + expectedIntersection);
		System.out.println("Actual: " + intersectionBag);
		if (intersectionBag.areEqual(expectedIntersection)) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Test difference
		ArrayBag<String> differenceBag = bag1.difference(bag2);
		ArrayBag<String> expectedDifference = new ArrayBag<>();
		expectedDifference.add("apple");
		expectedDifference.add("apple");
		System.out.println("Difference test:");
		System.out.println("Expected: " + expectedDifference);
		System.out.println("Actual: " + differenceBag);
		if (differenceBag.areEqual(expectedDifference)) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Test replace
		boolean replaceResult = bag1.replace("apple", "grape");
		boolean expectedReplace = true;
		System.out.println("Replace test:");
		System.out.println("Bag1 after replace: " + bag1);
		System.out.println("Expected: " + expectedReplace);
		System.out.println("Actual: " + replaceResult);
		if (replaceResult && bag1.contains("grape")) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Test toSet
		ArrayBag<String> setBag = bag4.toSet();
		ArrayBag<String> expectedSet = new ArrayBag<>();
		expectedSet.add("banana");
		expectedSet.add("apple");
		System.out.println("To Set test:");
		System.out.println("Expected: " + expectedSet);
		System.out.println("Actual: " + setBag);
		if (setBag.areEqual(expectedSet)) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Test getMostFrequentItem
		String mostFrequent = bag5.getMostFrequentItem();
		String expectedMostFrequent = "banana";
		System.out.println("Most Frequent Item test:");
		System.out.println("Expected: " + expectedMostFrequent);
		System.out.println("Actual: " + mostFrequent);
		if (mostFrequent.equals(expectedMostFrequent)) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Test isSubsetOf
		boolean isSubset = bag4.isSubsetOf(bag5);
		boolean expectedSubset = true;
		System.out.println("Is Subset test:");
		System.out.println("Bag 4: " + bag4);
		System.out.println("Bag 5: " + bag5);
		System.out.println("Expected: " + expectedSubset);
		System.out.println("Actual: " + isSubset);
		if (isSubset == expectedSubset) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Test areEqual
		boolean areEqual = bag5.areEqual(bag6);
		boolean expectedEqual = true;
		System.out.println("Are Equal test:");
		System.out.println("Bag 5: " + bag5);
		System.out.println("Bag 6: " + bag6);
		System.out.println("Expected: " + expectedEqual);
		System.out.println("Actual: " + areEqual);
		if (areEqual == expectedEqual) {
			System.out.println("Result: PASS");
			score += 3;
		} else {
			System.out.println("Result: FAIL");
		}
		System.out.println();

		// Bonus points for all methods correct
		if (score == 24) {
			score += 1;
			System.out.println("All tests passed! Bonus point awarded.");
		}

		// Display final score
		System.out.println("Final Score: " + score + "/25");
	}
}

