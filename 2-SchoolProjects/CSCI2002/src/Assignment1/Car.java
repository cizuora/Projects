package Assignment1;

/*================================
Author     : Chidera Izuora
Class Name : Book
Date       : 03-15-2025
Course     : CS2002
Purpose    : Assignment 1
=================================*/

public class Car {
    private String carName;
    private double mileage;
    private double fuelTankCapacity;
    private double gasLevel;

    // Default constructor
    public Car() {
        this.carName = "Unknown";
        this.mileage = 0;
        this.fuelTankCapacity = 0;
        this.gasLevel = 0;
    }

    // Overloaded constructor 
    //gasLevel was not included in car1
    public Car(String carName, double fuelTankCapacity, double mileage) {
        this.carName = carName;
        this.fuelTankCapacity = fuelTankCapacity;
        this.mileage = mileage;
        this.gasLevel = 0; // Initial gas level is 0
    }

    // Getters
    public String getCarName() {
        return carName;
    }

    public double getMileage() {
        return mileage;
    }

    public double getFuelTankCapacity() {
        return fuelTankCapacity;
    }

    public double getGasLevel() {
        return gasLevel;
    }

    // Setters
    public void setCarName(String carName) {
        this.carName = carName;
    }

    public void setMileage(double mileage) {
        this.mileage = mileage;
    }

    public void setFuelTankCapacity(double fuelTankCapacity) {
        this.fuelTankCapacity = fuelTankCapacity;
    }

    public void setGasLevel(double gasLevel) {
        if (gasLevel <= fuelTankCapacity) {
            this.gasLevel = gasLevel;
        } else {
            this.gasLevel = fuelTankCapacity; // Prevent overfilling
        }
    }

    // toString method
    @Override
    public String toString() {
        return "Car: " + carName + ", Mileage: " + mileage + " mpg, Fuel Tank Capacity: " + fuelTankCapacity + " gallons, Gas Level: " + gasLevel + " gallons";
    }

    // Method to drive a certain distance
    public void drive(double distance) {
        double fuelNeeded = distance / mileage;
        if (fuelNeeded <= gasLevel) {
            gasLevel -= fuelNeeded;
        } else {
            double actualDistance = gasLevel * mileage; // Drive as far as possible
            gasLevel = 0;
            System.out.println("Ran out of gas after driving " + actualDistance + " miles.");
        }
    }

    // Method to check if the car can drive a given distance
    public boolean canDrive(double distance) {
        return gasLevel >= (distance / mileage);
    }

    // Method to fill gas up to the fuel tank capacity
    public void fillGas(double x) {
        if (x <= 0) {
            System.out.println("Invalid gas amount.");
            return;
        }
        else if (gasLevel + x > fuelTankCapacity) {
             // Prevents overflow
        } else {
            gasLevel += x;
        }
    }
}



