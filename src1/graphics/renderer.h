#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "../physics/player.h"

void render_player(Player* player, SDL_Renderer* renderer);

#endif // RENDERER_H
