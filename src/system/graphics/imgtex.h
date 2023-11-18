#ifndef IMGTEX_H_
#define IMGTEX_H_

/**
 * imgtex.h
 * ========
 * Wrapper of SDL_Surface to provide image textures
 **/

#include <SDL2/SDL.h>

struct ImgTex;

struct ImgTex* imgtex_init( SDL_Renderer*, const char* loc );

void imgtex_free( struct ImgTex* );

SDL_Texture* imgtex_getTex( struct ImgTex* );

SDL_Rect imgtex_getTilePos( struct ImgTex*, int tile );

#endif //IMGTEX_H_
