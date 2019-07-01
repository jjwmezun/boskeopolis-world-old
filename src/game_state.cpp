#include "game_state.hpp"
#include "title_state.hpp"

#define MAX_GAME_STATES 5

static GameState game_states[ MAX_GAME_STATES ] = {};
static int states_used = 0;

static void init_state( GameState* state );
static void update_state( GameState* state, int ticks );
static void render_state( GameState* state );

void game_state_init()
{
	game_states[ 0 ] = title_state_create();
	init_state( &game_states[ 0 ] );
	states_used = 1;
};

void game_state_update( int ticks )
{
	update_state( &game_states[ states_used - 1 ], ticks );
};

void game_state_render()
{
	for ( int i = 0; i < states_used; ++i )
	{
		render_state( &game_states[ i ] );
	}
};

void game_state_change( GameState state )
{
	game_states[ 0 ] = state;
	init_state( &game_states[ 0 ] );
	states_used = 1;
	game_states[ 1 ].type = GSTATE_NULL;
};

void game_state_push( GameState state )
{
	game_states[ states_used ] = state;
	init_state( &game_states[ states_used ] );
	++states_used;
};

static void init_state( GameState* state )
{
	state->init( &state->data );
};

static void update_state( GameState* state, int ticks )
{
	state->update( ticks, &state->data );
};

static void render_state( GameState* state )
{
	state->render( &state->data );
};
