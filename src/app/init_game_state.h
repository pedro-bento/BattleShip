#ifndef INIT_GAME_STATE_H
#define INIT_GAME_STATE_H

#include <SDL.h>
#include "../game/game.h"

void init_game_state(Game* game, SDL_Renderer* renderer, int* shouldQuit);

#endif
