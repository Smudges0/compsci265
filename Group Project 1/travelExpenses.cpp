/*-------------------
* Standard c++ includes/setup
-------------------*/

#include <iostream>
#include <string>
using namespace std;

/*----------------
 * I need these three variables to be passed
 * to the foodExpenses() function.
----------------*/

int days;
int departureTime;	// Leaving home
int arrivalTime;	// Arriving back home

/*---------------------------------------
* These two global variables are passed by reference 
* to the foodExpenses() function.
* This is the total amount covered and not covered, respectively.
*
* I assume you'll add this together with the totals from other functions.
------------------------------------------*/

double mealCovered = 0;
double mealNotCovered = 0;

/*-----------------------
* Function Prototypes
------------------------*/
void foodExpenses(int, int, int, double &, double &);
bool isMealAllowed(bool, bool, int, int, int);
bool isValidTime(int);
bool isValidTripLength(int);
bool isValidArrivalTime(int, int, int);
void calculateMealCoverage(double, double, double &, double &);
void testAll();

/*-------------------------------
* Main function only used for debugging purposes
-------------------------------*/

int main()
{
	bool runTest = true;

	if (runTest) {
		testAll();
		exit(0);
	}

	// Ask for trip length and validate inputs
	while (true) {
		cout << "Trip length in days:\n";
		cin >> days;
		if (cin.fail()) {
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		if (!isValidTripLength(days)) {
			cout << "Trip length cannot be less than one!\n";
			continue;
		}

		break;
	} 

	// Ask for departure time and validate inputs
	while (true) {
		cout << "Departure time on first day:\n";
		cin >> departureTime;
		if (cin.fail()) {
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		if (!isValidTime(departureTime)) {
			cout << "Invalid time! Must be 24 hour time between 0 and 2359!\n";
			continue;
		}

		break;
	} 

	// Ask for arrival time and validate inputs
	while (true){
		cout << "Arrival time on last day:\n";
		cin >> arrivalTime;
		if (cin.fail()) {
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		if (!isValidTime(arrivalTime)) {
			cout << "Invalid time! Must be 24 hour time between 0 and 2359!\n";
			continue;
		}
		if (!isValidArrivalTime(arrivalTime, departureTime, days)) {
			cout << "Arrival time must be after departure time for a one day trip!\n";
			continue;
		}

		break;
	}

	// Calculates how much food expense is covered/not covered
	foodExpenses(days, departureTime, arrivalTime, mealCovered, mealNotCovered); // Notice how mealCovered and mealNotCovered do not require an & here, 
																				 // because that part is done in the function definition
	cout << "Total covered expenses: " << mealCovered << "\n";
	cout << "Total uncovered expenses: " << mealNotCovered << "\n";
}


/*---------------------
* Function Definitions
---------------------*/

/*---------------------------------------------------
* foodExpenses() is the function that asks for the cost of each valid meal
* It needs to be passed the trip length (days), departure time and arrival time (in 24h/military time), and two global variables to store the totals
* mealCovered and mealNotCovered are GLOBAL VARIABLES that are passed by reference, they hold the total amout of money covered/not covered by the company.
* The reason I passed by reference is because A FUNCTION CANNOT RETURN TWO VALUES AT A TIME. 
* I passed these variables by reference so that I could edit them while in this function.
* THIS IS WHY foodExpenses() RETURNS A VOID
---------------------------------------------------*/

void foodExpenses(int days, int departureTime, int arrivalTime, double &mealCovered, double &mealNotCovered)
{
	string mealName;
	double mealCost;
	double maxCovered;
	bool isDayOne;
	bool isLastDay;

	const double maxBreakfastCost = 9.00;
	const double maxLunchCost = 12.00;
	const double maxDinnerCost = 16.00;

	for (int x = 1; x <= days; x++) {
		isDayOne = (x == 1);
		isLastDay = (x == days);

		for (int y = 1; y <= 3; y++) {
			//	Check if allowed, if not, continue next loop
			if (!isMealAllowed(isDayOne, isLastDay, y, departureTime, arrivalTime)) {
				continue;
			}
			if (y == 1) {
				mealName = "breakfast";
				maxCovered = maxBreakfastCost;
			}
			else if (y == 2) {
				mealName = "lunch";
				maxCovered = maxLunchCost;
			}
			else {
				mealName = "dinner";
				maxCovered = maxDinnerCost;
			}

			while (true) {
				cout << "Cost of " << mealName << " on day " << x << ":\n";
				cin >> mealCost;
				if (cin.fail()) {
					cout << "Invalid input!\n";
					cin.clear();
					cin.ignore(256, '\n');
					continue;
				}
				if (mealCost < 0) {
					cout << "Cannot enter negative amount!\n";
					continue;
				}

				break;
			} 

			calculateMealCoverage(mealCost, maxCovered, mealCovered, mealNotCovered);
		}
	}
}

/*------------------------------------------
* isMealAllowed() is a helper function called by foodExpenses()
* It needs to be passed the day number, meal number, departure time and arrival time (in 24h/military time)
* It checks whether a meal is covered or not, which is only required on the first/last days of the trip
* THIS FUNCTION IS REQUIRED BY foodExpenses(), PLEASE DON'T FORGET TO INCLUDE IT
------------------------------------------*/

bool isMealAllowed(bool isDayOne, bool isLastDay, int mealNum, int departureTime, int arrivalTime)
{
	const int breakfastTimeDepart = 659;
	const int lunchTimeDepart = 1159;
	const int dinnerTimeDepart = 1759;
	const int breakfastTimeArrive = 800;
	const int lunchTimeArrive = 1300;
	const int dinnerTimeArrive = 1900;

	bool isAllowed = true;

	// For one-day trips, you must run BOTH first day and last day checks.

	isAllowed = false;
	if (isDayOne) {
		if (mealNum == 1) {
			if (departureTime <= breakfastTimeDepart) {
				isAllowed = true;
			}
		}
		if (mealNum == 2) {
			if (departureTime <= lunchTimeDepart) {
				isAllowed = true;
			}
		}
		if (mealNum == 3) {
			if (departureTime <= dinnerTimeDepart) {
				isAllowed = true;
			}
		}
	}

	if (isLastDay) {
		if (mealNum == 1) {
			if (arrivalTime >= breakfastTimeArrive) {
				isAllowed = true;
			}
		}
		if (mealNum == 2) {
			if (arrivalTime >= lunchTimeArrive) {
				isAllowed = true;
			}
		}
		if (mealNum == 3) {
			if (arrivalTime >= dinnerTimeArrive) {
				isAllowed = true;
			}
		}
	}

	return isAllowed;
}

void calculateMealCoverage(double mealCost, double maxCovered, double &mealCovered, double &mealNotCovered)
{
	if (mealCost <= maxCovered) {
		mealCovered += mealCost;
	}
	else {
		mealCovered += maxCovered;
		mealNotCovered += (mealCost - maxCovered);
	}
}

/*-----------------------------------
* This function is used to validate if military time is OK
* Any number over 2359 (11:59 pm) is considered invalid
* Any number with minutes over 59 IE 1070 (10:70 am) is also considered invalid
* This function is not necessary to my part of the project, I was only using this for testing
-----------------------------------*/

bool isValidTime(int time)
{
	const int maxTime = 2359;
	const int maxMins = 59;

	if (time > maxTime || ((time % 100) > maxMins) || time < 0) {
		return false;
	}

	return true;
}

bool isValidTripLength(int days) 
{
	if (days < 1) {
		return false;
	}
	return true;
}

bool isValidArrivalTime(int arrivalTime, int departureTime, int days)
{
	if (days == 1 && (arrivalTime <= departureTime)) {
		return false;
	}
	return true;
}

void testAll()
{
	bool pass = true;

	// Number of days should be > 1
	if (!(isValidTripLength(0))) {
		//cout << "Functioning: Trip length < 1 returns false.\n";
	}
	else {
		cout << "Error: Trip length < 1 returns true.\n";
		pass = false;
	}

	// Number of days should not be negative
	if (isValidTripLength(1)) {
		//cout << "Functioning: Trip length = 1 returns true.\n";
	}
	else {
		cout << "Error: Trip length 1 = returns false.\n";
		pass = false;
	}

	// 2 day trip should be valid - OK
	if (isValidTripLength(2)) {
		//cout << "Functioning: Trip length > 1 returns true.\n";
	}
	else {
		cout << "Error: Trip length > 1 returns false.\n";
		pass = false;
	}

	// Time should be > 0
	if (!(isValidTime(-1))) {
		//cout << "Functioning: Time < 1 returns false.\n";
	}
	else {
		cout << "Error: Time < 1 returns true.\n";
		pass = false;
	}

	// Time should be < 2400
	if (!(isValidTime(2400))) {
		//cout << "Functioning: Time > 2359 returns false.\n";
	}
	else {
		cout << "Error: Time > 2359 returns true.\n";
		pass = false;
	}

	// Minutes should be < 60
	if (!(isValidTime(60))) {
		//cout << "Functioning: Time with minutes > 59 returns false.\n";
	}
	else {
		cout << "Error: Time with minutes > 59 returns true.\n";
		pass = false;
	}

	// Time is 0 - OK
	if (isValidTime(0)) {
		//cout << "Functioning: Time = 0 returns true.\n";
	}
	else {
		cout << "Error: Time = 0 returns false.\n";
		pass = false;
	}

	// Time is a valid time	- OK
	if (isValidTime(1200)) {
		//cout << "Functioning: Valid time returns true.\n";
	}
	else {
		cout << "Error: Valid time returns false.\n";
		pass = false;
	}

	// Arrival time should be after Departure time on one-day trip
	if (!(isValidArrivalTime(800, 900, 1))) {
		//cout << "Functioning: Arrival time < Departure time when days = 1 returns false.\n";
	}
	else {
		cout << "Error: Arrival time < Departure time when days = 1 returns true.\n";
		pass = false;
	}

	// Arrival time should not be equal to Departure time on one-day trip
	if (!(isValidArrivalTime(800, 800, 1))) {
		//cout << "Functioning: Arrival time = Departure time when days = 1 returns false.\n";
	}
	else {
		cout << "Error: Arrival time = Departure time when days = 1 returns true.\n";
		pass = false;
	}

	// Arrival time is allowed to be before Departure time if trip length > 1 - OK
	if (isValidArrivalTime(800, 900, 2)) {
		//cout << "Functioning: Arrival time < Departure time when days > 1 returns true.\n";
	}
	else {
		cout << "Error: Arrival time < Departure time when days > 1 returns false.\n";
		pass = false;
	}

	// Arrival time is allowed to be equal to Departure time if trip length > 1 - OK
	if (isValidArrivalTime(800, 800, 2)) {
		//cout << "Functioning: Arrival time = Departure time when days > 1 returns true.\n";
	}
	else {
		cout << "Error: Arrival time = Departure time when days > 1 returns false.\n";
		pass = false;
	}

	// Arrival time is > Departure time when days = 1 - OK
	if (isValidArrivalTime(800, 700, 1)) {
		//cout << "Functioning: Arrival time > Departure time when days = 1 returns true.\n";
	}
	else {
		cout << "Error: Arrival time > Departure time when days = 1 returns false.\n";
		pass = false;
	}

	// Arrival time is > Departure time when days > 1 - OK
	if (isValidArrivalTime(800, 700, 2)) {
		//cout << "Functioning: Arrival time > Departure time when days > 1 returns true.\n";
	}
	else {
		cout << "Error: Arrival time > Departure time when days > 1 returns false.\n";
		pass = false;
	}

	// One Day trip checks
	// Must check both Departure time and Arrival time meal rules .
	// All meals are allowed except for during certain time periods (deadzone).

	// Breakfast is not allowed if you depart AND arrive between 700 and 759 inclusive.
	// Lunch is not allowed if you depart AND arrive between 1200 and 1259 inclusive.
	// Dinner is not allowed if you depart AND arrive between 1800 and 1859 inclusive.

	// Checking all combinations of departure/arrival times for a one-day trip, and check every meal to see if it is allowed
	
	// Checks departure time from 0000 to 2400 once on the hour, and once during the hour.
	for (int depTime = 0; depTime < 2400; depTime += 1) {
		if (!isValidTime(depTime)) {
			continue;
		}
		// Checks arrival time from departure time + 1, up to 2400. Checks once every hour. (Arrival time can't be before or equal to departure time.)
		for (int arrTime = depTime + 1; arrTime < 2400; arrTime += 1) {
			if (!isValidTime(arrTime)) {
				continue;
			}
			// Check each meal
			for (int testMealNum = 1; testMealNum <= 3; testMealNum++) {
				// Check if meal is not allowed
				if (!isMealAllowed(true, true, testMealNum, depTime, arrTime)) { 
					//cout << "Skips meal " << testMealNum << " when departing at " << depTime << " and arriving at " << arrTime << ".\n";
					// Check if skipped meal is supposed to be skipped because it is in a deadzone
					if ((700 <= depTime && depTime <= 759 && 700 <= arrTime && arrTime <= 759 && testMealNum == 1) // Breakfast
						|| (1200 <= depTime && depTime <= 1259 && 1200 <= arrTime && arrTime <= 1259 && testMealNum == 2)  // Lunch
						|| (1800 <= depTime && depTime <= 1859 && 1800 <= arrTime && arrTime <= 1859 && testMealNum == 3)) // Dinner 
					{
						//cout << "Valid skip.\n";
						continue;
					}
					// The meal was not allowed but it should have been
					cout << "Error, invalid skip. Meal " << testMealNum << " should have been allowed at departure time " << depTime << " and arrival time " << arrTime << ".\n";
					pass = false;
				}
				else 
				{
					// Meal was allowed
					// Check if allowed meal should have been skipped because it was in a deadzone
					if ((700 <= depTime && depTime <= 759 && 700 <= arrTime && arrTime <= 759 && testMealNum == 1) // Breakfast
						|| (1200 <= depTime && depTime <= 1259 && 1200 <= arrTime && arrTime <= 1259 && testMealNum == 2)  // Lunch
						|| (1800 <= depTime && depTime <= 1859 && 1800 <= arrTime && arrTime <= 1859 && testMealNum == 3)) // Dinner 
					{
						cout << "Error, invalid meal allowed. Meal " << testMealNum << " should have been skipped at departure time " << depTime << " and arrival time " << arrTime << ".\n";
						pass = false;
					}
					// The meal was correctly allowed				
				}
			}
		}
	}

	if (pass) {
		cout << "All tests pass.\n";
	}
	else {
		cout << "One or more tests fail.\n";
	}
}