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

/*-------------------------------
* Main function only used for debugging purposes
-------------------------------*/

int main()
{
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
		if (days < 1) {
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
		if (days == 1 && (arrivalTime <= departureTime)) {
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
			if (isDayOne || isLastDay) {
				//	Check if allowed on first/last day, if not, continue next loop
				if (!isMealAllowed(isDayOne, isLastDay, y, departureTime, arrivalTime)) {
					continue;
				}
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

			if (mealCost <= maxCovered) {
				mealCovered += mealCost;
			}
			else {
				mealCovered += maxCovered;
				mealNotCovered += (mealCost - maxCovered);
			}
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
	const int breakfastTimeArrive = 801;
	const int lunchTimeArrive = 1301;
	const int dinnerTimeArrive = 1901;

	bool isAllowed = false;

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

	if (time > maxTime || ((time % 100) > maxMins)) {
		return false;
	}

	return true;
}