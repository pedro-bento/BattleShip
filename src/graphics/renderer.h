#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include "../physics/player.h"
#include "../physics/game.h"

// render_shot
// renders a square at position 'pos'
void render_shot(Vec2i pos, SDL_Renderer* renderer, Settings* settings);

// render_ship_preview
// renders a ship with transparency
void render_ship_preview(Ship* ship, SDL_Renderer* renderer, Settings* settings);

// render_player
// renders a players map (ship_state)
void render_player(Player* player, SDL_Renderer* renderer, Settings* settings);

// render_opponent
// renders a player shot_state (opponent)
void render_opponent(Player* player, SDL_Renderer* renderer, Settings* settings);

// render_grid
// renders map grid lines
void render_grid(SDL_Renderer* renderer, Settings* settings);

// render_final
// renders both players to show results
void render_final(Game* game, SDL_Renderer* renderer, Settings* settings);

#endif // RENDERER_H
