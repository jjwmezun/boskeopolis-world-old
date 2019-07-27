#pragma once

#include "box.hpp"

struct Sprite
{
	Box position;
	double walk_acc;
	double maxv;
	double accx;
	double accy;
	double vx;
	double vy;
};

void sprite_update_acceleration( Sprite* sprite );
void sprite_update_x_acceleration( Sprite* sprite );
void sprite_update_by_input( Sprite* sprite );
