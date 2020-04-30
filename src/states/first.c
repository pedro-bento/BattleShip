#include "first.h"
#include "configure_game.h"
#include "placing_ships.h"
#include "../math/math.h"
#include "../graphics/ui.h"
#include "../system/log.h"

typedef enum
{
  THIS,
  MANUAL,
  RANDOM,
} Next;

typedef struct
{
  SDL_Renderer* renderer;
  Settings* settings;
  Text title;
  Button manual;
  Button random;
  Next next;
} Data;

void fst_render(State* state, SDL_Renderer* renderer);
void fst_handle_event(State* state, SDL_Event* event);
State* fst_update(State* state);

State* new_first_state(Settings* settings, SDL_Renderer* renderer)
{
  State* state = malloc(sizeof(State));
  LOG_FAIL(state);

  Data* data = malloc(sizeof(Data));
  LOG_FAIL(data);

  data->renderer = renderer;

  data->settings = settings;

  data->title = text(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.08),
    settings->WINDOW_WIDTH * 0.4, settings->WINDOW_HEIGHT * 0.05,
    "BattleShip", settings->font_big, COLOR_RADIOACTIVE_GREEN, renderer);

  data->manual = button(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.35),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.08, 5,
    "Manual Config", settings->font, COLOR_BLACK,
    COLOR_RADIOACTIVE_GREEN, renderer);

  data->random = button(
    vec2i(settings->WINDOW_WIDTH * 0.5, settings->WINDOW_HEIGHT * 0.5),
    settings->WINDOW_WIDTH * 0.2, settings->WINDOW_HEIGHT * 0.08, 5,
    "Random Config", settings->font, COLOR_BLACK,
    COLOR_RADIOACTIVE_GREEN, renderer);

  data->next = THIS;

  state->data = data;
  state->render = fst_render;
  state->handle_event = fst_handle_event;
  state->update = fst_update;

  return state;
}

void delete_first_state(State* state)
{
  delete_text(&((Data*)state->data)->title);
  delete_button(&((Data*)state->data)->manual);
  delete_button(&((Data*)state->data)->random);
  free(state->data);
  free(state);
}

void fst_render(State* state, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_text(&((Data*)state->data)->title, renderer);
  render_button(&((Data*)state->data)->manual, renderer);
  render_button(&((Data*)state->data)->random, renderer);

  SDL_RenderPresent(renderer);
}

void fst_handle_event(State* state, SDL_Event* event)
{
  if(event->type == SDL_MOUSEBUTTONDOWN)
  {
    Vec2i mouse_pos = vec2i(event->button.x, event->button.y);
    if(button_isClick(&((Data*)state->data)->manual, mouse_pos))
      ((Data*)state->data)->next = MANUAL;
    else if(button_isClick(&((Data*)state->data)->random, mouse_pos))
      ((Data*)state->data)->next = RANDOM;
  }
}

State* fst_update(State* state)
{
  if(((Data*)state->data)->next == MANUAL){
    SDL_Renderer* renderer = ((Data*)state->data)->renderer;
    Settings* settings = ((Data*)state->data)->settings;
    State* new_state = new_configure_game_state(settings, renderer);
    delete_first_state(state);
    return new_state;
  }else if(((Data*)state->data)->next == RANDOM){
    ((Data*)state->data)->settings->MAP_SIZE = rand_range(MIN_MAP_SIZE, MAX_MAP_SIZE);
    int map_size = ((Data*)state->data)->settings->MAP_SIZE;
    int max_number_of_ships = (map_size * map_size) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH);

    ((Data*)state->data)->settings->CELL_SIZE =
    ((Data*)state->data)->settings->WINDOW_WIDTH < ((Data*)state->data)->settings->WINDOW_HEIGHT ?
      ((Data*)state->data)->settings->WINDOW_WIDTH / ((Data*)state->data)->settings->MAP_SIZE :
      ((Data*)state->data)->settings->WINDOW_HEIGHT / ((Data*)state->data)->settings->MAP_SIZE;

    int count = 0;
    int value = rand_range(1, max_number_of_ships/5);
    for(int i = 0; i < value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = F;

    value = rand_range(1, max_number_of_ships/5);
    for(int i = 0; i < value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = I;

    value = rand_range(1, max_number_of_ships/5);
    for(int i = 0; i < value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = Z;

    value = rand_range(1, max_number_of_ships/5);
    for(int i = 0; i < value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = H;

    value = rand_range(1, max_number_of_ships/5);
    for(int i = 0; i < value; ++i, ++count)
      ((Data*)state->data)->settings->ships[count] = P;

    ((Data*)state->data)->settings->NUM_OF_SHIPS = count;

    SDL_Renderer* renderer = ((Data*)state->data)->renderer;
    Settings* settings = ((Data*)state->data)->settings;
    Game* game = new_game(settings);
    State* new_state = new_placing_ships_state(settings, game, renderer);
    delete_first_state(state);
    return new_state;
  }

  return state;
}
