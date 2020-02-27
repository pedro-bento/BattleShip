#include "init_game_state.h"
#include "../math/vec2.h"
#include "../game/ship.h"
#include "../renderer/renderer.h"
#include "../ui/ui.h"

// init current player
void player_init_game_state(Game* game, GamePlayer player, SDL_Renderer* renderer, int* shouldQuit);
// handles inputs & returns 1 if ship is placed
int  player_init_handle_events(Game* game, SDL_Keycode key, Ship* ship);

typedef void (*Rotate_func)(Ship* ship);
void move_ship(Game* game, Ship* ship, Vec2 dxy);
void rotate_ship(Game* game, Ship* ship, Rotate_func func);

void init_game_state(Game* game, SDL_Renderer* renderer, int* shouldQuit)
{
  player_init_game_state(game, PLAYER1, renderer, shouldQuit);
  player_init_game_state(game, PLAYER2, renderer, shouldQuit);
}

void player_init_game_state(Game* game, GamePlayer player, SDL_Renderer* renderer, int* shouldQuit)
{
  const int ship_length[5] = {5, 4, 3, 3, 2};
  int count = 0;
  Ship* ship = game_create_random_ship(game, player, ship_length[count]);

  TTF_Font* ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
  SDL_Color text_color = {255, 255, 255};

  char* str;
  if(player == PLAYER1){
    str = "Place your ships, Player 1!\0";
  }else{
    str = "Place your ships, Player 2!\0";
  }

  SDL_Surface* surface_player1 = TTF_RenderText_Solid(ubuntu_mono, str, text_color);
  SDL_Texture* player1_message = SDL_CreateTextureFromSurface(renderer, surface_player1);

  TextBox player_init = {.text = player1_message,
    .pos_rect = { .x = SCREEN_WIDTH/2-200, .y = SCREEN_HEIGHT+FOOTER_HEIGHT-60, .w = 400, .h = 60},
    .text_rect = { .x = SCREEN_WIDTH/2-190, .y = SCREEN_HEIGHT+FOOTER_HEIGHT-50, .w = 380, .h = 40},
    .backgroud_color = {0, 0, 0}};

  SDL_Event e;
  while(count < NUM_OF_SHIPS && !*shouldQuit)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_KEYDOWN)
      {
        if(player_init_handle_events(game, e.key.keysym.sym, ship))
        {
          if(game_player_place_ship(game, player, ship))
          {
            count++;
            ship = game_create_random_ship(game, player, ship_length[count % 5]);
          }
        }
      }

      else if(e.type == SDL_QUIT)
      {
        *shouldQuit = 1;
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    render_game_player(renderer, game, player);
    render_ship(renderer, ship);
    textbox_render(&player_init, renderer);
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
