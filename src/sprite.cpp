#include "input.hpp"
#include "sprite.hpp"

void sprite_update_acceleration( Sprite* sprite )
{
	sprite->vx += sprite->accx;
	if ( sprite->vx > sprite->maxv )
	{
		sprite->vx = sprite->maxv;
	}
	else if ( sprite->vx < -sprite->maxv )
	{
		sprite->vx = -sprite->maxv;
	}
	sprite->position.x += sprite->vx;

	sprite->vy += sprite->accy;
	if ( sprite->vy > sprite->maxv )
	{
		sprite->vy = sprite->maxv;
	}
	else if ( sprite->vy < -sprite->maxv )
	{
		sprite->vy = -sprite->maxv;
	}

	sprite->position.y += sprite->vy;
}

void sprite_update_by_input( Sprite* sprite )
{
	if ( input_held( INPUT_RIGHT ) )
	{
		sprite->accx = sprite->walk_acc;
	}
	else if ( input_held( INPUT_LEFT ) )
	{
		sprite->accx = -sprite->walk_acc;
	}
	else
	{
		sprite->accx = 0.0;
		sprite->vx /= 1.15;
	}

	if ( input_held( INPUT_UP ) )
	{
		sprite->accy = -sprite->walk_acc;
	}
	else if ( input_held( INPUT_DOWN ) )
	{
		sprite->accy = sprite->walk_acc;
	}
	else
	{
		sprite->accy = 0.0;
		sprite->vy /= 1.15;
	}
}
