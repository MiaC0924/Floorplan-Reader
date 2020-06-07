# Floorplan-Reader
makefile and header file / recursive function / pointers / memory

1. findDoors(FloorPlan *fplan)
- finds all the doors for that floor
- first iterate through the grid and count the number of doors
- then store the numDoors total in the floor plan
- once the doors have been counted, allocate memory for an array that will store exactly that many doors
- The array is stored in the floor plan’s doors pointer
- go through the grid again and fill in this array by setting the row & col of the door in the grid


2. findRooms(Building *build, int floorNum)
- go through the floorPlan’s grid for that floor number to identify its rooms
- go through the grid from left to right (starting at the top row)
- more explanition on comment about how to count the size by a recursive procedure

3. sortRooms(Building *build)
- goes through all pre-computed rooms on all floors and sorts the rooms as being an office, meeting room, lab, storage room or hallway
- go through the roomList lists of each floor plan and build up the 5 linked lists of the building (i.e., the offices, meetingRooms, labs, storageRooms and hallways linked-lists of the building structure)
- The idea is to go through each of the floor plan roomLists and move the room into one of the five room type lists for the building
- The room type is decided by room size
- When the procedure completes, the 5 linked lists of the building are filled up with all rooms in the building and each floor plan’s linked list of rooms is NULL.

4. printRoomList(Room *roomList, char *roomType)
- take a linked list of rooms and a string indicating a room type
- display all the rooms in that list 
- one room at a time showing the room type, floor number, square footage (i.e., 4 times the size) and number of doors

5. freeEverything(Building *build)
- free up all dynamically-allocated memory so that valgrind shows no memory leaks nor errors
