#include <stdio.h>
#include <stdlib.h>

#include "building.h"


// This function creates the floors of a Building
void createFloors(Building *aBuilding) {
	// Add the 1st floor plan
	char  temp1[HEIGHT][WIDTH+1] =
			{"111111111111111111111",
			 "100000100000100000001",
			 "100001110000100000001",
			 "100002010000100000001",
			 "111111011121121111111",
			 "100010000000000020001",
			 "100010112111111110001",
			 "100020100000100010001",
			 "100010100000100010001",
			 "111110100000100010001",
			 "100010100000100111211",
			 "100010100000100200001",
			 "100010111121111101211",
			 "100020000000000001001",
			 "111110000000001121111",
			 "100020000000001000001",
			 "100010000000001000001",
			 "100012110000001000001",
			 "100010010000001000001",
			 "100010010000001000001",
			 "111111111122111111111"};
	aBuilding->floors[0].numDoors = 0;
	aBuilding->floors[0].roomList = NULL;
	aBuilding->floors[0].doors = NULL;
	for (int r=0;r<HEIGHT; r++)
		for (int c=0; c<WIDTH; c++)
			aBuilding->floors[0].grid[r][c] = temp1[r][c];

	// Add the 2nd floor plan
	char temp2[HEIGHT][WIDTH+1] =
			{"111111111111111111111",
			 "100010000000000010001",
			 "100020000000000020001",
			 "100010000000000011211",
			 "100011111121111110001",
			 "100010001000100010001",
			 "100010001000100011111",
			 "100011211111112110001",
			 "100010000000000010001",
			 "100010000000000020001",
			 "100011211000112110001",
			 "100010001000100011111",
			 "100010001000100010001",
			 "100011111000111110001",
			 "100010000000000020001",
			 "100010000000000010001",
			 "100011211000111111111",
			 "100010001000100010001",
			 "100020001000200020001",
			 "100010001000100010001",
			 "111111111121111111111"};
	aBuilding->floors[1].numDoors = 0;
	aBuilding->floors[1].roomList = NULL;
	aBuilding->floors[1].doors = NULL;
	for (int r=0;r<HEIGHT; r++)
		for (int c=0; c<WIDTH; c++)
			aBuilding->floors[1].grid[r][c] = temp2[r][c];

	// Add the 3rd floor plan
	char temp3[HEIGHT][WIDTH+1] =
			{"111111111111111111111",
			 "100010000000000010001",
			 "100020000000000020001",
			 "111110011121110011111",
			 "100010010000010010001",
			 "100020011111110020001",
			 "111110020010020011111",
			 "100010010010010010001",
			 "100020011111110020001",
			 "111110020010020011111",
			 "200000010010010000002",
			 "111110011111110011111",
			 "100010020010020010001",
			 "100020010010010020001",
			 "111110011111110011111",
			 "100010020010020010001",
			 "100020010010010020001",
			 "111110011111110011111",
			 "100010000000000010001",
			 "100020000000000020001",
			 "111111111121111111111"};
	aBuilding->floors[2].numDoors = 0;
	aBuilding->floors[2].roomList = NULL;
	aBuilding->floors[2].doors = NULL;
	for (int r=0;r<HEIGHT; r++)
		for (int c=0; c<WIDTH; c++)
			aBuilding->floors[2].grid[r][c] = temp3[r][c];

	// Add the 4th floor plan
	char temp4[HEIGHT][WIDTH+1] =
			{"111111111111111111111",
			 "100010000010000010001",
			 "100020000020000020001",
			 "100010000010000010001",
			 "112111121111121111211",
			 "100010000010000010001",
			 "100010000010000010001",
			 "100010000010000010001",
			 "112110000010000011211",
			 "100010000010000010001",
			 "100010000010000010001",
			 "100011121111121110001",
			 "112110000010000011211",
			 "100010000010000010001",
			 "100010000020000010001",
			 "100010000010000010001",
			 "112110000010000011211",
			 "100011111111111110001",
			 "100010000000000010001",
			 "100020000000000020001",
			 "111111111121111111111"};
	aBuilding->floors[3].numDoors = 0;
	aBuilding->floors[3].roomList = NULL;
	aBuilding->floors[3].doors = NULL;
	for (int r=0;r<HEIGHT; r++)
		for (int c=0; c<WIDTH; c++)
			aBuilding->floors[3].grid[r][c] = temp4[r][c];

	// Add the 5th floor plan
	char temp5[HEIGHT][WIDTH+1] =
			{"111111111111111111111",
			 "100010000010000010001",
			 "100010000010000010001",
			 "100010001111100010001",
			 "100011211000112110001",
			 "100010001000100010001",
			 "100020002000200020001",
			 "100010001000100010001",
			 "111110001000100011211",
			 "100010001000100010001",
			 "100010001121100010001",
			 "100010001000100010001",
			 "100010001000100010001",
			 "100020001111100020001",
			 "100010000000000010001",
			 "111110000000000011111",
			 "100010000000000010001",
			 "100012111000111210001",
			 "100000001000100000001",
			 "100000001000100000001",
			 "111111111121111111111"};
	aBuilding->floors[4].numDoors = 0;
	aBuilding->floors[4].roomList = NULL;
	aBuilding->floors[4].doors = NULL;
	for (int r=0;r<HEIGHT; r++)
		for (int c=0; c<WIDTH; c++)
			aBuilding->floors[4].grid[r][c] = temp5[r][c];
}



// This is where it all begins
int main() {
	Building    building;

	// Initialize the building to have no lists of rooms to begin
	building.offices = NULL;
	building.meetingRooms = NULL;
	building.labs = NULL;
	building.hallways = NULL;
	building.storageRooms = NULL;

	// Create the floors for the building
	createFloors(&building);

	// Compute the graphs for each building plan and add them to a Graph Set
	for (int i=0; i<NUM_FLOORS; i++) {
		findDoors(&(building.floors[i]));
		findRooms(&building, i);
	}

	// Sort out all the rooms and display the results
	sortRooms(&building);

	// Display the room lists
	printRoomList(building.offices, "Office");
	printRoomList(building.meetingRooms, "Meeting Room");
	printRoomList(building.labs, "Lab");
	printRoomList(building.storageRooms, "Storage Room");
	printRoomList(building.hallways, "Hallway");

	// Free all allocated memory
	freeEverything(&building);
}
