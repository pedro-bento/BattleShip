#include "fight.h"
#include "../system/log.h"
#include "../graphics/renderer.h"
#include "results.h"

typedef struct
{
  SDL_Renderer* renderer;
  Settings* settings;
  Game* game;
  Vec2i shot[2];
  PlayerID current_player;
  bool isContinue;
} Data;

void f_render(State* state, SDL_Renderer* renderer);
void f_handle_event(State* state, SDL_Event* event);
State* f_update(State* state);

State* new_fight_state(Game* game, Settings* settings, SDL_Renderer* renderer)
{
  State* state = malloc(sizeof(State));
  LOG_FAIL(state);

  Data* data = malloc(sizeof(Data));
  LOG_FAIL(data);

  data->renderer        = renderer;
  data->settings        = settings;
  data->game            = game;
  data->current_player  = PLAYER1;
  data->isContinue      = false;
  data->shot[0] = data->shot[1] = vec2i(settings->MAP_SIZE/2,settings->MAP_SIZE/2);

  state->data         = data;
  state->render       = f_render;
  state->handle_event = f_handle_event;
  state->update       = f_update;

  return state;
}

void delete_fight_state(State* state)
{
  free(state->data);
  free(state);
}

void f_render(State* state, SDL_Renderer* renderer)
{
  Game* game              = ((Data*)state->data)->game;
  Settings* settings      = game->settings;
  PlayerID current_player = ((Data*)state->data)->current_player;
  Vec2i shot              = ((Data*)state->data)->shot[current_player - 1];

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_grid(renderer, settings);
  render_opponent(game_get_player_by_id(game, current_player), renderer, settings);
  render_shot(shot, renderer, settings);

  SDL_RenderPresent(renderer);
}

bool inBound(Vec2i pos, Settings* settings)
{
  if(pos.x < 0 || pos.y < 0 || pos.x >= settings->MAP_SIZE || pos.y >= settings->MAP_SIZE)
    return false;
  return true;
}

void f_handle_event(State* state, SDL_Event* event)
{
  Game* game                = ((Data*)state->data)->game;
  Settings* settings        = game->settings;
  PlayerID* current_player  = &((Data*)state->data)->current_player;
  Vec2i* shot               = &((Data*)state->data)->shot[*current_player - 1];
  bool* isContinue          = &((Data*)state->data)->isContinue;

  switch(event->type)
  {
    case SDL_KEYDOWN :{
      switch(event->key.keysym.sym)
      {
        case SDLK_w: case SDLK_UP: {
          *shot = vec2i(shot->x - 1, shot->y);
          if(!inBound(*shot, settings))
            *shot = vec2i(shot->x + 1,shot->y);
        } break;

        case SDLK_a: case SDLK_LEFT: {
          *shot = vec2i(shot->x, shot->y - 1);
          if(!inBound(*shot, settings))
            *shot = vec2i(shot->x, shot->y + 1);
        } break;

        case SDLK_s: case SDLK_DOWN: {
          *shot = vec2i(shot->x + 1,shot->y);
          if(!inBound(*shot, settings))
            *shot = vec2i(shot->x - 1,shot->y);
        } break;

        case SDLK_d: case SDLK_RIGHT: {
          *shot = vec2i(shot->x, shot->y + 1);
          if(!inBound(*shot, settings))
            *shot = vec2i(shot->x, shot->y - 1);
        } break;

        case SDLK_RETURN :{
          game_player_shoot(game, *shot, *current_player);
          *current_player = flip_player_id(*current_player);
          if(game_is_over(game)) *isContinue = true;
        } break;
      }
    } break;
  }
}

State* f_update(State* state)
{
  bool* isContinue = &((Data*)state->data)->isContinue;
  if(*isContinue == true)
  {
    SDL_Renderer* renderer = ((Data*)state->data)->renderer;
    Settings* settings     = ((Data*)state->data)->settings;
    Game* game             = ((Data*)state->data)->game;
    State* new_state       = new_results_state(game, settings, renderer);
    delete_fight_state(state);
    return new_state;
  }
  return state;
}
