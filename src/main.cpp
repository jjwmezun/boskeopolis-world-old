#include "game.hpp"
#include "main.hpp"
#include "render.hpp"

void main_update( int ticks );
void main_render();

struct Sprite
{
	double x;
	double y;
	double walk_acc;
	double maxv;
	double accx;
	double accy;
	double vx;
	double vy;
};

static int ticks = 0;
static bool still_running = true;
static Sprite autumn = { 200.0, 200.0, 0.5, 4.0, 0.0, 0.0, 0.0, 0.0 };
static BL2Texture autumn_texture;
static BL2Rect autumn_src = { 0, 0, 64, 94 };
static BL2Rect autumn_dest = { 200, 200, autumn_src.w, autumn_src.h };

int main()
{
	if ( game_init() != 0 || render_init() != 0 )
	{
		return -1;
	}

	autumn_texture = render_load_texture( "autumn.png" );
	while ( still_running )
	{
		game_handle_events();
		int these_ticks = game_get_ticks() - ticks;
		while ( these_ticks < ( int )( 1000 / 60 ) )
		{
			these_ticks = game_get_ticks() - ticks;
		};
		main_update( these_ticks );
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
	autumn.accx = autumn.walk_acc;
	autumn.vx += autumn.accx;
	if ( autumn.vx > autumn.maxv )
	{
		autumn.vx = autumn.maxv;
	}
	else if ( autumn.vx < -autumn.maxv )
	{
		autumn.vx = -autumn.maxv;
	}
	autumn.x += autumn.vx;
	autumn_dest.x = ( int )( autumn.x );
}

void main_render()
{
	render_clear_screen();
	render_sprite( autumn_texture, &autumn_src, &autumn_dest );
	render_present_screen();
}
