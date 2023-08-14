#include "draw_int.h"
#include "../draw.h"
#include "../actor.h"
#include "../constants.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#if 0
void draw_actor( struct Window* win, struct Actor* ac )
{
        int x1, x2, y1, y2;
        struct Point p = ac_getPos( ac );
        al_draw_filled_circle( p.x * SCALE, p.y * SCALE, 2 * SCALE,
                               al_map_rgb_f( 0, 0, 1 ) );
        x1 = ( (int)p.x / TILE_SZ ) * TILE_SZ * SCALE;
        y1 = ( (int)p.y / TILE_SZ ) * TILE_SZ * SCALE;
        x2 = ( (int)p.x / TILE_SZ + 1 ) * TILE_SZ * SCALE;
        y2 = ( (int)p.y / TILE_SZ + 1 ) * TILE_SZ * SCALE;
        al_draw_rectangle( x1, y1, x2, y2, al_map_rgb_f( 0.5,0.5,0.5 ), 2 );
}
#endif

void draw_actor( struct Window* win, struct Actor* ac )
{
        struct Point pos = ac_getPos( ac );
        int width = ac_getWidth( ac );
        int height = ac_getHeight( ac );

        al_draw_filled_rectangle( pos.x * SCALE, pos.y* SCALE,
                                  (pos.x + width) * SCALE,
                                  (pos.y - height) * SCALE,
                                  al_map_rgb_f( 0,0,1 ) );
}
