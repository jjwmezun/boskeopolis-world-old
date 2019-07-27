#pragma once

#include "box.hpp"
#include "render.hpp"
#include "sprite.hpp"

enum DirX
{
	DIRX_NULL,
	DIRX_LEFT,
	DIRX_RIGHT
};

struct LevelHero
{
	Sprite sprite;
	BL2Texture texture;
	BL2Rect gfx_src;
	BL2Rect gfx_dest;
	SDL_RendererFlip gfx_flip;
	int walk_animation;
	int walk_timer;
	bool is_jumping;
};

struct LevelStateData
{
	LevelHero autumn;
};
