#ifndef TEXT_H_
#define TEXT_H_

struct Text;

struct Text* text_init( char* message, uint8_t msg_sz );

void text_free( struct Text* text );

char* text_getMsg( struct Text* text );

#endif
