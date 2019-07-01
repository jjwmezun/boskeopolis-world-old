#include "config.hpp"
#include "message_state.hpp"
#include "render.hpp"
#include "text.hpp"

#define BOX_HEIGHT_CHARACTERS 6
#define BOX_HEIGHT_CHAR_SIZE 36
#define BOX_HEIGHT BOX_HEIGHT_CHAR_SIZE * BOX_HEIGHT_CHARACTERS

void message_state_update( int ticks, GameStateData* data );
void message_state_render( GameStateData* data );
void message_state_init( GameStateData* data );

GameState message_state_create( const char* message )
{
	GameStateData data = {};
	data.message =
	{
		{ { 0, CONFIG_HEIGHT - BOX_HEIGHT, CONFIG_WIDTH, BOX_HEIGHT }, { 255, 255, 255, 255 } },
		text_create_texture( message, BOX_HEIGHT_CHAR_SIZE, CONFIG_HEIGHT - BOX_HEIGHT + BOX_HEIGHT_CHAR_SIZE, CONFIG_WIDTH - ( BOX_HEIGHT_CHAR_SIZE * 2 ) )
	};
	return
	{
		GSTATE_MESSAGE,
		&message_state_update,
		&message_state_render,
		&message_state_init,
		data
	};
};

void message_state_update( int ticks, GameStateData* data )
{
};

void message_state_render( GameStateData* data )
{
	rect_graphics_render( &data->message.bg );
	sprite_graphics_render( &data->message.text );
};

void message_state_init( GameStateData* data )
{
};
