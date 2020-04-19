#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "../physics/player.h"

void render_shot(Vec2i pos, SDL_Renderer* renderer, Settings* settings);
void render_ship_preview(Ship* ship, SDL_Renderer* renderer, Settings* settings);
void render_player(Player* player, SDL_Renderer* renderer, Settings* settings);
void render_opponent(Player* player, SDL_Renderer* renderer, Settings* settings);
void render_grid(SDL_Renderer* renderer, Settings* settings);

#endif // RENDERER_H
