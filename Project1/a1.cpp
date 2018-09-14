// This program calculates the occupancy of a hotel given its height, number of rooms, and occupied rooms.
#include <iostream>
using namespace std;

int main()
{
	int floors, // How many floors the hotel has
		rooms, //Rooms per floor
		occupied, // Occupied rooms per floor
		totalRooms = 0, // Total Rooms
		totalOccupied = 0, // Total occupied rooms
		unoccupied; // Unoccupied rooms
	double percentage; // Occupancy Percentage
	bool cont = true; //Error checking for minimum value

	// Get number of floors
	do {
		cout << "How many floors does this hotel have?\n";
		cin >> floors;
		if (cin.fail()) {
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		if (floors >= 1) {
			cont = false;
		}
		else {
			cout << "Number of floors cannot be less than one!\n";
		}
	} while (cont);

	// Loop through each floor
	for (int x = 1; x <= floors; x++) {
		cont = true;
		if (x == 13) { // Skip thirteenth floor
			continue;
		}
		// Get number of rooms per floor
		do {
			cout << "How many rooms are there on floor " << x << "?\n";
			cin >> rooms;
			if (cin.fail()) {
				cout << "Invalid input!\n";
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			if (rooms >= 10) {
				totalRooms += rooms;
				cont = false;
			}
			else {
				cout << "Number of rooms cannot be less than ten!\n";
			}
		} while (cont);

		cont = true;
		// Get number of occupied rooms
		do {
			cout << "How many of those rooms are occupied?\n";
			cin >> occupied;
			if (cin.fail()) {
				cout << "Invalid input!\n";
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			if (occupied <= rooms) {
				totalOccupied += occupied;
				cont = false;
			}
			else {
				cout << "Occupied rooms cannot exceed actual rooms!\n";
			}
		} while (cont);
	}

	//Calculate Occupancy Percentage and Unoccupied rooms
	percentage = ((totalOccupied * 1.0) / totalRooms) * 100; // Multiply by 1.0 to keep decimals
	unoccupied = totalRooms - totalOccupied;

	//Output
	cout << "The hotel has " << totalRooms << " rooms. " << totalOccupied << " of them are occupied, leaving " << unoccupied << " unoccupied rooms.\n";
	cout << "the hotel is " << percentage << "% full.\n";

	return 0;
}