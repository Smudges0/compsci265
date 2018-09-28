//This program calculates which of the four company divisions has the greatest quarterly sales.
#include <iostream>
#include <string> //Necessary in order to concat divName in getSales
using namespace std;

//Function Prototypes
double getSales(string);
void findHighest(double, double, double, double);

//Variables to store each division's total sales
double divNE;
double divSE;
double divNW;
double divSW;

int main() 
{
	divNE = getSales("Northeast");
	divSE = getSales("Southeast");
	divNW = getSales("Northwest");
	divSW = getSales("Southwest");

	findHighest(divNE, divSE, divNW, divSW);

	//end
	return 0;
}

//Function Definitions

/*---------------------
Ask for a division's sales
-----------------------*/
double getSales(string divName) 
{
	double sales;
	bool cont = true;

	do {
		cout << "What is " << divName << " division's quarterly sales figure?\n";
		cin >> sales;
		if (cin.fail()) { // Error catching
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		if (sales < 0) {
			cout << "Invalid input! Amount cannot be less than $0.00.\n";
			continue;
		}
		cont = false;
	} while (cont);
	return sales;
}

/*-----------------------
Compare sales totals and print result message
-----------------------*/
void findHighest(double divNE, double divSE, double divNW, double divSW) 
{
	string divName = "Northeast";
	double highest = divNE; 

	if (divSE > highest)	{
		divName = "Southeast";
		highest = divSE;
	}
	if (divNW > highest) {
		divName = "Northwest";
		highest = divNW;
	}
	if (divSW > highest) {
		divName = "Southwest";
		highest = divSW;
	}

	cout << divName << " had the highest quarterly sales at $" << highest << "\n";
}

