#ifndef __TILEMAP_H
#define __TILEMAP_H

/**
 * tilemap.h
 * =========
 * Header file Tilemap object. Exposes all public functions for Tilemap object.
 *
 * By Jacqueline Walker
 * Licensed under the MPL v2.0
 * For more info, see: https://www.mozilla.org/en-US/MPL/2.0/
 **/

struct Tilemap;

/* Construct and populate Tilemap object with data from a file */
struct Tilemap* tm_populate( char* file );

/* Frees object from memory */
void tm_destruct( struct Tilemap* tm );

/* Get tile data from co-ord in Tilemap obj */
int tm_get_tile( struct Tilemap* tm, int w, int h );

/* Getters */
int tm_getW( struct Tilemap* tm ); //width
int tm_getH( struct Tilemap* tm ); //height

#endif //__TILEMAP_H
