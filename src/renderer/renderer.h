#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "../game/game.h"
#include "../math/vec2.h"
#include "../game/ship.h"

#define SCREEN_WIDTH 600
#define FOOTER_HEIGHT (SCREEN_WIDTH/10)
#define CELL_WIDTH (SCREEN_WIDTH / MAP_LENGTH)

// renders current player board (grid and ships)
void render_current_player(SDL_Renderer* renderer, Game* game);
// render current position ship
// CAN BE OPTIMIZED
void render_ship(SDL_Renderer* renderer, Ship* ship);
// renders opponents board (grid and hits)
void render_opponent(SDL_Renderer* renderer, Game* game);
// render current position of shot
void render_shot(SDL_Renderer* renderer, Vec2 shot);

#endif
