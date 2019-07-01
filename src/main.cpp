#include "game.hpp"
#include "game_state.hpp"
#include "main.hpp"
#include "render.hpp"
#include "text.hpp"

void main_update( int ticks );
void main_render();

static int ticks = 0;
static bool still_running = true;

int main()
{
	if ( game_init() != 0 || render_init() != 0 )
	{
		return -1;
	}

	text_init();
	game_state_init();
	while ( still_running )
	{
		game_handle_events();
		int these_ticks = game_get_ticks() - ticks;
		while ( these_ticks < ( int )( 1000 / 60 ) )
		{
			these_ticks = game_get_ticks() - ticks;
		};
		game_state_update( ticks );
		main_render();
		ticks = game_get_ticks();
	}
	render_close();
	return 0;
}

void main_quit()
{
	still_running = false;
}

void main_update( int ticks )
{
}

void main_render()
{
	render_clear_screen();
	game_state_render();
	render_present_screen();
}
