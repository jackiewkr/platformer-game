#define GRAPHICS_NS

#include "window.h"
#include "../events/error-handler.h"
#include "../../constants.h"

#include <SDL2/SDL_image.h>
#include <json-c/json.h>

struct Img
{
	SDL_Texture* image;
	unsigned int width;
	unsigned int height;
};



struct ImgTex
{
        SDL_Texture* tileset;
	int width;                 //in tiles
	int height;                //in tiles
        int tile_sz;
};

/* freadall()
 * ==========
 * Reads all the contents of a file into a character buffer. buf will be freed
 * before usage.
 *
 * Returns populated char buffer on success, NULL on error.
 * TODO: Fails on non-text files
 */
static char* freadall( FILE* fptr )
{
	char* buf = NULL;
	fseek( fptr, 0, SEEK_END );
	long file_len = ftell( fptr );
	if ( file_len == -1 )
		return NULL;
	
	fseek( fptr, 0, SEEK_SET );
	buf = malloc( sizeof(char) * (file_len + 1) );
	if ( buf == NULL )
		return NULL;
	
	fread( buf, file_len, 1, fptr );
	
	buf[file_len] = '\0';

	return buf;
}
	

/* imgtex_init()
 * =============
 * Initializes an Imgtex object and populates it from the file given. File
 * should be a JSON file with tilemap metadata. See documentation for more
 * details.
 * Returns NULL on error, valid IngTex ptr on success. More details are
 * printed to stderr.
 */
struct ImgTex* imgtex_init( SDL_Renderer* renderer, const char* loc )
{
        struct ImgTex* imgtex = malloc( sizeof(struct ImgTex) );
	if ( imgtex == NULL )
		err_report( FATAL, "Failed to malloc() an ImgTex!" );

	FILE* fptr = fopen( loc, "r" );
	char* buf = freadall( fptr );
	fclose( fptr );
	
	if ( buf == NULL )
		err_report( FATAL, "Failed to freadall() imgtex file!" );

	//parse as json object and extract necessary data
        json_tokener* tok = json_tokener_new();
	json_object* json = json_tokener_parse_ex( tok, buf, strlen( buf ) );
	free( buf );

	json_object* img = json_object_object_get( json, "tileset-img" );
	json_object* width = json_object_object_get( json, "width" );
	json_object* height = json_object_object_get( json, "height" );
        json_object* size = json_object_object_get( json, "tile-size" );
	
        imgtex->width = json_object_get_int( width );
	imgtex->height = json_object_get_int( height );
        imgtex->tile_sz = json_object_get_int( size );
        
        //key background magenta to transparent and load to tex
	SDL_Surface* raw_tileset = IMG_Load( json_object_get_string( img ) );
        
        uint32_t rgb_key = SDL_MapRGB( raw_tileset->format, 255, 0, 255 );
        SDL_SetColorKey( raw_tileset, SDL_TRUE, rgb_key );
	
        imgtex->tileset = SDL_CreateTextureFromSurface( renderer, raw_tileset );
        SDL_FreeSurface( raw_tileset );

        return imgtex;
}

void imgtex_free( struct ImgTex* imgtex )
{
        SDL_DestroyTexture( imgtex->tileset );
	free( imgtex );
}

SDL_Texture* imgtex_getTex( struct ImgTex* imgtex )
{
	return imgtex->tileset;
}

SDL_Rect imgtex_getTilePos( struct ImgTex* imgtex, int tile )
{
	int x = (tile-1) % imgtex->width;
        int y = (tile-1) / imgtex->width;

	SDL_Rect rect = { x * imgtex->tile_sz, y * imgtex->tile_sz, 
                          imgtex->tile_sz, imgtex->tile_sz };
	return rect;
}
