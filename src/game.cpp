#include "game.hpp"
#include "input.hpp"
#include "main.hpp"
#include <SDL2/SDL.h>

Input keycodes[ 284 ] { INPUT_NULL };

int game_init()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
		return -1;
	}

	keycodes[ SDL_SCANCODE_UP ] = INPUT_UP;
	keycodes[ SDL_SCANCODE_RIGHT ] = INPUT_RIGHT;
	keycodes[ SDL_SCANCODE_DOWN ] = INPUT_DOWN;
	keycodes[ SDL_SCANCODE_LEFT ] = INPUT_LEFT;

	return 0;
}

void game_handle_events()
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) != 0 )
	{
		switch ( event.type )
		{
			case ( SDL_QUIT ):
			{
				main_quit();
			}
			break;
			case ( SDL_KEYDOWN ):
			{
				if ( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
				{
					input_hold_quit();
				}
				else
				{
					input_hold( keycodes[ event.key.keysym.scancode ] );
				}
			}
			break;
			case ( SDL_KEYUP ):
			{
				input_release( keycodes[ event.key.keysym.scancode ] );
			}
			break;
		}
	}
}

int game_get_ticks()
{
	return SDL_GetTicks();
}
