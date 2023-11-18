#ifndef IMGTEX_H_
#define IMGTEX_H_

#ifdef GRAPHICS_NS //namespace only functions

        #include <SDL2/SDL.h>

        struct ImgTex;

        struct ImgTex* imgtex_init( SDL_Renderer*, const char* loc );

        void imgtex_free( struct ImgTex* );

        SDL_Texture* imgtex_getTex( struct ImgTex* );

        SDL_Rect imgtex_getTilePos( struct ImgTex*, int tile );

#endif

#endif //IMGTEX_H_
