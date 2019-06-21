#include "config.hpp"
#include "game.hpp"
#include "input.hpp"
#include "main.hpp"
#include "render.hpp"

void main_update( int ticks );
void main_render();

struct Box
{
	double x;
	double y;
	double w;
	double h;
};

struct Sprite
{
	Box position;
	double walk_acc;
	double maxv;
	double accx;
	double accy;
	double vx;
	double vy;
};

static int ticks = 0;
static bool still_running = true;
static BL2Rect autumn_src = { 0, 0, 64, 94 };
static Sprite autumn = { { 200, 200, autumn_src.w, 32 }, 0.5, 4.0, 0.0, 0.0, 0.0, 0.0 };
static BL2Texture autumn_texture;
static BL2Texture home_texture;
static BL2Rect bg_box = { 0, 0, CONFIG_WIDTH, CONFIG_HEIGHT };
static BL2Rect autumn_dest = { autumn.position.x, autumn.position.y - ( 94 - 32 ), autumn_src.w, autumn_src.h };

double box_bottom( const Box* box )
{
	return box->y + box->h;
}

double box_right( const Box* box )
{
	return box->x + box->w;
}

int main()
{
	if ( game_init() != 0 || render_init() != 0 )
	{
		return -1;
	}

	autumn_texture = render_load_texture( "autumn.png" );
	home_texture = render_load_texture( "home.png" );
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
	if ( input_held( INPUT_RIGHT ) )
	{
		autumn.accx = autumn.walk_acc;
	}
	else if ( input_held( INPUT_LEFT ) )
	{
		autumn.accx = -autumn.walk_acc;
	}
	else
	{
		autumn.accx = 0.0;
		autumn.vx /= 1.15;
	}

	if ( input_held( INPUT_UP ) )
	{
		autumn.accy = -autumn.walk_acc;
	}
	else if ( input_held( INPUT_DOWN ) )
	{
		autumn.accy = autumn.walk_acc;
	}
	else
	{
		autumn.accy = 0.0;
		autumn.vy /= 1.15;
	}

	autumn.vx += autumn.accx;
	if ( autumn.vx > autumn.maxv )
	{
		autumn.vx = autumn.maxv;
	}
	else if ( autumn.vx < -autumn.maxv )
	{
		autumn.vx = -autumn.maxv;
	}
	autumn.position.x += autumn.vx;
	if ( autumn.position.x < 96.0 )
	{
		autumn.position.x = 96.0;
	}
	if ( box_right( &autumn.position ) > ( CONFIG_WIDTH - 96.0 ) )
	{
		autumn.position.x = ( CONFIG_WIDTH - 96.0 - autumn.position.w );
	}
	autumn_dest.x = autumn.position.x;

	autumn.vy += autumn.accy;
	if ( autumn.vy > autumn.maxv )
	{
		autumn.vy = autumn.maxv;
	}
	else if ( autumn.vy < -autumn.maxv )
	{
		autumn.vy = -autumn.maxv;
	}

	autumn.position.y += autumn.vy;
	if ( autumn.position.y < 96.0 )
	{
		autumn.position.y = 96.0;
	}
	if ( box_bottom( &autumn.position ) > ( CONFIG_HEIGHT - 96.0 ) )
	{
		autumn.position.y = ( CONFIG_HEIGHT - 96.0 - autumn.position.h );
	}
	autumn_dest.y = autumn.position.y - ( 94 - 32 );
}

void main_render()
{
	render_clear_screen();
	render_sprite( home_texture, &bg_box, &bg_box );
	render_sprite( autumn_texture, &autumn_src, &autumn_dest );
	render_color_screen({ 200, 160, 128, 255 });
	render_present_screen();
}
