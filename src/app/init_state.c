#include "init_state.h"
#include "../math/vec2.h"
#include "../game/ship.h"
#include "../renderer/renderer.h"
#include "../ui/ui.h"
#include "../system/stacktrace.h"

// init current player
void player_init_game_state(Game* game, GamePlayer player, SDL_Renderer* renderer, int* shouldQuit);
// handles inputs & returns 1 if ship is placed
int  player_init_handle_events(Game* game, SDL_Keycode key, ShipLine* ship);

typedef void (*Rotate_func)(ShipLine* ship);
void move_ship(Game* game, ShipLine* ship, Vec2 dxy);
void rotate_ship(Game* game, ShipLine* ship, Rotate_func func);

typedef struct
{
  Game* game;
  TextBox text;
  GamePlayer current_player;
  int ship_length[5];
  ShipLine* ship;
  int count;
} InitData;

void init_render(State* s, SDL_Renderer* renderer);
void init_handle_event(State* s, SDL_Event* e);
int init_update(State* s, SDL_Renderer* renderer);

State* init_state_create(Game* game, SDL_Renderer* renderer)
{
  State* init = malloc(sizeof(State));
  trace_assert(init);
  InitData* data = malloc(sizeof(InitData));
  trace_assert(data);

  data->game = game;

  TTF_Font* ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
  SDL_Color text_color = {255, 255, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(ubuntu_mono, "Player 1!", text_color);
  SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);

  data->text = textbox(vec2(SCREEN_WIDTH * 0.875, SCREEN_HEIGHT * 0.085),
    150, 60, 10, (SDL_Color){.r = 0, .g = 0, .b = 0}, message);

  data->ship_length[0] = 5;
  data->ship_length[1] = 4;
  data->ship_length[2] = 3;
  data->ship_length[3] = 3;
  data->ship_length[4] = 2;

  data->current_player = PLAYER1;
  data->count = 0;
  data->ship = game_create_random_ship(game, data->current_player, data->ship_length[data->count]);

  init->data = (void*)data;
  init->render = &init_render;
  init->handle_event = &init_handle_event;
  init->update = &init_update;

  return init;
}

void init_state_destroy(State* state)
{
  free(state->data);
  free(state);
}

void init_render(State* s, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  render_game_player(renderer, ((InitData*)s->data)->game, ((InitData*)s->data)->current_player);
  render_ship(renderer, ((InitData*)s->data)->ship);
  textbox_render(&((InitData*)s->data)->text, renderer);
  SDL_RenderPresent(renderer);
}

void init_handle_event(State* s, SDL_Event* e)
{
  Game* game = ((InitData*)s->data)->game;
  ShipLine* ship = ((InitData*)s->data)->ship;
  GamePlayer player = ((InitData*)s->data)->current_player;

  if(e->type == SDL_KEYDOWN)
  {
    switch(e->key.keysym.sym)
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

      case SDLK_RETURN: {
        if(game_player_place_ship(game, player, ship))
        {
          ((InitData*)s->data)->count++;
          ((InitData*)s->data)->ship = game_create_random_ship(game, player,
            ((InitData*)s->data)->ship_length[((InitData*)s->data)->count % 5]);
        }
      } break;
    }
  }
}

int init_update(State* s, SDL_Renderer* renderer)
{
  if(((InitData*)s->data)->count >= NUM_OF_SHIPS)
  {
    if(((InitData*)s->data)->current_player == PLAYER1)
    {
      ((InitData*)s->data)->current_player = PLAYER2;
      ((InitData*)s->data)->count = 0;
      ((InitData*)s->data)->ship = game_create_random_ship(
        ((InitData*)s->data)->game, ((InitData*)s->data)->current_player,
        ((InitData*)s->data)->ship_length[((InitData*)s->data)->count % 5]);

      TTF_Font* ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
      SDL_Color text_color = {255, 255, 255};
      SDL_Surface* surface = TTF_RenderText_Solid(ubuntu_mono, "Player 2!", text_color);
      SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
      ((InitData*)s->data)->text.text = message;
    }
    else return 1;
  }
  return 0;
}

void move_ship(Game* game, ShipLine* ship, Vec2 dxy)
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

void rotate_ship(Game* game, ShipLine* ship, Rotate_func func)
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