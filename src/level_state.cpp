#include "box.hpp"
#include "collision.hpp"
#include "config.hpp"
#include "input.hpp"
#include "level_state.hpp"
#include "sprite.hpp"

#include <cstdio>

void level_state_update( int ticks, GameStateData* data );
void level_state_render( GameStateData* data );
void level_state_init( GameStateData* data );
void level_update_hero_input( Sprite* sprite );
bool level_test_on_ground( const LevelHero* hero );
void level_update_hero( LevelHero* hero );

void level_state_update( int ticks, GameStateData* data )
{
	level_update_hero( &data->level.autumn );
}

void level_state_render( GameStateData* data )
{
	const BL2Color autumn_color = { 255, 64, 8, 255 };
	render_rect_fullscreen( { 64, 128, 255, 255 } );
	//render_rect( &data->level.autumn.gfx_dest, &autumn_color );
	render_sprite_advanced( data->level.autumn.texture, &data->level.autumn.gfx_src, &data->level.autumn.gfx_dest, data->level.autumn.gfx_flip );
}

void level_state_init( GameStateData* data )
{
	data->level.autumn =
	{
		{ { 800, 400, 78, 128 }, 0.5, 4.0, 0.0, 0.0, 0.0, 0.0 },
		render_load_texture( "autumn-level.png" ),
		{ 0, 0, 78, 128 },
		{},
		SDL_FLIP_NONE,
		0,
		0,
		false
	};
	data->level.autumn.gfx_dest = { data->level.autumn.sprite.position.x, data->level.autumn.sprite.position.y, data->level.autumn.sprite.position.w, data->level.autumn.sprite.position.h };
}

GameState level_state_create()
{
	return
	{
		GSTATE_LEVEL,
		&level_state_update,
		&level_state_render,
		&level_state_init,
		{}
	};
};

void level_update_hero_input( Sprite* sprite )
{
	if ( input_held( INPUT_RIGHT ) )
	{
		sprite->accx = sprite->walk_acc;
	}
	else if ( input_held( INPUT_LEFT ) )
	{
		sprite->accx = -sprite->walk_acc;
	}
	else
	{
		sprite->accx = 0.0;
		sprite->vx /= 1.15;
	}
}

bool level_test_on_ground( const LevelHero* hero )
{
	return !hero->is_jumping && box_bottom( &hero->sprite.position ) >= CONFIG_HEIGHT;
}

void level_update_hero( LevelHero* hero )
{
	level_update_hero_input( &hero->sprite );
	sprite_update_acceleration( &hero->sprite );

	printf( "%f\n", ( double )( hero->sprite.vy ) );
	if ( !hero->is_jumping && !level_test_on_ground( hero ) )
	{
		hero->sprite.accy = 2.0;
	}
	else
	{
		if ( hero->is_jumping )
		{
			hero->sprite.accy = -0.5;
			if ( hero->sprite.vy <= -hero->sprite.maxv )
			{
				hero->sprite.accy = 0.0;
				hero->sprite.vy = 0.0;
				hero->is_jumping = false;
			}
		}
		else if ( input_held( INPUT_CONFIRM ) && level_test_on_ground( hero ) )
		{
			hero->is_jumping = true;
		}
		else
		{
			hero->sprite.accy = 0.0;
			hero->sprite.vy = 0.0;
		}
	}

	hero->gfx_dest.x = hero->sprite.position.x;
	hero->gfx_dest.y = hero->sprite.position.y;

	if ( hero->sprite.accx != 0 )
	{
		if ( hero->walk_timer >= 8 )
		{
			++hero->walk_animation;
			if ( hero->walk_animation > 7 )
			{
				hero->walk_animation = 0;
			}
			hero->walk_timer = 0;
		}
		else
		{
			++hero->walk_timer;
		}
	}
	else
	{
		hero->walk_animation = 0;
	}

	hero->gfx_src.x = hero->walk_animation * 78;
	if ( input_held( INPUT_RIGHT ) )
	{
		hero->gfx_flip = SDL_FLIP_HORIZONTAL;
	}
	else if ( input_held( INPUT_LEFT ) )
	{
		hero->gfx_flip = SDL_FLIP_NONE;
	}
}
