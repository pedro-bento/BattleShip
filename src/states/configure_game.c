#include "configure_game.h"
#include "../graphics/ui.h"
#include "../physics/game.h"
#include "../system/log.h"
#include "placing_ships.h"
#include <limits.h>

typedef struct
{
  SDL_Renderer* renderer;
  Settings* settings;
  Text title;
  Button play;
  NumericInputBox map_size;
  NumericInputBox f_input;
  NumericInputBox i_input;
  NumericInputBox z_input;
  NumericInputBox h_input;
  NumericInputBox p_input;
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

  data->renderer    = renderer;
  data->settings    = settings;
  data->isContinue  = false;

  data->title = text(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.065),
    settings->WINDOW_WIDTH * 0.4, settings->WINDOW_HEIGHT * 0.05,
    "Choose your settings!", settings->font_big, COLOR_RADIOACTIVE_GREEN, renderer);

  data->play = button(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.92),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.08, 5,
    "Let's play!", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN, renderer);

  data->map_size = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.18),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Map Size", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, MIN_MAP_SIZE, MIN_MAP_SIZE, MAX_MAP_SIZE);

  data->f_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.3),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Freddie Barr", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->i_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.42),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Iqra Mcneil", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->z_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.54),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Zarah Atkins", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->h_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.66),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Harri Eaton", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->p_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.78),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Priya Lynch", settings->font, COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);


  state->data = data;
  state->render = cg_render;
  state->handle_event = cg_handle_event;
  state->update = cg_update;

  return state;
}

void delete_configure_game_state(State* state)
{
  Text* title               = &((Data*)state->data)->title;
  Button* play              = &((Data*)state->data)->play;
  NumericInputBox* map_size = &((Data*)state->data)->map_size;
  NumericInputBox* f_input  = &((Data*)state->data)->f_input;
  NumericInputBox* i_input  = &((Data*)state->data)->i_input;
  NumericInputBox* z_input  = &((Data*)state->data)->z_input;
  NumericInputBox* h_input  = &((Data*)state->data)->h_input;
  NumericInputBox* p_input  = &((Data*)state->data)->p_input;

  delete_text(title);
  delete_button(play);
  delete_numeric_input_box(map_size);
  delete_numeric_input_box(f_input);
  delete_numeric_input_box(i_input);
  delete_numeric_input_box(z_input);
  delete_numeric_input_box(h_input);
  delete_numeric_input_box(p_input);
  free(state->data);
  free(state);
}

void cg_render(State* state, SDL_Renderer* renderer)
{
  Text* title               = &((Data*)state->data)->title;
  Button* play              = &((Data*)state->data)->play;
  NumericInputBox* map_size = &((Data*)state->data)->map_size;
  NumericInputBox* f_input  = &((Data*)state->data)->f_input;
  NumericInputBox* i_input  = &((Data*)state->data)->i_input;
  NumericInputBox* z_input  = &((Data*)state->data)->z_input;
  NumericInputBox* h_input  = &((Data*)state->data)->h_input;
  NumericInputBox* p_input  = &((Data*)state->data)->p_input;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_text(title, renderer);
  render_button(play, renderer);
  render_numeric_input_box(map_size, renderer);
  render_numeric_input_box(f_input, renderer);
  render_numeric_input_box(i_input, renderer);
  render_numeric_input_box(z_input, renderer);
  render_numeric_input_box(h_input, renderer);
  render_numeric_input_box(p_input, renderer);

  SDL_RenderPresent(renderer);
}

void cg_handle_event(State* state, SDL_Event* event)
{
  Button* play              = &((Data*)state->data)->play;
  NumericInputBox* map_size = &((Data*)state->data)->map_size;
  NumericInputBox* f_input  = &((Data*)state->data)->f_input;
  NumericInputBox* i_input  = &((Data*)state->data)->i_input;
  NumericInputBox* z_input  = &((Data*)state->data)->z_input;
  NumericInputBox* h_input  = &((Data*)state->data)->h_input;
  NumericInputBox* p_input  = &((Data*)state->data)->p_input;
  Settings* settings        = ((Data*)state->data)->settings;
  bool* isContinue          = &((Data*)state->data)->isContinue;
  SDL_Renderer* renderer    = ((Data*)state->data)->renderer;

  int total_number_of_ships = f_input->value + i_input->value + z_input->value + h_input->value + p_input->value;
  settings->MAP_SIZE = map_size->value;
  int max_number_of_ships = (settings->MAP_SIZE * settings->MAP_SIZE) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH);
  int global_max = max_number_of_ships - total_number_of_ships;

  if(event->type == SDL_MOUSEBUTTONDOWN)
  {
    Vec2i mouse_pos = vec2i(event->button.x, event->button.y);

    if(button_isClick(play, mouse_pos)){
      if(total_number_of_ships <= max_number_of_ships) *isContinue = true;
      else printf("Too many ships!\n");
      return;
    }

    // Map Settings
    if(update_numeric_input_box(map_size, mouse_pos, INT_MAX, renderer))
    {
      settings->MAP_SIZE = map_size->value;
      return;
    }

    // Ships settings
    if(update_numeric_input_box(f_input, mouse_pos, global_max, renderer))
      return;
    if(update_numeric_input_box(i_input, mouse_pos, global_max, renderer))
      return;
    if(update_numeric_input_box(z_input, mouse_pos, global_max, renderer))
      return;
    if(update_numeric_input_box(h_input, mouse_pos, global_max, renderer))
      return;
    if(update_numeric_input_box(p_input, mouse_pos, global_max, renderer))
      return;
  }
}

State* cg_update(State* state)
{
  NumericInputBox* map_size = &((Data*)state->data)->map_size;
  NumericInputBox* f_input  = &((Data*)state->data)->f_input;
  NumericInputBox* i_input  = &((Data*)state->data)->i_input;
  NumericInputBox* z_input  = &((Data*)state->data)->z_input;
  NumericInputBox* h_input  = &((Data*)state->data)->h_input;
  NumericInputBox* p_input  = &((Data*)state->data)->p_input;
  Settings* settings        = ((Data*)state->data)->settings;
  bool* isContinue          = &((Data*)state->data)->isContinue;
  SDL_Renderer* renderer = ((Data*)state->data)->renderer;

  if(*isContinue == true)
  {
    settings->MAP_SIZE = map_size->value;
    settings->NUM_OF_SHIPS = f_input->value + i_input->value + z_input->value + h_input->value + p_input->value;
    settings->CELL_SIZE = settings->WINDOW_WIDTH < settings->WINDOW_HEIGHT ?
      settings->WINDOW_WIDTH / settings->MAP_SIZE : settings->WINDOW_HEIGHT / settings->MAP_SIZE;

    int count = 0;
    for(int i = 0; i < f_input->value; ++i, ++count) settings->ships[count] = F;
    for(int i = 0; i < i_input->value; ++i, ++count) settings->ships[count] = I;
    for(int i = 0; i < z_input->value; ++i, ++count) settings->ships[count] = Z;
    for(int i = 0; i < h_input->value; ++i, ++count) settings->ships[count] = H;
    for(int i = 0; i < p_input->value; ++i, ++count) settings->ships[count] = P;

    Game* game = new_game(settings);
    State* new_state = new_placing_ships_state(settings, game, renderer);
    delete_configure_game_state(state);
    return new_state;
  }

  return state;
}
