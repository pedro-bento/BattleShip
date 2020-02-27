#ifndef BEGIN_GAME_STATE_H
#define BEGIN_GAME_STATE_H

#include <SDL.h>
#include "state.h"

State* begin_state_create(SDL_Renderer* renderer);
void begin_state_destroy(State* state);

#endif
