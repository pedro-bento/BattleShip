#include "placing_ships.h"
#include "../system/log.h"
#include "../math/vec.h"
#include "../math/math.h"
#include "../physics/ship.h"
#include "../physics/player.h"
#include "../physics/game.h"
#include "../graphics/renderer.h"
#include "../graphics/ui.h"
#include "fight.h"

typedef struct
{
  SDL_Renderer* renderer;
  Settings* settings;
  Game* game;
  Ship* ship;
  int current_player_id;
  int current_ship_count;
  Button random;
  bool random_pressed;
  bool no_ship_preview;
} Data;

void ps_render(State* state, SDL_Renderer* renderer);
void ps_handle_event(State* state, SDL_Event* event);
State* ps_update(State* state);

State* new_placing_ships_state(Settings* settings, Game* game, SDL_Renderer* renderer)
{
  State* state = malloc(sizeof(State));
  LOG_FAIL(state);

  Data* data = malloc(sizeof(Data));
  LOG_FAIL(data);
  data->renderer            = renderer;
  data->settings            = settings;
  data->game                = game;
  data->ship                = new_ship(settings->ships[0]);
  data->current_player_id   = 1;
  data->current_ship_count  = 0;
  data->random_pressed      = false;
  data->no_ship_preview     = false;

  data->random = button(
    vec2i(settings->WINDOW_WIDTH * 0.95, settings->WINDOW_HEIGHT * 0.05),
    settings->WINDOW_WIDTH * 0.078, settings->WINDOW_HEIGHT * 0.05, 2,
    "Random", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN, renderer);

  state->data         = data;
  state->render       = ps_render;
  state->handle_event = ps_handle_event;
  state->update       = ps_update;

  return state;
}

void delete_placing_ships_state(State* state)
{
  Button* button_random = &((Data*)state->data)->random;

  delete_button(button_random);
  free(state->data);
  free(state);
}

void ps_render(State* state, SDL_Renderer* renderer)
{
  Settings* settings    = ((Data*)state->data)->settings;
  Game* game            = ((Data*)state->data)->game;
  Ship* ship            = ((Data*)state->data)->ship;
  int current_player_id = ((Data*)state->data)->current_player_id;
  bool* no_ship_preview = &((Data*)state->data)->no_ship_preview;
  Button* button_random = &((Data*)state->data)->random;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_grid(renderer, settings);
  render_player(game_get_player_by_id(game, current_player_id), renderer, settings);
  if(!*no_ship_preview) render_ship_preview(ship, renderer, settings);
  else *no_ship_preview = false;
  render_button(button_random, renderer);

  SDL_RenderPresent(renderer);
}

void ps_handle_event(State* state, SDL_Event* event)
{
  Settings* settings      = ((Data*)state->data)->settings;
  Ship* ship              = ((Data*)state->data)->ship;
  Game* game              = ((Data*)state->data)->game;
  int* current_ship_count = &((Data*)state->data)->current_ship_count;
  int* current_player_id  = &((Data*)state->data)->current_player_id;
  Button* button_random   = &((Data*)state->data)->random;
  bool* random_pressed    = &((Data*)state->data)->random_pressed;
  bool* no_ship_preview   = &((Data*)state->data)->no_ship_preview;
  SDL_Renderer* renderer  = ((Data*)state->data)->renderer;

  switch(event->type)
  {
    case SDL_MOUSEBUTTONDOWN :{
      Vec2i mouse_pos = vec2i(event->button.x, event->button.y);
      if(!(*random_pressed) && button_isClick(button_random, mouse_pos))
      {
        *random_pressed = true;

        Vec2i dxy;
        while(*current_ship_count < settings->NUM_OF_SHIPS)
        {
          do{
            dxy = vec2i(rand_range(0, settings->MAP_SIZE-1) - ship->top_left.x, rand_range(0, settings->MAP_SIZE-1) - ship->top_left.y);

            ship_move(ship, dxy);

            size_t num_rots = rand_range(0, 4);

            for(size_t i = 0; i < num_rots; ++i)
              ship_rotate(ship, true);

          }while(!game_is_valid_ship(game, ship, *current_player_id, false));

          game_player_place_ship(game, ship, *current_player_id);

          *current_ship_count += 1;
          ship = ((Data*)state->data)->ship = new_ship(settings->ships[*current_ship_count]);
        }

        *no_ship_preview = true;
        ps_render(state, renderer);
        SDL_Delay(1500);
        *current_player_id += 1;
        *current_ship_count = 0;

        delete_ship(ship);

        if(*current_player_id > 2)
        {
          return;
        }

        ((Data*)state->data)->ship = new_ship(settings->ships[*current_ship_count]);
        *random_pressed = false;
        
        return;
      }
    } break;

    case SDL_KEYDOWN :{
      switch(event->key.keysym.sym)
      {
        case SDLK_w: case SDLK_UP: {
          ship_move(ship, vec2i(-1,0));
          if(!game_is_valid_ship(game, ship, *current_player_id, true))
            ship_move(ship, vec2i(1,0));
        } break;

        case SDLK_a: case SDLK_LEFT: {
          ship_move(ship, vec2i(0,-1));
          if(!game_is_valid_ship(game, ship, *current_player_id, true))
            ship_move(ship, vec2i(0,1));
        } break;

        case SDLK_s: case SDLK_DOWN: {
          ship_move(ship, vec2i(1,0));
          if(!game_is_valid_ship(game, ship, *current_player_id, true))
            ship_move(ship, vec2i(-1,0));
        } break;

        case SDLK_d: case SDLK_RIGHT: {
          ship_move(ship, vec2i(0,1));
          if(!game_is_valid_ship(game, ship, *current_player_id, true))
            ship_move(ship, vec2i(0,-1));
        } break;

        case SDLK_q :{
          ship_rotate(ship, false);
          if(!game_is_valid_ship(game, ship, *current_player_id, true))
            ship_rotate(ship, true);
        } break;

        case SDLK_e :{
          ship_rotate(ship, true);
          if(!game_is_valid_ship(game, ship, *current_player_id, true))
            ship_rotate(ship, false);
        } break;

        case SDLK_RETURN :{
          if(game_player_place_ship(game, ship, *current_player_id))
          {
            if(*current_ship_count >= settings->NUM_OF_SHIPS - 1)
            {
              *current_player_id += 1;
              *current_ship_count = 0;
              ((Data*)state->data)->ship = new_ship(settings->ships[*current_ship_count]);
              return;
            }

            if(*current_player_id > 2)
            {
              return;
            }

            *current_ship_count += 1;
            ((Data*)state->data)->ship = new_ship(settings->ships[*current_ship_count]);
          }
        } break;
      }
    } break;
  }
}

State* ps_update(State* state)
{
  if(((Data*)state->data)->current_player_id > 2)
  {
    SDL_Renderer* renderer = ((Data*)state->data)->renderer;
    Settings* settings = ((Data*)state->data)->settings;
    Game* game = ((Data*)state->data)->game;
    State* new_state = new_fight_state(game, settings, renderer);
    delete_placing_ships_state(state);
    return new_state;
  }
  return state;
}
