#include "../constants.h"
#include "draw_int.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/* chtoi: Takes a char, returns the x pos of the character in the text bmp */
static int chtoi( char ch )
{
        return (int)(ch - 32) * 8;
}

static void draw_char( struct Window* win, char ch, int x, int y )
{
        int fontmap_x = chtoi( ch );

        al_draw_scaled_bitmap( win->text, fontmap_x, 0, 8, 8,
                               x * SCALE, y * SCALE,
                               TEXT_SZ * SCALE, TEXT_SZ * SCALE, 0 );
}

void draw_text( struct Window* win, char* buf, int buf_sz, int x, int y )
{
        int curr_x = x;
        int curr_y = y;
        
        for ( int i = 0; i < buf_sz; i++ )
        {
                if ( buf[i] == '\n' )
                {
                        curr_x = x;
                        curr_y -= TEXT_SZ;
                }
                else
                {
                        draw_char( win, buf[i], curr_x, curr_y );
                        curr_x += TEXT_SZ;
                }
        }
}
