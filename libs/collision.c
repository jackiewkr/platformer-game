#include <stdio.h>

#include "collision.h"
#include "tilemap.h"
#include "point.h"
#include "constants.h"

#define FUDGE_VAL ( 2 )

/* Helper func; returns 0 if p in tile */
static unsigned int coll_doColl( struct Point p, struct Tilemap* tm )
{
        /* convert world position to tile position */
        struct Point tp;
        tp.x = ( (int)p.x / TILE_SZ );
        tp.y = ( (int)p.y / TILE_SZ );

        /* check given tile at pos */
        fprintf( stderr, "( %f,%f )", tp.x, tp.y );
        fprintf( stderr, ": %i\n", tm_get_tile( tm, tp.x, tp.y ));
        if ( tm_get_tile( tm, tp.x, tp.y ) != 0 )
                return 1;
        return 0;
}

int coll_hasCollided( struct Point p, struct Tilemap* tm )
{
        /* Check if colliding at curr pos */
        if ( coll_doColl( p, tm ) == 1 )
                return 1; /* x and y */

        #if 0
        /* fudge position to check if close to hitting tile */
        /* x */
        p.x += FUDGE_VAL;
        if ( coll_doColl( p, tm ) )
                return 1;
        p.x -= 2*FUDGE_VAL;
        if ( coll_doColl( p, tm ) )
                return -1;

        /* y */
        p.y += FUDGE_VAL;
        if ( coll_doColl( p, tm ) )
                return 2;
        p.y -= 2*FUDGE_VAL;
        if ( coll_doColl( p, tm ) )
                return -2;
        #endif
        return 0;
}

#if 0
int coll_isGrounded( struct Point p, struct Tilemap* tm )
{}
#endif
