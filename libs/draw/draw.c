#include "../draw.h"
#include "../constants.h"
#include "draw_int.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

struct Window* win_construct()
{
        al_init();
	al_init_image_addon();
        al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();

        al_set_new_window_title( "Platformer Engine" );

        struct Window* win = malloc( sizeof(struct Window) );
        win->disp = al_create_display( DISPLAY_WIDTH, DISPLAY_HEIGHT );

        win->tileset = al_load_bitmap( "assets/tileset.bmp" );
        win->text = al_load_bitmap( "assets/font.bmp" );
        al_convert_mask_to_alpha(  win->tileset, al_map_rgb_f( 1, 0, 1 )  );
        al_convert_mask_to_alpha(  win->text, al_map_rgb_f( 1, 0, 1 )  );

        return win;
}

void win_destruct( struct Window* win )
{
        al_destroy_bitmap( win->tileset );
        al_destroy_bitmap( win->text );
        al_destroy_display( win->disp );

        free( win );
}

void win_draw( struct Window* win, struct State* s )
{
        al_clear_to_color( al_map_rgb_f( 0, 0, 0 ) );
        /* bg */
        draw_tilemap( win, st_get_tm( s, 0 ) );
        /* fg */
        //draw_tilemap( win, st_get_tm( s, 1 ) );

        /* test actor draw */
        draw_actor( win, st_get_ac( s, 0 ) );
        
        al_flip_display();
}

void* win_getDisp( struct Window* win )
{
        //SLOPPY!
        return (void*)win->disp;
}
