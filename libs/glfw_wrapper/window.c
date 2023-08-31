#include "glfw_wrapper.h"

#include "../error-handler/error-handler.h"
#include "../constants.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

struct Window
{
        GLFWwindow* glfw_window;
};

static void _init_glfw()
{
        if ( !glfwInit() )
        {
                err_report( FATAL, "GLFW failed to initialize." );
        }
}

static void error_callback(int error, const char* description)
{
        err_report( FATAL, description );
}


struct Window* win_init()
{
        /* Initialize GLFW */
        _init_glfw();

        /* Allocate and populate Window struct */
        struct Window* win = malloc( sizeof(struct Window) );
        if ( win == NULL )
                err_report( FATAL, "Could not malloc() Window struct!" );
        
        win->glfw_window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT,
                                             "Platformer Engine", NULL, NULL );
        if ( win->glfw_window == NULL )
                err_report( FATAL, "GLFW Window failed to open." );

        /* Set context */
        glfwMakeContextCurrent( win->glfw_window );

        /* Set error callback */
g        glfwSetErrorCallback( error_callback );
        
        return win;
}

int win_checkCloseState( struct Window* win )
{
        return glfwWindowShouldClose( win->glfw_window );
}

void win_free( struct Window* win )
{
        glfwDestroyWindow( win->glfw_window );
        free( win );
        glfwTerminate();
}

void win_flip( struct Window* win )
{
        glfwSwapBuffers( win->glfw_window );
        glfwPollEvents();
}
