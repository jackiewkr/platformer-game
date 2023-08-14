#include "../tilemap.h"
#include "../draw.h"
#include "../constants.h"
#include "draw_int.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>

void draw_tile( int type, struct Window* win, float x, float y )
{
        int tx, ty;
        if (type) //if type != 0
        {
                tx = (type - 1) * TILE_SZ;
                ty = 0;
                al_draw_scaled_bitmap(  win->tileset, tx, ty, TILE_SZ, TILE_SZ,
                                        x * SCALE, y * SCALE,
                                        (TILE_SZ * SCALE), (TILE_SZ * SCALE),
                                        0  );
        }
}

/*
void draw_tilemap():
Draws all the tiles in a given Tilemap object at given (x,y) offset on the
display.
*/
void draw_tilemap( struct Window* win, struct Tilemap* tm )
{
        /* Draws left to right, top to bottom */
        for ( int i = 0; i < tm_getH( tm ); i++ )
        {
                for ( int j = 0; j < tm_getW( tm ); j++ )
                {
                        draw_tile(  tm_get_tile( tm, j, i ), win,
                                    (TILE_SZ * j), (TILE_SZ * i)  );
                }
        }
}

