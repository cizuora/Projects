package Assignment1;



/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2002
Purpose    : Assignment 1
=================================*/

public class CarAutoTester {
	public static void main(String[] args) {
		int totalPoints = 25;
		int deductedPoints = 0;

		// Test 1: Constructor and getters
		Car car1 = new Car("Honda Civic", 12.5, 30);
		if (!car1.getCarName().equals("Honda Civic") || car1.getFuelTankCapacity() != 12.5 || car1.getMileage() != 30
				|| car1.getGasLevel() != 0) {
			System.out.println("Test 1 failed: Constructor or getters are incorrect.");
			deductedPoints += 5;
		}

		// Test 2: Filling gas within capacity
		car1.fillGas(10);
		if (car1.getGasLevel() != 10) {
			System.out.println("Test 2 failed: Filling gas within capacity is incorrect.");
			deductedPoints += 5;
		}

		// Test 3: Filling gas exceeding capacity
		car1.fillGas(5);
		if (car1.getGasLevel() != 10) { // Gas level should remain 10
			System.out.println("Test 3 failed: Gas overflow handling is incorrect.");
			deductedPoints += 5;
		}

		// Test 4: Drive within gas level
		car1.drive(150); // Consumes 5 gallons
		if (car1.getGasLevel() != 5) {
			System.out.println("Test 4 failed: Driving within gas level is incorrect.");
			deductedPoints += 5;
		}

		// Test 5: Drive exceeding gas level
		car1.drive(180); // Should stop due to insufficient gas
		if (car1.getGasLevel() != 0) { // Gas level should be 0 after stop
			System.out.println("Test 5 failed: Driving exceeding gas level is incorrect.");
			deductedPoints += 5;
		}

		// Test 6: CanDrive method
		car1.fillGas(6);
		if (!car1.canDrive(150) || car1.canDrive(200)) {
			System.out.println("Test 6 failed: CanDrive method is incorrect.");
			deductedPoints += 5;
		}

		// Display results
		int finalScore = totalPoints - deductedPoints;
		System.out.println("Final Score: " + finalScore + "/" + totalPoints);

		if (deductedPoints == 0) {
			System.out.println("All tests passed successfully.");
		} else {
			System.out.println("Some tests failed. Please review the above messages.");
		}
	}
}


