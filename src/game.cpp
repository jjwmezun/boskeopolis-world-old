#include "game.hpp"
#include "main.hpp"
#include <SDL2/SDL.h>

int game_init()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
		return -1;
	}
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
		}
	}
}

int game_get_ticks()
{
	return SDL_GetTicks();
}
