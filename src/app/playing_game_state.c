#include "playing_game_state.h"
#include "../math/vec2.h"
#include "../renderer/renderer.h"

// handles inputs & returns new position of shot
Vec2 playing_handle_events(Game* game, SDL_Keycode key, Vec2 shot);

Vec2 move_shot(Vec2 vec, Vec2 dxy);

void playing_game_state(Game* game, SDL_Renderer* renderer, int* shouldQuit)
{
  Vec2 shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);

  SDL_Event e;
  while(game->state == PLAYING && !*shouldQuit)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_KEYDOWN)
        shot = playing_handle_events(game, e.key.keysym.sym, shot);
      else if(e.type == SDL_QUIT)
        *shouldQuit = 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    render_opponent(renderer, game);
    render_shot(renderer, shot);
    SDL_RenderPresent(renderer);
  }
}

Vec2 playing_handle_events(Game* game, SDL_Keycode key, Vec2 shot)
{
  switch(key)
  {
    case SDLK_w: case SDLK_UP: {
      shot = move_shot(shot, vec2(-1,0));
    } break;

    case SDLK_a: case SDLK_LEFT: {
      shot = move_shot(shot, vec2(0,-1));
    } break;

    case SDLK_s: case SDLK_DOWN: {
      shot = move_shot(shot, vec2(1,0));
    } break;

    case SDLK_d: case SDLK_RIGHT: {
      shot = move_shot(shot, vec2(0,1));
    } break;

    case SDLK_RETURN: {
      game_player_shoot_gui(game, shot);
      shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);
      game_swap_current_player(game);
    } break;
  }
  return shot;
}

Vec2 move_shot(Vec2 vec, Vec2 dxy)
{
  Vec2 prev = vec;
  vec = add(vec, dxy);

  if(vec.x < 0 || vec.x >= MAP_LENGTH || vec.y < 0 || vec.y >= MAP_LENGTH)
     return prev;
  return vec;
}
