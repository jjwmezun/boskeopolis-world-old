#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

typedef int_fast8_t BL2Texture;
typedef SDL_Rect BL2Rect;
typedef SDL_Color BL2Color;

constexpr int rect_right( const BL2Rect* rect )
{
	return rect->x + rect->w;
}

constexpr int rect_bottom( const BL2Rect* rect )
{
	return rect->y + rect->h;
}

int render_init();
void render_close();
void render_clear_screen();
void render_present_screen();
void render_sprite( BL2Texture texture, const BL2Rect* src, const BL2Rect* dest );
void render_rect( const BL2Rect* rect, const BL2Color* color );
BL2Texture render_load_texture( const char* name );
void render_color_screen( BL2Color color );
void render_create_new_texture( int width, int height );
BL2Texture render_finish_new_texture_creation();
