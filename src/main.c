#include "window/window.h"

int main( void )
{
        struct Window* win = window_init();

        while ( !window_shouldClose( win ) )
        {
                window_refresh( win );
        }

        window_free( win );

        return 0;
}
