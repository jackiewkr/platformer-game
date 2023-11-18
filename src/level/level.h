#ifndef LEVEL_H_
#define LEVEL_H_

#define DEV_ONLY extern

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

/* level_createBlank() : DEV_ONLY
 * ===================
 * Creates a level struct that is blank for use with level_designer.
 *
 * Returns Level struct.
 */
DEV_ONLY struct Level* level_createBlank();

/* level_load()
 * ============
 * Creates a Level struct and populates the struct with data from the
 * supplied level file.
 *
 * Returns populated struct Level on success, NULL on error. Additional details
 * are printed to stderr.
 */
struct Level* level_load( const char* loc );

/* level_free()
 * ============
 * Frees any memory associated with the struct Level and frees the struct.
 */
void level_free( struct Level* );

/* level_getRoom()
 * ===============
 * Gets the struct Room from a given id. 
 *
 * Returns a struct Room ptr on success, NULL on error. Additional details 
 * are printed to stderr.
 */
struct Room* level_getRoom( struct Level*, uint8_t id );

/* level_getConnectedRooms()
 * =========================
 * Gets any rooms adjacent to the room with the given ID as an array of
 * Room struct ptrs.
 *
 * Returns an array of struct Room ptrs. The last element in the array is a
 * NULL ptr. On error or if no rooms are adjacent, NULL is returned.
 * Additional details are printed to stderr.
 *
 * It is the user's responsibility to free the given array.
 */
struct Room** level_getConnectedRooms( struct Level*, uint8_t id );

/* level_createRoom() : DEV_ONLY
 * ==================
 * Creates a room with the given width and height at the specified position.
 * 
 * Returns the ID of the room just created.
 */
DEV_ONLY uint8_t level_createRoom( struct Level*, 
                                   ui_vec2_t pos, ui_vec2_t dims );

/* room_getTilemap()
 * =================
 * Gets a given tilemap for the given room. The index is from 0-2 (fg,mg,bg).
 *
 * Returns Tilemap struct ptr on success, NULL on error. Additional details are
 * printed to stderr. 
 */
struct Tilemap* room_getTilemap( struct Room*, uint8_t index );

/* room_getID()
 * ============
 * Gets the ID of the given room.
 *
 * Returns the given ID. Errors are printed to stderr.
 */
uint8_t room_getID( struct Room* );

/* room_getDims()
 * ==============
 * Gets the width and height of the given room.
 *
 * Returns the given dimensions. Errors are printed to stderr.
 */
ui_vec2_t room_getDims( struct Room* );

/* room_getPos()
 * ==============
 * Gets the x and y position of the given room.
 *
 * Returns the given position. Errors are printed to stderr.
 */
ui_vec2_t room_getPos( struct Room* );

/* tm_getTile()
 * ============
 * Gets the given tile at a given position on the tilemap. 
 *
 * Returns the given Tile. Errors are printed to stderr. 
 */
struct Tile tm_getTile( struct Tilemap*, ui_vec2_t pos );

/* tm_modTile()
 * ============
 * Modify the tile at the given position to take the given tile type.
 */
DEV_ONLY void tm_modTile( struct Tilemap*, ui_vec2_t pos, uint8_t type );

#endif //LEVEL_H_
