#ifndef INIT_STATE_H
#define INIT_STATE_H

#include <SDL.h>
#include "../game/game.h"
#include "state.h"

State* init_state_create(Game* game, SDL_Renderer* renderer);

#endif
