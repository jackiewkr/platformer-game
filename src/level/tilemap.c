/**
 * tilemap.c
 * =========
 * Tilemap object used to store data about a tile in an easy-to-interface way.
 *
 * By Jacqueline Walker
 * Licensed under the MPL v2.0
 * For more info, see: https://www.mozilla.org/en-US/MPL/2.0/
 **/

#include "tilemap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 2d co-ord to index in to a 1d array */
static int pos_to_index( int x, int y, int w )
{
        return x + w * y;
}

/**
 * struct Tile:
 * Stored data about a given tile. To be extended with more data later.
 **/
struct Tile
{
        int tile;
};

/* Constructor for Tile object */
struct Tile* t_construct( int type )
{
        struct Tile* t = malloc( sizeof(struct Tile) );
        t->tile = type;

        return t;
}

/* Destructor for Tile object */
void t_destruct( struct Tile* t )
{
        free( t );
}

/**
 * struct Tilemap:
 * Represents tile data as a 2D grid when being accessed.
 **/
struct Tilemap
{
        struct Tile** map;
        int w;
        int h;
        int z; //TODO: use for draw order
};

/* Constructor for Tilemap object */
static struct Tilemap* tm_construct( int w, int h, int z )
{
        struct Tilemap* tm = malloc( sizeof(struct Tilemap) );
        tm->w = w;
        tm->h = h;

        tm->map = malloc( sizeof(struct Tile*) * tm->w * tm->h );

        return tm;
}

/* Destructor for Tilemap object */
void tm_destruct( struct Tilemap* tm )
{
        for( int i = 0; i < tm->w * tm->h; i++ )
        {
                if( tm->map[i] != NULL )
                        t_destruct( tm->map[i] );
        }
        free( tm->map );
        free( tm );
}

static void tm_add_tile( struct Tilemap* tm, int index, int tile )
{
        tm->map[index] = t_construct( tile );
}

/* Getters */
int tm_get_tile( struct Tilemap* tm, int w, int h )
{
        if ( w <= tm->w && w >= 0 && h <= tm->h && h >= 0 )
                return tm->map[ pos_to_index( w, h, tm->w ) ]->tile;
        else
                return -1;
}

int tm_getW( struct Tilemap* tm ) { return tm->w; }
int tm_getH( struct Tilemap* tm ) { return tm->h; }

/** ----- FILE I/O ----- **/

/* Reads contents of file from disk and copies tilemap data into a Tilemap object
 * Returns a Tilemap object
 */
struct Tilemap* tm_populate( char* loc )
{
        struct Tilemap* tm = NULL;
        FILE* fptr = fopen( loc, "r" );

        char* line = NULL;
        size_t len = 0;
        ssize_t nread;
        unsigned int index = 0;
        int tok_data[4];
        while (  ( nread = getline( &line, &len, fptr ) ) != -1  )
        {
                /* Iterate through tokens in line and get data */
                char* token = strtok( line, "," );
                int tok_index = 0;
                while ( token != NULL )
                {
                        tok_data[tok_index] = (int) atoi( token );
                        token = strtok( NULL, "," );
                        tok_index++;
                }

                if ( !index )
                {
                        tm = tm_construct( tok_data[0], tok_data[1],
                                           tok_data[3]);
                }
                else
                {
                        tm_add_tile( tm, index-1, tok_data[0] );
                }
                index++;
        }

        return tm;
}

/** ---- level designer ---- **/
struct Tilemap* tm_createBlank()
{
        struct Tilemap* tm = tm_construct( 20, 15, 1 );
	tm->map = malloc( sizeof(struct Tile*) * 20 * 15 );
	for ( int i = 0; i < 20*15; i++ )
	{
                tm->map[i] = t_construct( 0 );
	}

	return tm;
}
void tm_mod_tile( struct Tilemap* tm, int type, int w, int h )
{
        int index = pos_to_index( w, h, tm->w );
	tm->map[index]->tile = type;
}

void tm_export( struct Tilemap* tm, const char* loc )
{
        FILE* fptr = fopen( loc, "w" );
	fprintf( fptr, "20,15,1,8\n" );
	for ( int i = 0; i < tm->w * tm->h; i++ )
	{
		int x = i % tm->w;
		int y = i / tm->w;
		fprintf( fptr, "%i,%i,%i\n", tm->map[i]->tile, x, y );
	}
	fclose( fptr );
	
}
