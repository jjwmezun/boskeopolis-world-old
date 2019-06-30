#pragma once

enum Input
{
	INPUT_NULL,
	INPUT_UP,
	INPUT_RIGHT,
	INPUT_DOWN,
	INPUT_LEFT,
	INPUT_CONFIRM
};

void input_init();
bool input_held( Input input );
void input_hold( Input input );
void input_release( Input input );
void input_hold_quit();
