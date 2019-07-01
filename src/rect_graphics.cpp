#include "rect_graphics.hpp"

void rect_graphics_render( const RectGraphics* graphics )
{
	render_rect( &graphics->position, &graphics->color );
}
