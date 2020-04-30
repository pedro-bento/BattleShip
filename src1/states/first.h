#ifndef FIRST_H
#define FIRST_H

#include <SDL.h>

#include "state.h"
#include "../config.h"

State* new_first_state(Settings* settings, SDL_Renderer* renderer);

#endif
