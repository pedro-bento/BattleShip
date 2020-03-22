#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "math/vec.h"
#include "physics/ship.h"
#include "physics/player.h"
#include "physics/game.h"
#include "graphics/renderer.h"

void engine_run(SDL_Renderer* renderer)
{
  Game game = (Game)
  {
    .map_size = 40,
    .num_of_ships = 3,
    .player1 = (Player){ .ships_count = 0 },
    .player2 = (Player){ .ships_count = 0 },
  };

  int current_player_id = 1;

  Ship* ship = game_player_get_next_ship(&game, current_player_id);

  bool quit = false;
  SDL_Event event;
  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT :{
          quit = true;
        } break;

        case SDL_KEYDOWN :{
          switch(event.key.keysym.sym)
          {
            case SDLK_w: case SDLK_UP: {
              ship_move(ship, vec2i(-1,0));
            } break;

            case SDLK_a: case SDLK_LEFT: {
              ship_move(ship, vec2i(0,-1));
            } break;

            case SDLK_s: case SDLK_DOWN: {
              ship_move(ship, vec2i(1,0));
            } break;

            case SDLK_d: case SDLK_RIGHT: {
              ship_move(ship, vec2i(0,1));
            } break;

            case SDLK_q :{
              ship_rotate(ship, false);
            } break;

            case SDLK_e :{
              ship_rotate(ship, true);
            } break;

            case SDLK_RETURN :{
              if(game_get_player_by_id(&game, current_player_id)->ships_count >= game.num_of_ships)
                current_player_id++;
              if(current_player_id > 2) return;
              ship = game_player_get_next_ship(&game, current_player_id);
            } break;
          }
        } break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    render_player(game_get_player_by_id(&game, current_player_id), renderer);
    SDL_RenderPresent(renderer);
  }
}

#endif
