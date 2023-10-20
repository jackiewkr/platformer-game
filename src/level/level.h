#ifndef LEVEL_H_
#define LEVEL_H_

#include "../system/structures/vectors.h"

#include <stdint.h>

struct Level;
struct Room;
struct Tilemap;

struct Tile
{
	uint8_t type; //0 means no tile; 255 addressable tiles
	uint8_t is_visible : 1;
	uint8_t is_breakable : 1;
};

struct Level* level_load( const char* loc );

void level_free( struct Level* );

struct Room* level_getRoom( struct Level*, uint8_t id );

struct Room** level_getConnectedRooms( struct Level*, struct Room* );

struct Tilemap* room_getTilemap( struct Room*, int index );

uint8_t room_getID( struct Room* );

ui_vec2_t room_getDims( struct Room* );

ui_vec2_t room_getPos( struct Room* );

struct Tile tm_getTile( struct Tilemap*, ui_vec2_t pos );

#endif //LEVEL_H_
