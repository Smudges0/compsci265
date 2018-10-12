/*-------------------
* Standard c++ includes/setup
-------------------*/

#include <iostream>
#include <string>
using namespace std;

/*----------------------
* Global Variables and constants
----------------------*/

// Default size of our array
const int MONTHS = 12;

// Numbers of the month with the highest/lowest rainfall
int highestRainfall; 
int lowestRainfall;

/*--------------------
* Function Prototypes
--------------------*/

void rainfallExtremes(double[], int &, int &);
double totalRainfall(double[]);
double averageRainfall(double[]);
bool isValidRain(double);

/*-------------------------
* Main function, change runTest to true in order to activate testing
-------------------------*/

int main()
{
	double rainfall[MONTHS]; // Initialize our array

	// Fill our array with user inputs
	for (int x = 0; x < MONTHS; x++) {
		while (true) {
			cout << "Rainfall for month " << x+1 << ":\n";
			cin >> rainfall[x];
			if (cin.fail()) {
				cout << "Invalid input!\n";
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			if (!isValidRain(rainfall[x])) {
				cout << "Rainfall amount cannot be negative!\n";
				continue;
			}

			break;
		}
	}

	rainfallExtremes(rainfall, highestRainfall, lowestRainfall);
	cout << "Month with the highest rainfall: " << highestRainfall << "\n";
	cout << "Month with the lowest rainfall: " << lowestRainfall << "\n";

	cout << "Average rainfall for the year: " << averageRainfall(rainfall) << "\n";
	cout << "Total rainfall this year: " << totalRainfall(rainfall) << "\n";
}

/*------------------------
* Function Definitions
------------------------*/

bool isValidRain(double rainAmount) {
	if (rainAmount >= 0) {
		return true;
	}
	return false;
}

void rainfallExtremes(double rainfall[], int &highestRainfall, int &lowestRainfall) {
	highestRainfall = 0;
	lowestRainfall = 0;
	double previousRainfall = 0;
	for (int x = 0; x < MONTHS; x++) {
		if (rainfall[x] >= previousRainfall) {
			highestRainfall = x + 1;
		}
		if (rainfall[x] <= previousRainfall) {
			lowestRainfall = x + 1;
		}
		previousRainfall = rainfall[x];
	}
}

double averageRainfall(double rainfall[]) {
	double average = 0;
	for (int x = 0; x < MONTHS; x++) {
		average += rainfall[x];
	}
	average /= MONTHS;
	return average;
}

double totalRainfall(double rainfall[]) {
	double total = 0;
	for (int x = 0; x < MONTHS; x++) {
		total += rainfall[x];
	}
	return total;
}

/*------------------
* Testing Function
------------------*/

void testAll()
{
	bool pass = true;

	// Rainfall should not be negative
	if (!isValidRain(-1)) {

	}
	else {
		cout << "Error: rainfall of -1 returns true\n";
		pass = false;
	}

	// Rainfall should be >= 0
	if (isValidRain(0)) {

	}
	else {
		cout << "Error: rainfall of 0 returns false\n";
		pass = false;
	}
}