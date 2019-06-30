#pragma once

#include "game_state.hpp"

GameState title_state_create();
void title_state_update( int ticks, GameStateData* data );
void title_state_render( GameStateData* data );
void title_state_init( GameStateData* data );
