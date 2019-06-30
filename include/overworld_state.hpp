#pragma once

#include "config.hpp"
#include "game_state.hpp"
#include "sprite.hpp"

GameState overworld_state_create();
void overworld_state_update( int ticks, GameStateData* data );
void overworld_state_render( GameStateData* data );
void overworld_state_init( GameStateData* data );
