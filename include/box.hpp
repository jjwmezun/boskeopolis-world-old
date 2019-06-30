#pragma once

struct Box
{
	double x;
	double y;
	double w;
	double h;
};

constexpr double box_bottom( const Box* box )
{
	return box->y + box->h;
}

constexpr double box_right( const Box* box )
{
	return box->x + box->w;
}
