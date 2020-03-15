#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include <SDL.h>
#include "../game/game.h"
#include "state.h"

State* playing_state_create(Game* game, SDL_Renderer* renderer);

#endif
