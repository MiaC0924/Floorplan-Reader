#define WIDTH  21                 // width of floor plan grids
#define HEIGHT 21                 // height of floor plan grids

#define NUM_FLOORS   5            // Number of fllors in the building


typedef struct RoomType {
	unsigned char     floor;        // Floor number (1 to NUM_FLOORS-1) that this room is on
	unsigned char     size;         // number of grid cells in the room
	unsigned char     numDoors;     // number of doors the room connects to
	struct RoomType  *nextRoom;     // The next room in the list
} Room;

typedef struct DoorType {
	unsigned char  row;             // grid location  that door lies at
	unsigned char  col;
	Room           *openFromRoom;   // room on one side of the door
	Room           *openToRoom;     // room on other side of the door
} Door;

typedef struct FloorPlanType {
	char           grid[HEIGHT][WIDTH];
	Door          *doors;           // Dynamically-Allocated array doors on this floor
	unsigned char  numDoors;        // Number of doors found on this floor
	Room          *roomList;        // Linked List of rooms on this floor
} FloorPlan;

typedef struct BuildingType {
	FloorPlan     floors[NUM_FLOORS];  // Individual Floors, statically-allocated
	Room         *offices;             // Linked-List of all offices in the building (includes all floors)
	Room         *meetingRooms;        // Linked-List of all meeting rooms in the building (includes all floors)
	Room         *labs;                // Linked-List of all labs in the building (includes all floors)
	Room         *hallways;            // Linked-List of all hallways in the building (includes all floors)
	Room         *storageRooms;        // Linked-List of all storageRooms in the building (includes all floors)
} Building;

// External functions used my the main program
extern void freeEverything(Building *);
extern void findRooms(Building *, int);
extern void findDoors(FloorPlan *);
extern void sortRooms(Building *);
extern void printRoomList(Room *, char *);
