#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "../physics/ship.h"

void render_ship(Ship* ship, SDL_Renderer* renderer);

#endif // RENDERER_H
