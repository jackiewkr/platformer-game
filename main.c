/**
 * main.c
 * =========
 * Main file for the platformer game. Handles logic relating to gameticks and
 * calling of functions when needed.
 *
 * By Jacqueline Walker
 * Licensed under the MPL v2.0
 * For more info, see: https://www.mozilla.org/en-US/MPL/2.0/
 **/

#include "libs/glfw_wrapper/glfw_wrapper.h"
#include "libs/error-handler/error-handler.h"

int main()
{
        struct Window* win = win_init();

        while ( !win_checkCloseState( win ) )
        {
                /* Main loop */
                win_flip( win );
        }
        err_report( INFO, "Closing..." );
        win_free( win );
}
