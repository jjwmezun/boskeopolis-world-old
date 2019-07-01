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
	set_char( 'P', 760, 42 );
	set_char( 'S', 905, 50 );
	set_char( 'a', 1329, 36 );
	set_char( 'e', 1477, 42 );
	set_char( 'r', 1973, 36 );
	set_char( 's', 2008, 37 );
	set_char( 't', 2045, 45 );
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
