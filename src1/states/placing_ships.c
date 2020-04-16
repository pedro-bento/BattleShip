#include "placing_ships.h"
#include "../system/log.h"
#include "../math/vec.h"
#include "../physics/ship.h"
#include "../physics/player.h"
#include "../physics/game.h"
#include "../graphics/renderer.h"
#include "../graphics/ui.h"

typedef struct
{
  Settings* settings;
  Game* game;
  Ship* ship;
  int current_player_id;
  int current_ship_count;
} Data;

void render(State* state, SDL_Renderer* renderer);
void handle_event(State* state, SDL_Event* event);
bool update(State* state);

State* new_placing_ships_state(Settings* settings, Game* game, SDL_Renderer* renderer)
{
  State* state = malloc(sizeof(State));
  LOG_FAIL(state);

  Data* data = malloc(sizeof(Data));
  LOG_FAIL(data);
  data->settings = settings;
  data->game = game;
  data->ship = new_ship(F);
  data->current_player_id = 1;
  data->current_ship_count = 1;

  state->data = data;
  state->render = render;
  state->handle_event = handle_event;
  state->update = update;

  return state;
}

void render(State* state, SDL_Renderer* renderer)
{
  Settings* settings = ((Data*)state->data)->settings;
  Game* game = ((Data*)state->data)->game;
  Ship* ship = ((Data*)state->data)->ship;
  int current_player_id = ((Data*)state->data)->current_player_id;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  render_grid(renderer, settings);
  render_player(game_get_player_by_id(game, current_player_id), renderer, settings);
  render_ship_preview(ship, renderer, settings);
  SDL_RenderPresent(renderer);
}

void handle_event(State* state, SDL_Event* event)
{
  Settings* settings = ((Data*)state->data)->settings;
  Ship* ship = ((Data*)state->data)->ship;
  Game* game = ((Data*)state->data)->game;
  int current_ship_count = ((Data*)state->data)->current_ship_count;
  int current_player_id = ((Data*)state->data)->current_player_id;

  switch(event->type)
  {
    case SDL_KEYDOWN :{
      switch(event->key.keysym.sym)
      {
        case SDLK_w: case SDLK_UP: {
          ship_move(ship, vec2i(-1,0));
          if(!game_is_valid_ship(game, ship, current_player_id, true))
            ship_move(ship, vec2i(1,0));
        } break;

        case SDLK_a: case SDLK_LEFT: {
          ship_move(ship, vec2i(0,-1));
          if(!game_is_valid_ship(game, ship, current_player_id, true))
            ship_move(ship, vec2i(0,1));
        } break;

        case SDLK_s: case SDLK_DOWN: {
          ship_move(ship, vec2i(1,0));
          if(!game_is_valid_ship(game, ship, current_player_id, true))
            ship_move(ship, vec2i(-1,0));
        } break;

        case SDLK_d: case SDLK_RIGHT: {
          ship_move(ship, vec2i(0,1));
          if(!game_is_valid_ship(game, ship, current_player_id, true))
            ship_move(ship, vec2i(0,-1));
        } break;

        case SDLK_q :{
          ship_rotate(ship, false);
          if(!game_is_valid_ship(game, ship, current_player_id, true))
            ship_rotate(ship, true);
        } break;

        case SDLK_e :{
          ship_rotate(ship, true);
          if(!game_is_valid_ship(game, ship, current_player_id, true))
            ship_rotate(ship, false);
        } break;

        case SDLK_RETURN :{
          if(game_player_place_ship(game, ship, current_player_id))
          {
            if(current_ship_count >= settings->NUM_OF_SHIPS)
            {
              ((Data*)state->data)->current_player_id++;
              ((Data*)state->data)->current_ship_count = 0;
            }

            if(((Data*)state->data)->current_player_id > 2)
            {
              return;
            }

            ((Data*)state->data)->ship = new_ship(F);
            ((Data*)state->data)->current_ship_count++;
          }
        } break;
      }
    } break;
  }
}

bool update(State* state)
{
  if(((Data*)state->data)->current_player_id > 2)
    return true;
  return false;
}
