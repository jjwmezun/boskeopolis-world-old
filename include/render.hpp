#include <cstdint>
#include <SDL2/SDL.h>

typedef int_fast8_t BL2Texture;
typedef SDL_Rect BL2Rect;

int render_init();
void render_close();
void render_clear_screen();
void render_present_screen();
void render_sprite( BL2Texture texture, const BL2Rect* src, const BL2Rect* dest );
BL2Texture render_load_texture( const char* name );
