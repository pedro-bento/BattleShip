#ifndef RESULTS_H
#define RESULTS_H

#include <SDL.h>

#include "state.h"
#include "../config.h"
#include "../physics/game.h"

// returns a heap allocated state
State* new_results_state(Game* game, Settings* settings, SDL_Renderer* renderer);

#endif
