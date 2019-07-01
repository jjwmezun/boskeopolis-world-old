#pragma once

#include "render.hpp"

struct RectGraphics
{
	BL2Rect position;
	BL2Color color;
};

void rect_graphics_render( const RectGraphics* graphics );
