#pragma once

void text_init();
SpriteGraphics text_create_texture( const char* text, int x, int y, int w );
SpriteGraphics text_create_texture_center_x( const char* text, int y );
