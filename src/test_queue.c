/* test_queue.c
 * ============
 * Tests the queue implementation
 */

#include "system/structures/queue.h"
#include <stdio.h>

int main( void )
{
        struct Queue* q = dq_init();
        char a[16] = "Hello";
        char b[16] = "World";
        char c[16] = "And";
        char d[16] = "Computers";

        dq_add( q, (void*)a );
        dq_add( q, (void*)b );
        dq_add( q, (void*)c );
        dq_add( q, (void*)d );

        for ( int i = 0; i < dq_getSz( q ); i++ )
        {
                printf( "%s\n", (char*)dq_get( q ) );
        }

        dq_free( q );

        return 0;
}
