#include "collision.hpp"
#include "config.hpp"
#include "input.hpp"
#include "level_state.hpp"
#include "message_state.hpp"
#include "overworld_state.hpp"
#include "sprite.hpp"

#define AUTUMN_WIDTH 64
#define ANIMATION_LIMIT 2

void overworld_state_update( int ticks, GameStateData* data );
void overworld_state_render( GameStateData* data );
void overworld_state_init( GameStateData* data );

void overworld_state_update( int ticks, GameStateData* data )
{
	sprite_update_by_input( &data->overworld.autumn );
	sprite_update_acceleration( &data->overworld.autumn );
	if ( data->overworld.autumn.position.x < 96.0 )
	{
		data->overworld.autumn.position.x = 96.0;
	}
	if ( box_right( &data->overworld.autumn.position ) > ( CONFIG_WIDTH - 96.0 ) )
	{
		data->overworld.autumn.position.x = ( CONFIG_WIDTH - 96.0 - data->overworld.autumn.position.w );
	}
	if ( data->overworld.autumn.position.y < 96.0 )
	{
		data->overworld.autumn.position.y = 96.0;
	}
	if ( box_bottom( &data->overworld.autumn.position ) > ( CONFIG_HEIGHT - 96.0 ) )
	{
		data->overworld.autumn.position.y = ( CONFIG_HEIGHT - 96.0 - data->overworld.autumn.position.h );
	}
	data->overworld.autumn_dest.x = data->overworld.autumn.position.x;
	data->overworld.autumn_dest.y = data->overworld.autumn.position.y - ( 94 - 32 );

	if ( input_held( INPUT_CONFIRM ) )
	{
		if ( collision_box_test( &data->overworld.autumn.position, &data->overworld.locked_door ) )
		{
			game_state_push( message_state_create( "It's locked.\nLuckily, I have the key in my pocket, since it's not like I'd be able to find it anywhere else." ) );
		}
	}

	if ( data->overworld.animation_timer >= 7 )
	{
		data->overworld.autumn_src.x += AUTUMN_WIDTH;
		data->overworld.bg_src.x += CONFIG_WIDTH;
		if ( data->overworld.autumn_src.x >= AUTUMN_WIDTH * ANIMATION_LIMIT )
		{
			data->overworld.autumn_src.x = 0;
			data->overworld.bg_src.x = 0;
		}
		data->overworld.animation_timer = 0;
	}
	else
	{
		++data->overworld.animation_timer;
	}
}

void overworld_state_render( GameStateData* data )
{
	render_sprite( data->overworld.home_texture, &data->overworld.bg_src, &data->overworld.bg_dest );
	render_sprite( data->overworld.autumn_texture, &data->overworld.autumn_src, &data->overworld.autumn_dest );
	render_color_screen({ 200, 160, 128, 255 });
}

void overworld_state_init( GameStateData* data )
{
	data->overworld.autumn_texture = render_load_texture( "autumn2.png" );
	data->overworld.home_texture = render_load_texture( "home2.png" );
	data->overworld.autumn_src = { 0, 0, AUTUMN_WIDTH, 94 };
	data->overworld.autumn = { { 200, 200, data->overworld.autumn_src.w, 32 }, 0.5, 4.0, 0.0, 0.0, 0.0, 0.0 };
	data->overworld.bg_src = { 0, 0, CONFIG_WIDTH, CONFIG_HEIGHT };
	data->overworld.bg_dest = { 0, 0, CONFIG_WIDTH, CONFIG_HEIGHT };
	data->overworld.autumn_dest = { data->overworld.autumn.position.x, data->overworld.autumn.position.y - ( 94 - 32 ), data->overworld.autumn_src.w, data->overworld.autumn_src.h };
	data->overworld.animation_timer = 0;
	data->overworld.locked_door = { 864.0, 88.0, 15.0, 12.0 };
}

GameState overworld_state_create()
{
	return
	{
		GSTATE_OVERWORLD,
		&overworld_state_update,
		&overworld_state_render,
		&overworld_state_init,
		{}
	};
};
