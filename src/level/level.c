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
#include "../system/system.h"

struct Tilemap
{
        struct Tile* tilemap;
        uint2d_t dims;
};

struct Tilemap* _tm_init( uint2d_t dims )
{
        struct Tilemap* tm = malloc( sizeof(struct Tilemap) );
        if ( tm == NULL )
                err_report( FATAL, "Tilemap struct failed to malloc()!" );
        
        tm->tilemap = malloc( sizeof(struct Tile) * dims.x * dims.y );
        for (int i = 0; i < dims.x * dims.y; i++ )
        {
                struct Tile t = {0,1,0};
                tm->tilemap[i] = t;
        }
        tm->dims = dims;

        return tm;
}

void _tm_free( struct Tilemap* tm )
{
        free( tm->tilemap );
        free( tm );
}

/* 2d co-ord to index in to a 1d array */
static int pos_to_index( int x, int y, int w )
{
        return x + w * y;
}

struct Tile tm_getTile( struct Tilemap* tm, uint2d_t pos )
{
        return tm->tilemap[ pos_to_index(pos.x, pos.y, tm->dims.x) ];
}

DEV_ONLY void tm_modTile( struct Tilemap* tm, uint2d_t pos, uint8_t type )
{
        tm->tilemap[ pos_to_index( pos.x, pos.y, tm->dims.x ) ].type = type;
}

struct Room
{
        struct Tilemap* fg;
        struct Tilemap* mg;
        struct Tilemap* bg;
        
        uint8_t id;
        uint2d_t dims;
        uint2d_t pos;
};

/* _room_init()
 * ============
 * Initializes a Room struct with the given values.
 * 
 * Returns a Room struct ptr on success, NULL on error. Errors are printed to
 * stderr
 */
static struct Room* _room_init( uint8_t id, uint2d_t pos, uint2d_t dims )
{
        struct Room* room = malloc( sizeof(struct Room) );
        if ( room == NULL )
                err_report( FATAL, "Room failed to malloc()!" );

        room->id = id;

        room->fg = NULL;
        room->mg = NULL;
        room->bg = NULL;

        room->pos = pos;
        room->dims = dims;

        return room;
}

/* _room_free()
 * ============
 * Frees a room struct  and any structs within.
 */
static void _room_free( struct Room* room )
{
        _tm_free( room->fg );
        _tm_free( room->mg );
        _tm_free( room->bg );

        free( room );
}

uint8_t room_getID( struct Room* room )
{
        return room->id;
}

uint2d_t room_getDims( struct Room* room )
{
        return room->dims;
}

uint2d_t room_getPos( struct Room* room )
{
        return room->pos;
}

struct Tilemap* room_getTilemap( struct Room* room, uint8_t index )
{
        switch( index )
        {
        case 0:
                return room->fg;
                break;
        case 1:
                return room->mg;
                break;
        case 2:
                return room->bg;
                break;
        default:
                return NULL;
        }
}

struct Level
{
	struct Room** rooms;		//associative arr of rooms
	struct Graph* room_graph;	//graph of room connections
};

DEV_ONLY struct Level* level_createBlank()
{
        struct Level* l = malloc( sizeof(struct Level) );
        if ( l == NULL )
                err_report( FATAL, "Level failed to malloc()!" );

        l->rooms = malloc( sizeof(struct Room*) * 255 );
        for ( int i = 0; i < 255; i++ )
                l->rooms[i] = NULL;

        l->room_graph = NULL;           //not done when designing levels

        return l;
}

void level_free( struct Level* l )
{
        if ( l->rooms != NULL )         //free rooms in room list if allocated
        {
                for ( int i = 0; i < 255; i++ )
                        if ( l->rooms[i] != NULL )
                                _room_free( l->rooms[i] );
        }
        //TODO: Free room_graph if allocated
        free( l );
}

DEV_ONLY uint8_t level_createRoom( struct Level* level, uint2d_t pos, 
                                   uint2d_t dims )
{
        uint8_t index = 0;
        uint8_t found_empty_idx = 0; //false
        while ( !found_empty_idx )
        {
                if ( level->rooms[index] != NULL )
                        index++;
                else
                        found_empty_idx++;
        }

        level->rooms[index] = _room_init( index, pos, dims );

        return index;
}

struct Room* level_getRoom( struct Level* level, uint8_t id )
{
        return level->rooms[id];
}



