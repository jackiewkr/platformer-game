#define EVENTS_NS

#include "events.h"

#include <SDL2/SDL.h>

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

//mapping from SDLK keycodes to own format; TODO switch to lookup table
enum Keycode ev_getKeycode( struct Event* ev )
{
        enum Keycode retcode = KEY_NONE;
	if ( ev->curr_event.type == SDL_KEYDOWN ||
	     ev->curr_event.type == SDL_KEYUP )
	{
		SDL_KeyboardEvent kev = ev->curr_event.key;
		switch ( kev.keysym.sym )
		{
		case SDLK_0:
                        retcode = KEY_0;
                        break;
                case SDLK_1:
                        retcode = KEY_1;
                        break;
                case SDLK_2:
                        retcode = KEY_2;
                        break;
                case SDLK_3:
                        retcode = KEY_3;
                        break;
                case SDLK_4:
                        retcode = KEY_4;
                        break;
                case SDLK_5:
                        retcode = KEY_5;
                        break;
                case SDLK_6:
                        retcode = KEY_6;
                        break;
                case SDLK_7:
                        retcode = KEY_7;
                        break;
                case SDLK_8:
                        retcode = KEY_8;
                        break;
                case SDLK_9:
                        retcode = KEY_9;
                        break;
                case SDLK_a:
                        retcode = KEY_A;
                        break;
                case SDLK_b:
                        retcode = KEY_B;
                        break;
                case SDLK_c:
                        retcode = KEY_C;
                        break;
                case SDLK_d:
                        retcode = KEY_D;
                        break;
                case SDLK_e:
                        retcode = KEY_E;
                        break;
                case SDLK_f:
                        retcode = KEY_F;
                        break;
                case SDLK_g:
                        retcode = KEY_G;
                        break;
                case SDLK_h:
                        retcode = KEY_H;
                        break;
                case SDLK_i:
                        retcode = KEY_I;
                        break;
                case SDLK_j:
                        retcode = KEY_J;
                        break;
                case SDLK_k:
                        retcode = KEY_K;
                        break;
                case SDLK_l:
                        retcode = KEY_L;
                        break;
                case SDLK_m:
                        retcode = KEY_M;
                        break;
                case SDLK_n:
                        retcode = KEY_N;
                        break;
                case SDLK_o:
                        retcode = KEY_O;
                        break;
                case SDLK_p:
                        retcode = KEY_P;
                        break;
                case SDLK_q:
                        retcode = KEY_Q;
                        break;
                case SDLK_r:
                        retcode = KEY_R;
                        break;
                case SDLK_s:
                        retcode = KEY_S;
                        break;
                case SDLK_t:
                        retcode = KEY_T;
                        break;
                case SDLK_u:
                        retcode = KEY_U;
                        break;
                case SDLK_v:
                        retcode = KEY_V;
                        break;
                case SDLK_w:
                        retcode = KEY_W;
                        break;
                case SDLK_x:
                        retcode = KEY_X;
                        break;
                case SDLK_y:
                        retcode = KEY_Y;
                        break;
                case SDLK_z:
                        retcode = KEY_Z;
                        break;
                case SDLK_LEFT:
                        retcode = KEY_LEFT;
                        break;
                case SDLK_UP:
                        retcode = KEY_UP;
                        break;
                case SDLK_RIGHT:
                        retcode = KEY_RIGHT;
                        break;
                case SDLK_DOWN:
                        retcode = KEY_DOWN;
                        break;
                case SDLK_ESCAPE:
                        retcode = KEY_ESC;
                        break;
                case SDLK_RETURN:
                        retcode = KEY_ENTER;
                        break;
                case SDLK_TAB:
                        retcode = KEY_TAB;
                        break;
                case SDLK_LSHIFT:
                case SDLK_RSHIFT:
                        retcode = KEY_SHIFT;
                        break;
                case SDLK_LALT:
                case SDLK_RALT:
                        retcode = KEY_ALT;
                        break;
                case SDLK_LCTRL:
                case SDLK_RCTRL:
                        retcode = KEY_CTRL;
                        break;
                default:
                        retcode = KEY_NONE;
                        break;
		}

                return retcode;
	}
	return KEY_NONE;
}
