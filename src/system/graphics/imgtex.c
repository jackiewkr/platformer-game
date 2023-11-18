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
	unsigned int width;                 //in tiles
	unsigned int height;                //in tiles
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

	imgtex->tileset = IMG_LoadTexture( renderer,
					   json_object_get_string( img ) );
	imgtex->width = (unsigned int)json_object_get_int( width );
	imgtex->height = (unsigned int)json_object_get_int( height );
	
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
	unsigned int x = (tile-1) % imgtex->width;
	unsigned int y = (tile-1) / imgtex->width;

	SDL_Rect rect = { x*TILE_SZ, y*TILE_SZ, TILE_SZ, TILE_SZ };
	return rect;
}
