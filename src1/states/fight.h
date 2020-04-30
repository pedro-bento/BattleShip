#ifndef FIGHT_H
#define FIGHT_H

#include <SDL.h>
#include <stdbool.h>

#include "state.h"
#include "../config.h"
#include "../physics/game.h"

State* new_fight_state(Game* game, Settings* settings, SDL_Renderer* renderer);

#endif
