#include "configure_game.h"
#include "../graphics/ui.h"
#include "../physics/game.h"
#include "../system/log.h"
#include "placing_ships.h"

typedef struct
{
  SDL_Renderer* renderer;
  Settings* settings;
  Text title;
  Button play;
  NumericInputBox f_input;
  NumericInputBox i_input;
  NumericInputBox z_input;
  NumericInputBox h_input;
  bool isContinue;
} Data;

void cg_render(State* state, SDL_Renderer* renderer);
void cg_handle_event(State* state, SDL_Event* event);
State* cg_update(State* state);

State* new_configure_game_state(Settings* settings, SDL_Renderer* renderer)
{
  State* state = malloc(sizeof(State));
  LOG_FAIL(state);

  Data* data = malloc(sizeof(Data));
  LOG_FAIL(data);
  data->renderer = renderer;
  data->settings = settings;
  data->title = text(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.05), 200, 50,
    "BattleShip", settings->font, COLOR_RADIOACTIVE_GREEN, renderer);
  data->play = button(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.95),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.075, 10,
    "Let's play!", settings->font, COLOR_BLACK,
    COLOR_RADIOACTIVE_GREEN, renderer);
  data->f_input = numeric_input_box(vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.2), settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.05, "Fisherman Folk", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN, renderer, 1, -1);
  data->i_input = numeric_input_box(vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.35), settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.05, "Sailor's Irony", settings->font, COLOR_BLACK,
  COLOR_RADIOACTIVE_GREEN, renderer, 1, -1);
  data->z_input = numeric_input_box(vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.5), settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.05, "River Zebrafish", settings->font, COLOR_BLACK,
  COLOR_RADIOACTIVE_GREEN, renderer, 1, -1);
  data->h_input = numeric_input_box(vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.65), settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.05, "Hercules Catamaran", settings->font, COLOR_BLACK,
  COLOR_RADIOACTIVE_GREEN, renderer, 1, -1);
  data->isContinue = false;

  state->data = data;
  state->render = cg_render;
  state->handle_event = cg_handle_event;
  state->update = cg_update;

  return state;
}

void delete_configure_game_state(State* state)
{
  free(state->data);
  free(state);
}

void cg_render(State* state, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_text(&((Data*)state->data)->title, renderer);
  render_button(&((Data*)state->data)->play, renderer);
  render_numeric_input_box(&((Data*)state->data)->f_input, renderer);
  render_numeric_input_box(&((Data*)state->data)->i_input, renderer);
  render_numeric_input_box(&((Data*)state->data)->z_input, renderer);
  render_numeric_input_box(&((Data*)state->data)->h_input, renderer);

  SDL_RenderPresent(renderer);
}

void cg_handle_event(State* state, SDL_Event* event)
{
  if(event->type == SDL_MOUSEBUTTONDOWN)
  {
    if(button_isClick(&((Data*)state->data)->play, vec2i(event->button.x, event->button.y)))
    {
      ((Data*)state->data)->isContinue = true;
    }
  }
}

State* cg_update(State* state)
{
  if(((Data*)state->data)->isContinue == true)
  {
    SDL_Renderer* renderer = ((Data*)state->data)->renderer;
    Settings* settings = ((Data*)state->data)->settings;
    Game* game = new_game(settings);
    State* new_state = new_placing_ships_state(settings, game, renderer);
    delete_configure_game_state(state);
    return new_state;
  }
  return state;
}
