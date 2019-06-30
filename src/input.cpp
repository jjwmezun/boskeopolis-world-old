#include "input.hpp"
#include "main.hpp"

#define INPUT_LIMIT 6

bool keys_held[ INPUT_LIMIT ] = { false };

bool input_held( Input input )
{
	return keys_held[ input ];
}

void input_hold( Input input )
{
	keys_held[ input ] = true;
};

void input_release( Input input )
{
	keys_held[ input ] = false;
};

void input_hold_quit()
{
	main_quit();
}
