/*-------------------
 * Rainfall Statistics program
 * CIS - 165 Assignment 4
 * Simon Bruce
 *-------------------*/

#include <iostream>
#include <string>
using namespace std;

/*----------------------
 * Global Variables and constants
 *----------------------*/

// Default size of our array
const int MONTHS = 12;

// Numbers of the month with the highest/lowest rainfall
int highestRainMonth; 
int lowestRainMonth;

// Month Names Array
const string monthNames[MONTHS] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

/*--------------------
 * Function Prototypes
 *--------------------*/

void getRainfallExtremes(double[], int &, int &);
double getTotalRainfall(double[]);
double getAverageRainfall(double[]);
bool isValidRainAmount(double);
void testAll();


/*-------------------------
 * Main function, change runTest to true in order to activate testing
 *-------------------------*/

int main()
{
	double rainfall[MONTHS]; // Initialize our array: Months are numbered from 1-12, but indexes go from 0-11

	bool runTests = true;
	if (runTests) {
		testAll();
		exit(0);
	}

	// Get rainfall for each month from the user, and store it in the array
	for (int x = 0; x < MONTHS; x++) {
		while (true) {
			cout << "Rainfall for " << monthNames[x] << ":\n"; // Increment index so January is month 1, etc
			cin >> rainfall[x];
			if (cin.fail()) {
				cout << "Invalid input!\n";
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			if (!isValidRainAmount(rainfall[x])) {
				cout << "Rainfall amount cannot be negative!\n";
				continue;
			}
			break;
		}
	}
	// Output statistics such as Highest Month, Lowest Month, etc
	getRainfallExtremes(rainfall, highestRainMonth, lowestRainMonth);
	cout << "Month with the highest rainfall: " << monthNames[highestRainMonth] << "\n";
	cout << "Month with the lowest rainfall: " << monthNames[lowestRainMonth] << "\n";

	cout << "Average rainfall for the year: " << getAverageRainfall(rainfall) << "\n";
	cout << "Total rainfall this year: " << getTotalRainfall(rainfall) << "\n";
}

/*------------------------
 * Function Definitions
 *------------------------*/

/*--------------------------
 * Check if rainfall amount is valid (Must be > 0).
 *-------------------------*/

bool isValidRainAmount(double rainAmount) {
	if (rainAmount >= 0) {
		return true;
	}
	return false;
}


/*--------------------------
 * Find which months have the highest/lowest amount of rainfall.
 *
 * highestRainMonth and lowestRainMonth are modified by this function.
 *-------------------------*/

void getRainfallExtremes(double rainfall[], int &highestRainMonth, int &lowestRainMonth) { 
	highestRainMonth = 0;
	lowestRainMonth = 0;
	double previousHighestRainfall = rainfall[0]; // Initialize to first month
	double previousLowestRainfall = rainfall[0];
	for (int x = 0; x < MONTHS; x++) {
		if (rainfall[x] >= previousHighestRainfall) {
			highestRainMonth = x;
			previousHighestRainfall = rainfall[x];
		}
		if (rainfall[x] <= previousLowestRainfall) {
			lowestRainMonth = x;
			previousLowestRainfall = rainfall[x];
		}
	}
}

/*--------------------------
 * Gets the average rainfall for the year
 *-------------------------*/
double getAverageRainfall(double rainfall[]) {
	double average = 0;
	for (int x = 0; x < MONTHS; x++) {
		average += rainfall[x];
	}
	average /= MONTHS;
	return average;
}

/*--------------------------
 * Gets the total rainfall for the year
 *-------------------------*/
double getTotalRainfall(double rainfall[]) {
	double total = 0;
	for (int x = 0; x < MONTHS; x++) {
		total += rainfall[x];
	}
	return total;
}

/*------------------
 * Testing Function
 *------------------*/

void testAll()
{
	
	bool pass = true;

	// Rainfall should not be negative
	if (!isValidRainAmount(-1)) {
		// Test will pass if -1 is invalid
	}
	else {
		cout << "Error: rainfall of -1 returns true\n";
		pass = false;
	}

	// Rainfall should be >= 0
	if (isValidRainAmount(0)) {
		// Test will pass if 0 is valid
	}
	else {
		cout << "Error: rainfall of 0 returns false\n";
		pass = false;
	}

	// Average Rainfall should be 5.5 when rainfall[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
	double testArray1[MONTHS] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	if (getAverageRainfall(testArray1) == 5.5) {
		// Test will pass if average = 5.5
	}
	else {
		cout << "Error: average rainfall for testArray1 =/= 5.5\n";
		pass = false;
	}

	// Total Rainfall should be 66 
	if (getTotalRainfall(testArray1) == 66) {
		// Test will pass if total = 66
	}
	else {
		cout << "Error: total rainfall for testArray1 =/= 66\n";
		pass = false;
	}

	// January should have the lowest rainfall and December should have the highest 
	getRainfallExtremes(testArray1, highestRainMonth, lowestRainMonth);

	if (highestRainMonth == 11 && lowestRainMonth == 0) {

	}
	else {
		cout << "Error: highestRainMonth or lowestRainMonth =/= 11 or 0 respectively (Ascending)\n";
		pass = false;
	}

	// January should have the highest rainfall and December should have the lowest for descending rainfall[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
	double testArray2[MONTHS] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	getRainfallExtremes(testArray2, highestRainMonth, lowestRainMonth);

	if (highestRainMonth == 0 && lowestRainMonth == 11) {

	}
	else {
		cout << "Error: highestRainMonth or lowestRainMonth =/= 0 or 11 respectively (Descending)\n";
		pass = false;
	}

	// January should have the lowest rainfall and February should have the highest for alternating ascending rainfall[] = {0, 11, 1, 10, 2, 9, 3, 8, 4, 7, 5, 6}
	double testArray3[MONTHS] = { 0, 11, 1, 10, 2, 9, 3, 8, 4, 7, 5, 6 };
	getRainfallExtremes(testArray3, highestRainMonth, lowestRainMonth);

	if (highestRainMonth == 1 && lowestRainMonth == 0) {
		
	}
	else {
		cout << "Error: highestRainMonth or lowestRainMonth =/= 1 or 0 respectively (Alternating Ascending)\n";
		pass = false;
	}

	// January should have the highest rainfall and February should have the lowest for alternating descending rainfall[] = {11, 0, 10, 1, 9, 2, 8, 3, 7, 4, 6, 5}
	double testArray4[MONTHS] = { 11, 0, 10, 1, 9, 2, 8, 3, 7, 4, 6, 5 };
	getRainfallExtremes(testArray4, highestRainMonth, lowestRainMonth);

	if (highestRainMonth == 0 && lowestRainMonth == 1) {

	}
	else {
		cout << "Error: highestRainMonth or lowestRainMonth =/= 0 or 1 respectively (Alternating Descending)\n";
		pass = false;
	}

	// December should be both the highest and lowest for same amount rainfall[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	double testArray6[MONTHS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	getRainfallExtremes(testArray6, highestRainMonth, lowestRainMonth);

	if (highestRainMonth == 11 && lowestRainMonth == 11) {

	}
	else {
		cout << "Error: highestRainMonth and lowestRainMonth =/= 11 (Same amount rainfall)\n";
		pass = false;
	}

	// December should be both the highest and lowest for same amount rainfall[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}
	double testArray7[MONTHS] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
	getRainfallExtremes(testArray7, highestRainMonth, lowestRainMonth);

	if (highestRainMonth == 11 && lowestRainMonth == 11) {

	}
	else {
		cout << "Error: highestRainMonth and lowestRainMonth =/= 11 (Same amount rainfall)\n";
		pass = false;
	}

	if (!pass) {
		cout << "Failure: One or more tests did not pass.\n";
	}
	else {
		cout << "Success: All tests pass.\n";
	}
}