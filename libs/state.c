/**
 * state.c
 * =========
 * State object used to store data about the gamestate and the current level.
 *
 * By Jacqueline Walker
 * Licensed under the MPL v2.0
 * For more info, see: https://www.mozilla.org/en-US/MPL/2.0/
 **/

#include "state.h"
#include "tilemap.h"
#include "point.h"

#include <stdlib.h>

/**
 * struct State:
 * Stores current level.
 **/
struct State
{
        struct Point mouse_pos;
        
        /* Currently loaded tilemaps */
        struct Tilemap* fg_tm;
        struct Tilemap* bg_tm;

        struct Actor** ac_list;
        int list_sz;
};

/* Constructor for State object */
struct State* st_construct()
{
        struct State* st = malloc( sizeof(struct State) );
        return st;
}

/* Destructor for State object */
void st_destruct( struct State* st )
{
        if ( st->fg_tm != NULL )
                tm_destruct( st->fg_tm );
        if ( st->bg_tm != NULL )
                tm_destruct( st->bg_tm );

        //TODO: actor support
        free( st );
}

void st_set_tm( struct State* st, struct Tilemap* tm, int fg )
{
        if (fg)
                st->fg_tm = tm;
        else
                st->bg_tm = tm;
}

struct Tilemap* st_get_tm( struct State* st, int fg )
{
        if (fg)
                return st->fg_tm;
        else
                return st->bg_tm;
}

struct Actor* st_get_ac( struct State* st, int index )
{
        return st->ac_list[index];
}

void st_add_ac( struct State* st, struct Actor* ac )
{
        st->ac_list = realloc( st->ac_list,
                               sizeof(struct Actor**) * st->list_sz+1 );
        st->ac_list[st->list_sz] = ac;
        st->list_sz++;
}

void st_tick_actors( struct State* st )
{
        for( int i = 0; i < st->list_sz; i++ )
        {
                ac_tick( st->ac_list[i], st->bg_tm );
        }
}

void st_moveLeft( struct State* st )
{
        ac_moveLeft( st->ac_list[0] );
}

void st_moveRight( struct State* st )
{
        ac_moveRight( st->ac_list[0] );
}
