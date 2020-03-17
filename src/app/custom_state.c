#include "custom_state.h"
#include "../system/stacktrace.h"
#include "../ui/ui.h"
#include "../math/vec2.h"
#include "../config.h"
#include "init_state.h"

typedef struct
{
  Button start;
  SliderField length_slider;
  SliderField i_slider;
  SliderField j_slider;
  SliderField l_slider;
  SliderField o_slider;
  SliderField s_slider;
  SliderField t_slider;
  SliderField z_slider;
  int next;
} CustomData;

void custom_render(State* s, SDL_Renderer* renderer);
void custom_handle_event(State* s, SDL_Event* e);
State* custom_update(State* s, SDL_Renderer* renderer);

State* custom_state_create(SDL_Renderer* renderer)
{
  State* custom = malloc(sizeof(State));
  trace_assert(custom);
  CustomData* data = malloc(sizeof(CustomData));
  trace_assert(data);

  SDL_Surface* surface = TTF_RenderText_Solid(ubuntu_mono, "Start", (SDL_Color){255, 255, 255});
  SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
  data->start = button(vec2(SCREEN_WIDTH * 0.66f, SCREEN_HEIGHT * 0.1f), SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f, SCREEN_HEIGHT * 0.01f, (SDL_Color){0, 0, 0}, message);

  data->length_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.1f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_MAP_SIZE, "Length", renderer);
  data->i_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.2f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS, "Num I", renderer);
  data->j_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.3f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS, "Num J", renderer);
  data->l_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.4f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS, "Num L", renderer);
  data->o_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.5f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS, "Num O", renderer);
  data->s_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.6f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS, "Num S", renderer);
  data->t_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.7f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS, "Num T", renderer);
  data->z_slider = sliderfield(vec2(SCREEN_WIDTH * 0.22f, SCREEN_HEIGHT * 0.8f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS, "Num Z", renderer);

  data->next = 0;

  custom->data = (void*)data;
  custom->render = &custom_render;
  custom->handle_event = &custom_handle_event;
  custom->update = &custom_update;

  return custom;
}

void custom_state_destroy(State* state)
{
  free(state->data);
  free(state);
}

void custom_render(State* s, SDL_Renderer* renderer)
{
  CustomData* data = ((CustomData*)s->data);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  button_render(&data->start, renderer);

  sliderfield_render(&data->length_slider, renderer);
  sliderfield_render(&data->i_slider, renderer);
  sliderfield_render(&data->j_slider, renderer);
  sliderfield_render(&data->l_slider, renderer);
  sliderfield_render(&data->o_slider, renderer);
  sliderfield_render(&data->s_slider, renderer);
  sliderfield_render(&data->t_slider, renderer);
  sliderfield_render(&data->z_slider, renderer);

  SDL_RenderPresent(renderer);
}

void custom_handle_event(State* s, SDL_Event* e)
{
  CustomData* data = ((CustomData*)s->data);
  sliderfield_drag(&data->length_slider, e);
  sliderfield_drag(&data->i_slider, e);
  sliderfield_drag(&data->j_slider, e);
  sliderfield_drag(&data->l_slider, e);
  sliderfield_drag(&data->o_slider, e);
  sliderfield_drag(&data->s_slider, e);
  sliderfield_drag(&data->t_slider, e);
  sliderfield_drag(&data->z_slider, e);

  if(e->type == SDL_MOUSEBUTTONDOWN){
    if(button_isClick(&data->start, vec2(e->button.x, e->button.y))){
      data->next = 1;
      config_custom(
        (int)data->length_slider.sld.value,
        (int)data->i_slider.sld.value,
        (int)data->j_slider.sld.value,
        (int)data->l_slider.sld.value,
        (int)data->o_slider.sld.value,
        (int)data->s_slider.sld.value,
        (int)data->t_slider.sld.value,
        (int)data->z_slider.sld.value);
    }
  }
}

State* custom_update(State* s, SDL_Renderer* renderer)
{
  CustomData* data = ((CustomData*)s->data);
  if(data->next){
    custom_state_destroy(s);
    Game* game = game_create();
    return init_state_create(game, renderer);
  }

  return s;
}
