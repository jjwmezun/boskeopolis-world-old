#include "sprite_graphics.hpp"

void sprite_graphics_render( const SpriteGraphics* graphics )
{
	render_sprite( graphics->texture, &graphics->src, &graphics->dest );
};
