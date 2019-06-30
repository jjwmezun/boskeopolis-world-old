#pragma once

#include "box.hpp"

constexpr bool collision_box_test( const Box* lhs, const Box* rhs )
{
	return
	(
		lhs->x < box_right( rhs ) &&
		box_right( lhs ) > rhs->x &&
		lhs->y < box_bottom( rhs ) &&
		box_bottom( lhs ) > rhs->y
	);
}
