#include "../system.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void err_report( enum ErrorLevel el, const char* msg )
{
        if ( msg == NULL )
                msg = "";
        //TODO* assume msg isnt string literal and needs sanitize
        switch (el)
        {
        case WARNING:
                fprintf( stderr, "WARNING: %s %s\n", msg, strerror(errno) );
                break;
        case FATAL:
                fprintf( stderr, "FATAL: %s %s\nExiting...\n", msg,
                         strerror(errno) );
                exit(0);
                break;
        case INFO:
        default:
                fprintf( stderr, "INFO: %s\n", msg );
                break;
        }
}
