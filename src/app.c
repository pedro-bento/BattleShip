#include "app.h"

#include <SDL.h>

#include "game/game.h"
#include "game/ship.h"
#include "renderer/renderer.h"
#include "math/vec2.h"

Vec2 move_vec2(Vec2 vec, Vec2 dxy);
void move_ship(Game* game, Ship* ship, Vec2 dxy);

void app_player_init(Game* game, SDL_Renderer* renderer);
int app_player_init_handle_events(Game* game, SDL_Keycode key, Ship* ship);

void app_playing_game_state(Game* game, SDL_Renderer* renderer);
Vec2 app_playing_game_state_handle_events(Game* game, SDL_Keycode key, Vec2 shot);

void app_run()
{
  Game game;
  game_init(&game);

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  app_player_init(&game, renderer);
  game_swap_current_player(&game);
  app_player_init(&game, renderer);

  app_playing_game_state(&game, renderer);

  game_print(&game);

  if(game.state == PLAYER1_WIN) printf("\nPLAYER 1 WON!\n");
  else printf("\nPLAYER 2 WON!\n");

  game_free(&game);

  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  // SDL_Quit(); // malloc_consolidation error?????
}

void app_player_init(Game* game, SDL_Renderer* renderer)
{
  const int ship_length[5] = {5, 4, 3, 3, 2};
  int count = 0, shouldQuit = 0;
  Ship* ship = game_create_random_ship(game, ship_length[count]);

  SDL_Event e;
  while(count < NUM_OF_SHIPS && !shouldQuit)
  {
    // Events
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_KEYDOWN){
        if(app_player_init_handle_events(game, e.key.keysym.sym, ship)){
          if(game_player_add_ship(game, ship, count)){
            count++;
            ship = game_create_random_ship(game, ship_length[count % 5]);
          }
        }else if(e.type == SDL_QUIT){
          shouldQuit = 1;
        }
      }
    }

    // render and draw
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    render_current_player(renderer, game);
    render_ship(renderer, ship);
    SDL_RenderPresent(renderer);
  }
}

// returns 1 if ship is placed
int app_player_init_handle_events(Game* game, SDL_Keycode key, Ship* ship)
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
      Vec2 prev_front = ship->front;
      Vec2 prev_back = ship->back;
      ship_rotate_counterclockwise(ship);
      if(game_is_valid_ship(game, ship))
        break;
      ship->front = prev_front;
      ship->back = prev_back;
    } break;

    case SDLK_e: {
      Vec2 prev_front = ship->front;
      Vec2 prev_back = ship->back;
      ship_rotate_clockwise(ship);
      if(game_is_valid_ship(game, ship))
        break;
      ship->front = prev_front;
      ship->back = prev_back;
    } break;

    case SDLK_RETURN: return 1;
  }
  return 0;
}

void app_playing_game_state(Game* game, SDL_Renderer* renderer)
{
  int shouldQuit = 0;
  Vec2 shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);

  SDL_Event e;
  while(game->state == PLAYING && !shouldQuit)
  {
    // Events
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_KEYDOWN)
        shot = app_playing_game_state_handle_events(game, e.key.keysym.sym, shot);
      else if(e.type == SDL_QUIT)
        shouldQuit = 1;
    }

    // render and draw
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    render_opponent(renderer, game);
    render_shot(renderer, shot);
    SDL_RenderPresent(renderer);
  }
}

Vec2 app_playing_game_state_handle_events(Game* game, SDL_Keycode key, Vec2 shot)
{
  switch(key)
  {
    case SDLK_w: case SDLK_UP: {
      shot = move_vec2(shot, vec2(-1,0));
    } break;

    case SDLK_a: case SDLK_LEFT: {
      shot = move_vec2(shot, vec2(0,-1));
    } break;

    case SDLK_s: case SDLK_DOWN: {
      shot = move_vec2(shot, vec2(1,0));
    } break;

    case SDLK_d: case SDLK_RIGHT: {
      shot = move_vec2(shot, vec2(0,1));
    } break;

    case SDLK_RETURN: {
      game_player_shoot_gui(game, shot);
      shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);
      game_swap_current_player(game);
    } break;
  }
  return shot;
}

Vec2 move_vec2(Vec2 vec, Vec2 dxy)
{
  Vec2 prev = vec;
  vec = add(vec, dxy);

  if(vec.x < 0 || vec.x >= MAP_LENGTH || vec.y < 0 || vec.y >= MAP_LENGTH)
     return prev;
  return vec;
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
