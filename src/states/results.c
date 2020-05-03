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

  data->renderer    = renderer;
  data->settings    = settings;
  data->game        = game;
  data->isContinue  = false;

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

  state->data         = data;
  state->render       = r_render;
  state->handle_event = r_handle_event;
  state->update       = r_update;

  return state;
}

void delete_results_state(State* state)
{
  Text* text_player1      = &((Data*)state->data)->p1;
  Text* text_player2      = &((Data*)state->data)->p2;
  Button* button_quit     = &((Data*)state->data)->quit;
  SDL_Renderer* renderer  = ((Data*)state->data)->renderer;
  Game* game              = ((Data*)state->data)->game;

  delete_text(text_player1);
  delete_text(text_player2);
  delete_button(button_quit);
  SDL_DestroyRenderer(renderer);
  delete_game(game);
  free(state->data);
  free(state);
}

void r_render(State* state, SDL_Renderer* renderer)
{
  Text* text_player1  = &((Data*)state->data)->p1;
  Text* text_player2  = &((Data*)state->data)->p2;
  Button* button_quit = &((Data*)state->data)->quit;
  Settings* settings  = ((Data*)state->data)->settings;
  Game* game          = ((Data*)state->data)->game;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_text(text_player1, renderer);
  render_text(text_player2, renderer);
  render_button(button_quit, renderer);
  render_final(game, renderer, settings);

  SDL_RenderPresent(renderer);
}

void r_handle_event(State* state, SDL_Event* event)
{
  Button* button_quit = &((Data*)state->data)->quit;
  bool* isContinue    = &((Data*)state->data)->isContinue;

  if(event->type == SDL_MOUSEBUTTONDOWN)
  {
    Vec2i mouse_pos = vec2i(event->button.x, event->button.y);
    if(button_isClick(button_quit, mouse_pos))
      *isContinue = true;
  }
}

State* r_update(State* state)
{
  bool isContinue    = ((Data*)state->data)->isContinue;

  if(isContinue == true){
    delete_results_state(state);
    return NULL;
  }
  return state;
}
