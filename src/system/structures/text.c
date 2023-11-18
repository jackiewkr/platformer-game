#define STRUCTURES_NS

#include "text.h"

#include <stdlib.h>
#include <string.h>

static char* to_stringLit( char* msg, uint8_t size )
{
        char* format_buf = malloc( size + 1 );
        memcpy( format_buf, msg, size );
        format_buf[size] = '\0';

        return format_buf;
}

struct Text
{
        char* message;          //string literal
};

struct Text* text_init( char* message, uint8_t msg_size )
{
        struct Text* text = malloc( sizeof(struct Text) );
        text->message = to_stringLit( message, msg_size );
        
        return text;
}

void text_free( struct Text* text )
{
        free( text->message );
        free(text);
}

char* text_getMsg( struct Text* text )
{
        return text->message;
}
