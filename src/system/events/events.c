#include <SDL2/SDL.h>

#include "../system.h"

struct Event
{
        SDL_Event curr_event;
};

//TODO: neaten up; more modular solution
event_callback_t QUIT_func = NULL;
event_callback_t MOUSEMOVE_func = NULL;
event_callback_t MOUSEDOWN_func = NULL;
event_callback_t MOUSEUP_func = NULL;
event_callback_t KEYDOWN_func = NULL;
event_callback_t KEYUP_func = NULL;

void ev_setCallback( event_callback_t func, enum EventType type )
{
	switch ( type )
	{
	case QUIT:
		QUIT_func = func;
		break;
	case MOUSEMOVE:
		MOUSEMOVE_func = func;
		break;
	case MOUSEDOWN:
		MOUSEDOWN_func = func;
		break;
	case MOUSEUP:
		MOUSEUP_func = func;
		break;
	case KEYDOWN:
		KEYDOWN_func = func;
		break;
	case KEYUP:
		KEYUP_func = func;
		break;
	default:
		break;
	}
}

void ev_doEvents( void )
{
	SDL_Event curr_event;
	while ( SDL_PollEvent( &curr_event ) )
	{
		//construct event wrapper
		struct Event ev_wrapper;
		ev_wrapper.curr_event = curr_event;
		
		switch ( curr_event.type )
		{
		case SDL_QUIT:
			if ( QUIT_func != NULL )
			        QUIT_func( &ev_wrapper );
			break;
		case SDL_MOUSEMOTION:
			if ( MOUSEMOVE_func != NULL )
			        MOUSEMOVE_func( &ev_wrapper );
			break;
		case SDL_MOUSEBUTTONDOWN:
			if ( MOUSEDOWN_func != NULL )
			        MOUSEDOWN_func( &ev_wrapper );
			break;
		case SDL_MOUSEBUTTONUP:
			if ( MOUSEUP_func != NULL )
			        MOUSEUP_func( &ev_wrapper );
			break;
		case SDL_KEYDOWN:
			if ( KEYDOWN_func != NULL )
			        KEYDOWN_func( &ev_wrapper );
			break;
		case SDL_KEYUP:
			if ( KEYUP_func != NULL )
			        KEYUP_func( &ev_wrapper );
			break;
		default:
			break;
		}
	}
}

enum Keys ev_getKeycode( struct Event* ev )
{
	if ( ev->curr_event.type == SDL_KEYDOWN ||
	     ev->curr_event.type == SDL_KEYUP )
	{
		SDL_KeyboardEvent kev = ev->curr_event.key;
		switch ( kev.keysym.sym )
		{
		case SDLK_LEFT:
			return KEY_LEFT;
			break;
		case SDLK_RIGHT:
			return KEY_RIGHT;
			break;
		case SDLK_UP:
			return KEY_UP;
			break;
		case SDLK_DOWN:
			return KEY_DOWN;
			break;
		case SDLK_RETURN:
			return KEY_ENTER;
			break;
                case SDLK_TAB:
			return KEY_TAB;
			break;
		default:
			return KEY_NONE;
			break;
		}
	}
	return KEY_NONE;
}
