#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <SDL.h>

#include "../game/game.h"
#include "../math/vec2.h"
#include "../game/ship.h"
#include "../config.h"
#include "../quadtree.h"

// renders current player board (grid and ships)
void render_game_player(SDL_Renderer* renderer, Game* game, GamePlayer player);
// render current position ship
void render_ship(SDL_Renderer* renderer, ShipLine* ship);
// renders opponents board (grid and hits)
void render_opponent(SDL_Renderer* renderer, Game* game, GamePlayer player);
// render current position of shot
void render_shot(SDL_Renderer* renderer, Vec2 shot);
// render both players
// Just a prototype!
void render_all(SDL_Renderer* renderer, Game* game);

void render_quadtree(SDL_Renderer* renderer, QT* qt);

#endif
