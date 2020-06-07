#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "building.h"

void findDoors(FloorPlan *fplan){
	//find the numDoors total
	int numDoors = 0;
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH+1; j++){
			if (fplan->grid[i][j] == '2') numDoors++;
		}
	}

	//sort the number of doors and allocate memory for doors
	fplan->numDoors = numDoors;
	fplan->doors = malloc(numDoors * sizeof *(fplan->doors));

	//find the row and the col of doors and sort the data
	int idx = 0;
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH+1; j++){
			if (fplan->grid[i][j] == '2') {
				fplan->doors[idx].row = i;
				fplan->doors[idx].col = j;
				//printf("the %dth door is on row %d and col %d\n", idx, i, j);
				idx++;
			}
		}
	}
}

/* ------------- NOW WE FIND ROOMS --------------- */
/* ------------- NOW WE FIND ROOMS --------------- */
/* ------------- NOW WE FIND ROOMS --------------- */

//add room function to add a new room into SLList RoomList
Room *initialRoom() {
	Room *newItem = NULL;
	newItem = malloc(sizeof(struct RoomType));

	//initialize data of Node
	newItem->floor = 0;
	newItem->size = 0;
	newItem->numDoors = 0;
	newItem->nextRoom = NULL;

//	if (tail != NULL) {
//		tail->nextRoom = newItem; //add new node at the end of the list
//	}
	//tail = newItem; //move tail to the newest node
	return newItem;
}

//find doors around a room grid
int findDoorOfRoom (FloorPlan *fplan, int i, int j, Room *room){
	for (int ii = 0; ii < 3; ii++){
		for (int jj = 0; jj < 3; jj++){
			if (fplan->grid[i-1+ii][j-1+jj] == '2'){
				for (int idx = 0; idx < fplan->numDoors; idx++){
					if (fplan->doors[idx].row == i-1+ii && fplan->doors[idx].col == j-1+jj){
						//if this door didn't been counted or linked
						if (fplan->doors[idx].openFromRoom != room && fplan->doors[idx].openToRoom != room){
							room->numDoors++; //add one door of room

							if (fplan->doors[idx].openFromRoom != NULL){
								fplan->doors[idx].openToRoom = room;
								return 1;
							}
							fplan->doors[idx].openFromRoom = room;
							return 1;
						}

					}
				}
			}
		}
	}
	return 0;
}

void getRoomSize(FloorPlan *fplan, int i, int j, Room *room){
	if (fplan->grid[i][j] == '0'){
		room->size++;
		fplan->grid[i][j] = '9';

		/* Check around 8 grids when we find a grids has value 0
		 * we won't get out of room since there're walls around
		 * if we find a grid not equals to 0, we won't go to that grid
		 * | ? | ? | ? |
		 * -------------
		 * | ? | 0 | ? |
		 * -------------
		 * | ? | ? | ? |
		 */
		for (int ii = 0; ii < 3; ii++){
			for (int jj = 0; jj < 3; jj++){
				if (fplan->grid[i-1+ii][j-1+jj] == '0'){
					//only when we find a grid around also = 0, we go to that grid
					findDoorOfRoom(fplan,i,j,room);
					getRoomSize(fplan, i-1+ii, j-1+jj, room); //recursive
				}
			}
		}
	}
}

//use above functions to find room, room size and doors
void findRooms(Building *build, int floorNum){
	// set a dummy node as the head of Linked List
	// at the beginning, tail = dummy since there's nothing in the SLList
	FloorPlan *fplan = &build->floors[floorNum];
	Room *dummy = NULL;
	dummy = malloc(sizeof(struct RoomType));
	Room *tail = dummy;

	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH+1; j++){
			if (fplan->grid[i][j] == '0'){
				Room *newItem = initialRoom();
				if (tail == NULL) dummy->nextRoom = newItem;
				else tail->nextRoom = newItem;
				tail = newItem;
				//printf("test\n");

				newItem->floor = floorNum;
				getRoomSize(fplan, i, j, newItem); //recursive function to get the size of room

				//printf("room on %d floor has size %d and doors %d\n", newItem->floor, newItem->size, newItem->numDoors);

			}
		}
	}
	fplan->roomList = dummy->nextRoom;
	//printf("Floor %d, room 01: %d\n",floorNum, fplan->roomList->size);
	//printf("01: %d",fplan->roomList->nextRoom->size);

	free(dummy);

}

// check the type of room with assignment requirements
char checkRoomType (Room *room){
	if (room->size <= 6) return 's';
	if (room->numDoors == 1 && room->size > 6) return 'o';
	if (room->numDoors > 1 && room->numDoors < 4 && room->size >= 30) return 'l';
	if (room->numDoors > 1 && room->numDoors < 4 && room->size < 30) return 'm';
	if (room->numDoors > 4) return 'h';
	return '0';
}

void sortRooms(Building *build){
	// set pointers to point out the curr head of the roomList and the tail of the other lists
	// help to track the current node
	Room *currRoom = NULL;
	Room *currOffice = NULL;
	Room *currMeeting = NULL;
	Room *currLab = NULL;
	Room *currHall = NULL;
	Room *currStorage = NULL;

	for (int i=0; i<NUM_FLOORS; i++) {
		//printf("=============  now we are in the %d floor  =============\n", i);
		currRoom = build->floors[i].roomList;
		while(currRoom != NULL) {
			/* ---------- if Storage Room ---------- */
			if(checkRoomType(currRoom)=='s'){
				if(currStorage == NULL){
					currStorage = currRoom;
					build->storageRooms = currRoom;
					currStorage->nextRoom = NULL;
				}else{
					currStorage->nextRoom = currRoom;
					currStorage = currStorage->nextRoom;
					currStorage->nextRoom = NULL;
				}
				//printf("added a room to storage list with size %d\n", currStorage->size);
			}

			/* ---------- if Meeting Room ---------- */
			if(checkRoomType(currRoom)=='m'){
				if(currMeeting == NULL){
					currMeeting = currRoom;
					build->meetingRooms = currRoom;
					currMeeting->nextRoom = NULL;
				}else{
					currMeeting->nextRoom = currRoom;
					currMeeting = currMeeting->nextRoom;
					currMeeting->nextRoom = NULL;
				}
				//printf("added a room to meeting list with size %d\n", currMeeting->size);
			}

			/* ---------- if Office Room ---------- */
			if(checkRoomType(currRoom)=='o'){
				if(currOffice == NULL){
					currOffice = currRoom;
					build->offices = currRoom;
					currOffice->nextRoom = NULL;
				}else{
					currOffice->nextRoom = currRoom;
					currOffice = currOffice->nextRoom;
					currOffice->nextRoom = NULL;
				}
				//printf("added a room to office list with size %d\n", currOffice->size);
			}

			/* ---------- if hallways ---------- */
			if(checkRoomType(currRoom)=='h'){
				if(currHall == NULL){
					currHall = currRoom;
					build->hallways = currRoom;
					currHall->nextRoom = NULL;
				}else{
					currHall->nextRoom = currRoom;
					currHall = currLab->nextRoom;
					currHall->nextRoom = NULL;
				}
				//printf("added a room to hallway list with size %d\n", currHall->size);
			}


			/* ---------- if labs Room ---------- */
			if(checkRoomType(currRoom)=='l'){
				if(currLab == NULL){
					currLab = currRoom;
					build->labs = currRoom;
					currLab->nextRoom = NULL;
				}else{
					currLab->nextRoom = currRoom;
					currLab = currLab->nextRoom;
					currLab->nextRoom = NULL;
				}
				//printf("added a room to lab list with size %d\n", currLab->size);
			}

			currRoom = currRoom->nextRoom;
		}
	}
}

void printRoomList(Room *roomList, char *roomType){
	Room *curr = NULL;
	//check roomType first
	if(strcmp(roomType, "Office")==0){
		//set curr on the head of SLList, if curr is not NULL, print
		curr = roomList;
		while(curr != NULL) {
			printf("Office (on floor %d) with %d square feet and %d doors\n", curr->floor, curr->size, curr->numDoors);
			//mode curr to the next node, this while loop will action untill curr == NULL
			curr = curr->nextRoom;
		}
	} else if(strcmp(roomType, "Meeting Room")==0){
		curr = roomList;
		while(curr != NULL) {
			printf("Meeting Room (on floor %d) with %d square feet and % doors\n", curr->floor, curr->size, curr->numDoors);
			curr = curr->nextRoom;
		}
	} else if(strcmp(roomType, "Lab")==0){
		curr = roomList;
		while(curr != NULL) {
			printf("Lab (on floor %d) with %d square feet and %d doors\n", curr->floor, curr->size, curr->numDoors);
			curr = curr->nextRoom;
		}
	} else if(strcmp(roomType, "Storage Room")==0){
		curr = roomList;
		while(curr != NULL) {
			printf("Storage Room (on floor %d) with %d square feet and %d doors\n", curr->floor, curr->size, curr->numDoors);
			curr = curr->nextRoom;
		}
	} else if(strcmp(roomType, "Hallway")==0){
		curr = roomList;
		while(curr != NULL) {
			printf("Hallway (on floor %d) with %d square feet and %d doors\n", curr->floor, curr->size, curr->numDoors);
			curr = curr->nextRoom;
		}
	}
}

//free memory
void freeEverything(Building *build){
	free(build->labs);
	free(build->hallways);
	free(build->offices);
	free(build->meetingRooms);
	free(build->storageRooms);
	//free(build);
}