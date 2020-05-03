#ifndef PLACING_SHIPS_H
#define PLACING_SHIPS_H

#include <SDL.h>

#include "state.h"
#include "../config.h"
#include "../physics/game.h"

// returns a heap allocated state
State* new_placing_ships_state(Settings* settings, Game* game, SDL_Renderer* renderer);

#endif
