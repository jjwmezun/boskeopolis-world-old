#include "input.hpp"
#include "render.hpp"
#include "overworld_state.hpp"
#include "text.hpp"
#include "title_state.hpp"

#define LOGO_WIDTH 1100
#define LOGO_HEIGHT 113

GameState title_state_create()
{
	return
	{
		GSTATE_TITLE,
		&title_state_update,
		&title_state_render,
		&title_state_init,
		{}
	};
};

void title_state_update( int ticks, GameStateData* data )
{
	if ( input_held( INPUT_CONFIRM ) )
	{
		game_state_change( overworld_state_create() );
	}
};

void title_state_render( GameStateData* data )
{
	sprite_graphics_render( &data->title.logo );
	sprite_graphics_render( &data->title.press_start );
};

void title_state_init( GameStateData* data )
{
	data->title =
	{
		{
			render_load_texture( "logo.png" ),
			{ 0, 0, LOGO_WIDTH, LOGO_HEIGHT },
			{ 50, 50, LOGO_WIDTH, LOGO_HEIGHT }
		},
		text_create_texture_center_x( "Press Start", 200 )
	};
};
