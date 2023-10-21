/**
 * level.c
 * =======
 * Format for storing levels. Allows up to 255 rooms with 3 tilemaps per room.
 * Rooms are connected to each other by having a room that is adjacent to 
 * another room on one of its sides.
 **/

#include <stdlib.h>
#include <stdint.h>

#include "level.h"
#include "../system/structures/graph.h"
#include "../system/system.h"

struct Level
{
	struct Room* rooms;		//associative arr of rooms
	struct Graph* room_graph;	//graph of room connections
};

DEV_ONLY struct Level* level_createBlank()
{
	struct Level* l = malloc( sizeof(struct Level) );
}
