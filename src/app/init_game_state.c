#include "init_game_state.h"
#include "../math/vec2.h"
#include "../game/ship.h"
#include "../renderer/renderer.h"

// init current player
void player_init(Game* game, SDL_Renderer* renderer, int* shouldQuit);
// handles inputs & returns 1 if ship is placed
int  player_init_handle_events(Game* game, SDL_Keycode key, Ship* ship);

typedef void (*Rotate_func)(Ship* ship);
void move_ship(Game* game, Ship* ship, Vec2 dxy);
void rotate_ship(Game* game, Ship* ship, Rotate_func func);

void init_game_state(Game* game, SDL_Renderer* renderer, int* shouldQuit)
{
  game->current_player = PLAYER1;
  player_init(game, renderer, shouldQuit);

  game->current_player = PLAYER2;
  player_init(game, renderer, shouldQuit);

  game->current_player = PLAYER1;
}

void player_init(Game* game, SDL_Renderer* renderer, int* shouldQuit)
{
  const int ship_length[5] = {5, 4, 3, 3, 2};
  int count = 0;
  Ship* ship = game_create_random_ship(game, ship_length[count]);

  SDL_Event e;
  while(count < NUM_OF_SHIPS && !*shouldQuit){
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_KEYDOWN){
        if(player_init_handle_events(game, e.key.keysym.sym, ship)){
          if(game_player_add_ship(game, ship, count)){
            count++;
            ship = game_create_random_ship(game, ship_length[count % 5]);
          }
        }
      }else if(e.type == SDL_QUIT){
        *shouldQuit = 1;
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    render_current_player(renderer, game);
    render_ship(renderer, ship);
    SDL_RenderPresent(renderer);
  }
}

int  player_init_handle_events(Game* game, SDL_Keycode key, Ship* ship)
{
  switch(key)
  {
    case SDLK_w: case SDLK_UP: {
      move_ship(game, ship, vec2(-1,0));
    } break;

    case SDLK_a: case SDLK_LEFT: {
      move_ship(game, ship, vec2(0,-1));
    } break;

    case SDLK_s: case SDLK_DOWN: {
      move_ship(game, ship, vec2(1,0));
    } break;

    case SDLK_d: case SDLK_RIGHT: {
      move_ship(game, ship, vec2(0,1));
    } break;

    case SDLK_q: {
      rotate_ship(game, ship, &ship_rotate_counterclockwise);
    } break;

    case SDLK_e: {
      rotate_ship(game, ship, &ship_rotate_clockwise);
    } break;

    case SDLK_RETURN: return 1;
  }
  return 0;
}

void move_ship(Game* game, Ship* ship, Vec2 dxy)
{
  Vec2 prev_front = ship->front;
  Vec2 prev_back = ship->back;

  ship->front = add(ship->front, dxy);
  ship->back = add(ship->back, dxy);

  Vec2 p1 = ship->front;
  Vec2 p2 = ship->back;
  if(p1.x < 0 || p1.x >= MAP_LENGTH || p1.y < 0 || p1.y >= MAP_LENGTH ||
     p2.x < 0 || p2.x >= MAP_LENGTH || p2.y < 0 || p2.y >= MAP_LENGTH)
  {
    ship->front = prev_front;
    ship->back = prev_back;
  }
}

void rotate_ship(Game* game, Ship* ship, Rotate_func func)
{
  Vec2 prev_front = ship->front;
  Vec2 prev_back = ship->back;
  func(ship);
  Vec2 p1 = ship->front;
  Vec2 p2 = ship->back;
  if(p1.x < 0 || p1.x >= MAP_LENGTH || p1.y < 0 || p1.y >= MAP_LENGTH ||
     p2.x < 0 || p2.x >= MAP_LENGTH || p2.y < 0 || p2.y >= MAP_LENGTH)
  {
    ship->front = prev_front;
    ship->back = prev_back;
  }
}
