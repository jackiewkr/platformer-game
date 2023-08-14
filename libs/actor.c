#include "actor.h"
#include "physics.h"
#include "tilemap.h"
#include "point.h"
#include "constants.h"

#include <stdlib.h>
#include <stdio.h>

struct Actor
{
        int type;
        struct Physics_Obj* pho;
        unsigned int active;
};

struct Actor* ac_construct( int type, int x, int y, int z, int w, int h )
{
        struct Actor* ac = malloc( sizeof(struct Actor) );
        ac->type = type;

        ac->pho = ph_construct( w, h );
        ph_set_pos( ac->pho, pnt_init( x, y, z ) );
        ph_set_acc( ac->pho, pnt_init( GRAV_X, GRAV_Y, 0 ) );
        ac->active = 1;

        return ac;
}

void ac_destruct( struct Actor* ac )
{
        ph_destruct( ac->pho );
        free( ac );
}

struct Point ac_getPos( struct Actor* ac )
{
        return ph_get_pos( ac->pho );
}

int ac_getWidth( struct Actor* ac )
{
        return (int)ph_get_size( ac->pho ).x;
}

int ac_getHeight( struct Actor* ac )
{
        return (int)ph_get_size( ac->pho ).y;
}

void ac_tick( struct Actor* ac, struct Tilemap* tm )
{
        fprintf( stderr, "Tick!\n" );
        ph_tick( ac->pho, tm );
}

void ac_moveLeft( struct Actor* ac )
{
        ph_set_vel( ac->pho, pnt_init( -SPEED, 0, 0 ), 1 );
}

void ac_moveRight( struct Actor* ac )
{
        ph_set_vel( ac->pho, pnt_init( SPEED, 0, 0 ), 1 );
}

