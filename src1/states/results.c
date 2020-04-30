#include "results.h"
#include "../graphics/ui.h"
#include "../system/log.h"
#include "../graphics/renderer.h"

typedef struct
{
  SDL_Renderer* renderer;
  Settings* settings;
  Game* game;
  Text p1;
  Text p2;
  Button quit;
  bool isContinue;
} Data;

void r_render(State* state, SDL_Renderer* renderer);
void r_handle_event(State* state, SDL_Event* event);
State* r_update(State* state);

State* new_results_state(Game* game, Settings* settings, SDL_Renderer* renderer)
{
  State* state = malloc(sizeof(State));
  LOG_FAIL(state);

  Data* data = malloc(sizeof(Data));
  LOG_FAIL(data);

  data->renderer = renderer;
  data->settings = settings;
  data->game = game;
  data->isContinue = false;

  data->p1 = text(
    vec2i(settings->WINDOW_WIDTH * 0.25, settings->WINDOW_HEIGHT * 0.1),
    settings->WINDOW_WIDTH * 0.4, settings->WINDOW_HEIGHT * 0.05,
    "Player One", settings->font_big, COLOR_RADIOACTIVE_GREEN, renderer);

  data->p2 = text(
    vec2i(settings->WINDOW_WIDTH * 0.75, settings->WINDOW_HEIGHT * 0.1),
    settings->WINDOW_WIDTH * 0.4, settings->WINDOW_HEIGHT * 0.05,
    "Player Two", settings->font_big, COLOR_RADIOACTIVE_GREEN, renderer);

  data->quit = button(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.88),
    settings->WINDOW_WIDTH * 0.3, settings->WINDOW_HEIGHT * 0.08, 5,
    "Quit", settings->font_big, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN, renderer);

  state->data = data;
  state->render = r_render;
  state->handle_event = r_handle_event;
  state->update = r_update;

  return state;
}

void delete_results_state(State* state)
{
  delete_text(&((Data*)state->data)->p1);
  delete_text(&((Data*)state->data)->p2);
  delete_button(&((Data*)state->data)->quit);
  SDL_DestroyRenderer(((Data*)state->data)->renderer);
  delete_game(((Data*)state->data)->game);
  free(state->data);
  free(state);
}

void r_render(State* state, SDL_Renderer* renderer)
{
  Settings* settings = ((Data*)state->data)->settings;
  Game* game = ((Data*)state->data)->game;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_text(&((Data*)state->data)->p1, renderer);
  render_text(&((Data*)state->data)->p2, renderer);
  render_button(&((Data*)state->data)->quit, renderer);

  render_final(game, renderer, settings);

  SDL_RenderPresent(renderer);
}

void r_handle_event(State* state, SDL_Event* event)
{
  if(event->type == SDL_MOUSEBUTTONDOWN)
  {
    Vec2i mouse_pos = vec2i(event->button.x, event->button.y);
    if(button_isClick(&((Data*)state->data)->quit, mouse_pos))
      ((Data*)state->data)->isContinue = true;
  }
}

State* r_update(State* state)
{
  if(((Data*)state->data)->isContinue == true){
    delete_results_state(state);
    return NULL;
  }
  return state;
}
