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

  data->renderer = renderer;

  data->settings = settings;

  data->title = text(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.065),
    settings->WINDOW_WIDTH * 0.4, settings->WINDOW_HEIGHT * 0.05,
    "Choose your settings!", settings->font_big, COLOR_RADIOACTIVE_GREEN, renderer);

  data->play = button(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.92),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.08, 5,
    "Let's play!", settings->font, COLOR_BLACK,
    COLOR_RADIOACTIVE_GREEN, renderer);

  data->map_size = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.18),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Map Size", settings->font,
    COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, MIN_MAP_SIZE, MIN_MAP_SIZE, MAX_MAP_SIZE);

  data->f_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.3),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Freddie Barr", settings->font,
    COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->i_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.42),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Iqra Mcneil", settings->font,
    COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->z_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.54),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Zarah Atkins", settings->font,
    COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->h_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.66),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Harri Eaton", settings->font,
    COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->p_input = numeric_input_box(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.78),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.045,
    "Priya Lynch", settings->font,
    COLOR_BLACK, COLOR_RADIOACTIVE_GREEN,
    renderer, 1, 1, 99);

  data->isContinue = false;

  state->data = data;
  state->render = cg_render;
  state->handle_event = cg_handle_event;
  state->update = cg_update;

  return state;
}

void delete_configure_game_state(State* state)
{
  delete_text(&((Data*)state->data)->title);
  delete_button(&((Data*)state->data)->play);
  delete_numeric_input_box(&((Data*)state->data)->map_size);
  delete_numeric_input_box(&((Data*)state->data)->f_input);
  delete_numeric_input_box(&((Data*)state->data)->i_input);
  delete_numeric_input_box(&((Data*)state->data)->z_input);
  delete_numeric_input_box(&((Data*)state->data)->h_input);
  delete_numeric_input_box(&((Data*)state->data)->p_input);
  free(state->data);
  free(state);
}

void cg_render(State* state, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_text(&((Data*)state->data)->title, renderer);
  render_button(&((Data*)state->data)->play, renderer);

  render_numeric_input_box(&((Data*)state->data)->map_size, renderer);
  render_numeric_input_box(&((Data*)state->data)->f_input, renderer);
  render_numeric_input_box(&((Data*)state->data)->i_input, renderer);
  render_numeric_input_box(&((Data*)state->data)->z_input, renderer);
  render_numeric_input_box(&((Data*)state->data)->h_input, renderer);
  render_numeric_input_box(&((Data*)state->data)->p_input, renderer);

  SDL_RenderPresent(renderer);
}

void cg_handle_event(State* state, SDL_Event* event)
{
  int total_number_of_ships =
    ((Data*)state->data)->f_input.value +
    ((Data*)state->data)->i_input.value +
    ((Data*)state->data)->z_input.value +
    ((Data*)state->data)->h_input.value +
    ((Data*)state->data)->p_input.value;

  int map_size = ((Data*)state->data)->settings->MAP_SIZE =
    ((Data*)state->data)->map_size.value;
  int max_number_of_ships = (map_size * map_size) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH);

  int global_max = max_number_of_ships - total_number_of_ships;

  if(event->type == SDL_MOUSEBUTTONDOWN)
  {
    Vec2i mouse_pos = vec2i(event->button.x, event->button.y);

    if(button_isClick(&((Data*)state->data)->play, mouse_pos)){
      if(total_number_of_ships <= max_number_of_ships)
        ((Data*)state->data)->isContinue = true;
      else
        printf("Too many ships! %d %d\n", total_number_of_ships, max_number_of_ships);
      return;
    }

    // Map Settings
    if(update_numeric_input_box(&((Data*)state->data)->map_size, mouse_pos, INT_MAX, ((Data*)state->data)->renderer)){
      ((Data*)state->data)->settings->MAP_SIZE = ((Data*)state->data)->map_size.value;
      return;
    }

    // Ships settings
    if(update_numeric_input_box(&((Data*)state->data)->f_input, mouse_pos, global_max, ((Data*)state->data)->renderer))
      return;
    if(update_numeric_input_box(&((Data*)state->data)->i_input, mouse_pos, global_max, ((Data*)state->data)->renderer))
      return;
    if(update_numeric_input_box(&((Data*)state->data)->z_input, mouse_pos, global_max, ((Data*)state->data)->renderer))
      return;
    if(update_numeric_input_box(&((Data*)state->data)->h_input, mouse_pos, global_max, ((Data*)state->data)->renderer))
      return;
    if(update_numeric_input_box(&((Data*)state->data)->p_input, mouse_pos, global_max, ((Data*)state->data)->renderer))
      return;
  }
}

State* cg_update(State* state)
{
  if(((Data*)state->data)->isContinue == true)
  {
    ((Data*)state->data)->settings->MAP_SIZE = ((Data*)state->data)->map_size.value;

    ((Data*)state->data)->settings->NUM_OF_SHIPS =
      ((Data*)state->data)->f_input.value +
      ((Data*)state->data)->i_input.value +
      ((Data*)state->data)->z_input.value +
      ((Data*)state->data)->h_input.value +
      ((Data*)state->data)->p_input.value;

    ((Data*)state->data)->settings->CELL_SIZE =
    ((Data*)state->data)->settings->WINDOW_WIDTH < ((Data*)state->data)->settings->WINDOW_HEIGHT ?
      ((Data*)state->data)->settings->WINDOW_WIDTH / ((Data*)state->data)->settings->MAP_SIZE :
      ((Data*)state->data)->settings->WINDOW_HEIGHT / ((Data*)state->data)->settings->MAP_SIZE;

    int count = 0;
    for(int i = 0; i < ((Data*)state->data)->f_input.value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = F;
    for(int i = 0; i < ((Data*)state->data)->i_input.value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = I;
    for(int i = 0; i < ((Data*)state->data)->z_input.value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = Z;
    for(int i = 0; i < ((Data*)state->data)->h_input.value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = H;
    for(int i = 0; i < ((Data*)state->data)->p_input.value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = P;

    SDL_Renderer* renderer = ((Data*)state->data)->renderer;
    Settings* settings = ((Data*)state->data)->settings;
    Game* game = new_game(settings);
    State* new_state = new_placing_ships_state(settings, game, renderer);
    delete_configure_game_state(state);
    return new_state;
  }
  return state;
}
