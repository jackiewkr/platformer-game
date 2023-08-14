#ifndef __DRAW_INT_H
#define __DRAW_INT_H

#include "../draw.h"
#include "../tilemap.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

struct Window
{
        ALLEGRO_DISPLAY * disp;
        /* Bitmaps */
        ALLEGRO_BITMAP* tileset;
        ALLEGRO_BITMAP* text;
};

void draw_text( struct Window* win, char* buf, int buf_sz, int x, int y );

void draw_tilemap( struct Window* win, struct Tilemap* tm );

void draw_actor( struct Window* win, struct Actor* ac );

#endif //__DRAW_INT_H
