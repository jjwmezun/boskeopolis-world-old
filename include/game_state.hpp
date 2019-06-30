#pragma once

#include "overworld_state_data.hpp"
#include "title_state_data.hpp"

enum GameStateType
{
	GSTATE_NULL,
	GSTATE_TITLE,
	GSTATE_OVERWORLD,
	GSTATE_MESSAGE
};

union GameStateData
{
	TitleStateData title;
	OverworldStateData overworld;
};

struct GameState
{
	GameStateType type;
	void ( *update )( int, GameStateData* );
	void ( *render )( GameStateData* );
	void ( *init )( GameStateData* );
	GameStateData data;
};

void game_state_init();
void game_state_update( int ticks );
void game_state_render();
void game_state_change( GameState state );
