#include "config.hpp"
#include "render.hpp"
#include "sprite_graphics.hpp"
#include "text.hpp"

#define NUMBER_OF_CHARS 255

static BL2Texture texture = -1;
static BL2Rect charmap[ NUMBER_OF_CHARS ] = { { 0, 0, 0, 71 } };

void set_char( char letter, int x, int w );

void text_init()
{
	texture = render_load_texture( "charset.png" );
	set_char( ' ', 0, 25 );
	set_char( 'A', 25, 48 );
	set_char( 'B', 73, 46 );
	set_char( 'C', 121, 44 );
	set_char( 'D', 164, 41 );
	set_char( 'E', 204, 40 );
	set_char( 'F', 248, 36 );
	set_char( 'G', 286, 52 );
	set_char( 'H', 340, 48 );
	set_char( 'I', 395, 43 );
	set_char( 'J', 444, 59 );
	set_char( 'K', 504, 44 );
	set_char( 'L', 554, 43 );
	set_char( 'M', 602, 58 );
	set_char( 'N', 662, 46 );
	set_char( 'O', 708, 51 );
	set_char( 'P', 760, 42 );
	set_char( 'S', 905, 50 );

	set_char( 'a', 1329, 36 );
	set_char( 'b', 1365, 36 );
	set_char( 'c', 1401, 35 );
	set_char( 'd', 1436, 40 );
	set_char( 'e', 1477, 42 );

	set_char( 'f', 1518, 42 );
	set_char( 'g', 1560, 40 );
	set_char( 'h', 1603, 47 );
	set_char( 'i', 1656, 19 );
	set_char( 'j', 1674, 35 );
	set_char( 'k', 1712, 37 );
	set_char( 'l', 1751, 30 );
	set_char( 'm', 1785, 46 );
	set_char( 'n', 1832, 44 );
	set_char( 'o', 1876, 40 );
	set_char( 'p', 1917, 41 );
	set_char( 'q', 1962, 58 );
	set_char( 'r', 2019, 36 );
	set_char( 's', 2054, 37 );
	set_char( 't', 2089, 45 );

	set_char( '\'', 2374, 14 );
	set_char( '.', 2393, 14 );
};

SpriteGraphics text_create_texture( const char* text, int x, int y, int w )
{
	int char_x = 0;
	int char_y = 0;
	render_create_new_texture( w, CONFIG_HEIGHT );
	while ( *text )
	{
		if ( *text == '\n' )
		{
			char_y += 36;
			char_x = 0;
		}

		const BL2Rect* src = &charmap[ ( int )( *text ) ];
		const int char_width = src->w / 2;
		const BL2Rect dest = { char_x, char_y, char_width, 36 };
		render_sprite( texture, src, &dest );
		++text;
		char_x += char_width;
		if ( char_x >= w )
		{
			char_y += 36;
			char_x = 0;
		}
	}
	return
	{
		render_finish_new_texture_creation(),
		{ 0, 0, w, CONFIG_HEIGHT },
		{ x, y, w, CONFIG_HEIGHT }
	};
};

SpriteGraphics text_create_texture_center_x( const char* text, int y )
{
	render_create_new_texture( CONFIG_WIDTH, 36 );
	int x = 0;
	while ( *text )
	{
		const BL2Rect* src = &charmap[ ( int )( *text ) ];
		const int char_width = src->w / 2;
		const BL2Rect dest = { x, 0, char_width, 36 };
		render_sprite( texture, src, &dest );
		++text;
		x += char_width;
	}
	const int dest_x = ( CONFIG_WIDTH / 2 ) - ( x / 2 );
	return
	{
		render_finish_new_texture_creation(),
		{ 0, 0, CONFIG_WIDTH, 36 },
		{ dest_x, y, CONFIG_WIDTH, 36 }
	};
};

void set_char( char letter, int x, int w )
{
	charmap[ letter ] = { x, 0, w, 71 };
}
