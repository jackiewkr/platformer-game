/**
 * physics.c
 * =========
 * Generic physics system for use with the engine. Any object which needs
 * to interact with the world should include a Physics_Obj within their struct.
 *
 * By Jacqueline Walker
 * Licensed under the MPL v2.0
 * For more info, see: https://www.mozilla.org/en-US/MPL/2.0/
 **/

#include "physics.h"
#include "tilemap.h"
#include "constants.h"
#include "collision.h"

#include <stdlib.h>
#include <stdio.h>

struct Physics_Obj
{
        struct Point pos;
        struct Point vel;
        struct Point acc;
        struct Point size;
        long int tick_cnt; //counter for ticks
};

struct Physics_Obj* ph_construct( int w, int h )
{
        struct Physics_Obj* pho = malloc( sizeof(struct Physics_Obj) );
        pho->tick_cnt = 0;
        pho->pos = pnt_init( 0.0, 0.0, 0.0 );
        pho->vel = pnt_init( 0.0, 0.0, 0.0 );
        pho->size = pnt_init( (double)w, (double)h, 0.0 );
        
        return pho;
}

void ph_destruct( struct Physics_Obj* pho )
{
        free( pho );
}

struct Point ph_get_pos( struct Physics_Obj* pho )
{
        return pho->pos;
}

struct Point ph_get_vel( struct Physics_Obj* pho )
{
        return pho->vel;
}

struct Point ph_get_acc( struct Physics_Obj* pho )
{
        return pho->acc;
}

struct Point ph_get_size( struct Physics_Obj* pho )
{
        return pho->size;
}

void ph_set_pos( struct Physics_Obj* pho, struct Point p )
{
        pho->pos = pnt_init( p.x, p.y, p.z );
}

void ph_set_vel( struct Physics_Obj* pho, struct Point p, int rel )
{
        if ( rel )
        {
                pho->vel.x = (p.x == 0) ? pho->vel.x : p.x;
                pho->vel.y = (p.y == 0) ? pho->vel.y : p.y;
                pho->vel.z = (p.z == 0) ? pho->vel.z : p.z;
        }
        else
                pho->vel = pnt_init( p.x, p.y, p.z );
}

void ph_set_acc( struct Physics_Obj* pho, struct Point p )
{
        pho->acc = pnt_init( p.x, p.y, p.z );
}

void ph_copy( struct Physics_Obj* dest, struct Physics_Obj* source )
{
        ph_set_pos( dest, source->pos );
        ph_set_vel( dest, source->vel, 0 );
        ph_set_acc( dest, source->acc );
}

#if 0
/* For each sub-tick, calculate the new position using a given position and
 * the physics object's vel and acc 
 */
static struct Point ph_doSubTick( struct Physics_Obj* pho, struct Point pos )
{
        const float SUBTICK_FPS = FPS * COLL_STEPS;
        
        pho->vel.x = pho->vel.x + pho->acc.x / SUBTICK_FPS;
        pho->vel.y = pho->vel.y + pho->acc.y / SUBTICK_FPS;

        /* damping */
        pho->vel.x /= ( 1 + DAMP_COEFF / SUBTICK_FPS );
        /* terminal velocity */
        if ( pho->vel.y > TERM_VEL )
                pho->vel.y = TERM_VEL;

        pos.x += pho->vel.x / SUBTICK_FPS;
        pos.y += pho->vel.y / SUBTICK_FPS;

        return pos;
}

/* For a given physics object, calculate physics for that frame in 4 sub-ticks.
 * If the player will collide on any axis, prevent the player from moving on 
 * that axis
 */
void ph_tick( struct Physics_Obj* pho, struct Tilemap* tm )
{
        struct Point temp_pos = pho->pos;
        for ( int i = 0; i < COLL_STEPS; i++ )
        {
                /* get theoretical position at this sub-tick */
                struct Point th_temp_pos = ph_doSubTick( pho, temp_pos );

                /* check if collision occurs */
                int coll = coll_hasCollided( temp_pos, tm );
                fprintf( stderr, "%i\n", coll );
                switch ( coll )
                {
                case -1:
                case 1: /* x-axis only coll */
                        temp_pos.y = th_temp_pos.y;
                        pho->vel.x = 0;
                        break;
                case -2:
                case 2: /* y-axis only coll */
                        temp_pos.x = th_temp_pos.x;
                        pho->vel.y = 0;
                        break;
                case 3: /* both axes coll */
                        pho->vel.x = 0;
                        pho->vel.y = 0;
                        break;
                default:
                        temp_pos = th_temp_pos;
                        break;
                }
        }

        ph_set_pos( pho, temp_pos );
        fprintf( stderr, "TICK: ( %f, %f )\n", pho->pos.x, pho->pos.y );
}
#endif

void ph_calcNewPos( struct Physics_Obj* pho, struct Tilemap* tm )
{
        pho->vel.x = pho->vel.x + pho->acc.x / FPS;
        if ( !coll_hasCollided( pho->pos, tm ) )
                pho->vel.y = pho->vel.y + pho->acc.y / FPS;

        /* damping */
        pho->vel.x /= ( 1 + DAMP_COEFF / FPS );
        /* terminal velocity */
        if ( pho->vel.y > TERM_VEL )
                pho->vel.y = TERM_VEL;

        pho->pos.x += pho->vel.x / FPS;
        pho->pos.y += pho->vel.y / FPS;
}

void ph_tick( struct Physics_Obj* pho, struct Tilemap* tm )
{
        struct Point pho_size = ph_get_size( pho );
        struct Physics_Obj* new_pho = ph_construct( (int)pho_size.x,
                                                    (int)pho_size.y );
        ph_copy( new_pho, pho );
        ph_calcNewPos( new_pho, tm );
        
        if ( coll_hasCollided( new_pho->pos, tm ) )
        {}
        else
        {
                ph_copy( pho, new_pho );
        }
        ph_destruct( new_pho );
}
