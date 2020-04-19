#ifndef CONFIGURE_GAME_H
#define CONFIGURE_GAME_H

#include <SDL.h>
#include <stdbool.h>

#include "state.h"
#include "../config.h"

State* new_configure_game_state(Settings* settings, SDL_Renderer* renderer);

#endif
