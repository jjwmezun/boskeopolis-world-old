#include "config.hpp"
#include "render.hpp"
#include <SDL2/SDL_image.h>

#define MAX_TEXTURES 127

static SDL_Texture* textures[ MAX_TEXTURES ];
static BL2Texture number_of_textures = 0;
static SDL_Renderer* renderer = nullptr;
static SDL_Window* window = nullptr;
static char* base_path;
static uint_fast16_t max_filename_length = 0;
static SDL_Texture* screen_texture;
static SDL_Rect screen_box = { 0, 0, CONFIG_WIDTH, CONFIG_HEIGHT };
static SDL_Texture* render_to_texture = nullptr;

int render_init()
{
	window = SDL_CreateWindow( "Boskeopolis Land II", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CONFIG_WIDTH, CONFIG_HEIGHT, SDL_WINDOW_OPENGL );
	if ( window == nullptr )
	{
		SDL_Log( "Could not create window: %s\n", SDL_GetError() );
		return -1;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_TARGETTEXTURE );
	if ( renderer == nullptr )
	{
		SDL_Log( "Could not create renderer: %s\n", SDL_GetError() );
		return -1;
	}

	if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
	{
		SDL_Log( "IMG_Initialization failed: %s", SDL_GetError() );
		return -1;
	}
	base_path = SDL_GetBasePath();
	char* temp_base_path = base_path;
	while ( *temp_base_path )
	{
		++max_filename_length;
		++temp_base_path;
	}
	max_filename_length += 255;
	screen_texture = SDL_GetRenderTarget( renderer );
	return 0;
}

void render_close()
{
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( renderer );
	SDL_free( base_path );
}

void render_clear_screen()
{
	//SDL_SetRenderTarget( renderer, screen_texture );
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );
}

void render_present_screen()
{
	//SDL_SetRenderTarget( renderer, screen_texture );
	SDL_RenderPresent( renderer );
}

void render_sprite( BL2Texture texture, const BL2Rect* src, const BL2Rect* dest )
{
	SDL_RenderCopy( renderer, textures[ texture ], src, dest );
};

void render_rect( const BL2Rect* rect, const BL2Color* color )
{
	SDL_SetRenderDrawColor( renderer, color->r, color->g, color->b, color->a );
	SDL_RenderFillRect( renderer, rect );
};

void render_color_screen( BL2Color color )
{
	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_MOD );
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
	SDL_RenderFillRect( renderer, &screen_box );
	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_NONE );
};

BL2Texture render_load_texture( const char* name )
{
	char* full_filename = ( char* )( calloc( max_filename_length, sizeof( char ) ) );
	strcat( full_filename, base_path );
	strcat( full_filename, name );
	SDL_RWops* rwop = SDL_RWFromFile( full_filename, "rb" );
	if ( rwop == nullptr )
	{
		SDL_Log( "SDL_RWFromFile failed: %s", SDL_GetError() );
		return -1;
	}
	SDL_Surface* surface = IMG_LoadPNG_RW( rwop );
	SDL_RWclose( rwop );
	if ( surface == nullptr )
	{
		SDL_Log( "SDL_Surface failed: %s", SDL_GetError() );
		return -1;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
	if ( texture == nullptr )
	{
		SDL_Log( "SDL_CreateTextureFromSurface failed: %s", SDL_GetError() );
		return -1;
	}
	textures[ number_of_textures ] = texture;
	BL2Texture texture_id = number_of_textures;
	++number_of_textures;
	return texture_id;
};

void render_create_new_texture( int width, int height )
{
	SDL_Texture* texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, height );
	if ( texture == nullptr )
	{
		printf( "Failed to allocate clear texture: %s\n", SDL_GetError() );
	}
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	SDL_SetRenderTarget( renderer, texture );
	render_to_texture = texture;
};

BL2Texture render_finish_new_texture_creation()
{
	textures[ number_of_textures ] = render_to_texture;
	BL2Texture texture_id = number_of_textures;
	++number_of_textures;
	SDL_SetRenderTarget( renderer, screen_texture );
	render_to_texture = nullptr;
	return texture_id;
};
