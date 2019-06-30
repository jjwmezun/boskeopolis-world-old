#pragma once

#include "box.hpp"
#include "render.hpp"
#include "sprite.hpp"

struct OverworldStateData
{
	BL2Rect autumn_src;
	Sprite autumn;
	BL2Texture autumn_texture;
	BL2Texture home_texture;
	BL2Rect bg_src;
	BL2Rect bg_dest;
	BL2Rect autumn_dest;
	int animation_timer;
	Box locked_door;
};
