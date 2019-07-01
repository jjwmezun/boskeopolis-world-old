#pragma once

#include "render.hpp"

struct SpriteGraphics
{
	BL2Texture texture;
	BL2Rect src;
	BL2Rect dest;
};

void sprite_graphics_render( const SpriteGraphics* graphics );
