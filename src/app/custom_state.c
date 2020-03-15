#include "custom_state.h"
#include "../system/stacktrace.h"
#include "../ui/ui.h"
#include "../math/vec2.h"
#include "../config.h"

typedef struct
{
  Slider length_slider;
  Slider i_slider;
  Slider j_slider;
  Slider l_slider;
  Slider o_slider;
  Slider s_slider;
  Slider t_slider;
  Slider z_slider;
} CustomData;

void custom_render(State* s, SDL_Renderer* renderer);
void custom_handle_event(State* s, SDL_Event* e);
State* custom_update(State* s, SDL_Renderer* renderer);

State* custom_state_create()
{
  State* custom = malloc(sizeof(State));
  trace_assert(custom);
  CustomData* data = malloc(sizeof(CustomData));
  trace_assert(data);

  data->length_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.1f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);
  data->i_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.2f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);
  data->j_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.3f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);
  data->l_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.4f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);
  data->o_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.5f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);
  data->s_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.6f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);
  data->t_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.7f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);
  data->z_slider = slider(vec2(SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.8f),
    SCREEN_WIDTH * 0.17f, SCREEN_HEIGHT * 0.05f, MAX_NUM_OF_SHIPS);

  custom->data = (void*)data;
  custom->render = &custom_render;
  custom->handle_event = &custom_handle_event;
  custom->update = &custom_update;

  return custom;
}

void custom_render(State* s, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  slider_render(&((CustomData*)s->data)->length_slider, renderer);
  slider_render(&((CustomData*)s->data)->i_slider, renderer);
  slider_render(&((CustomData*)s->data)->j_slider, renderer);
  slider_render(&((CustomData*)s->data)->l_slider, renderer);
  slider_render(&((CustomData*)s->data)->o_slider, renderer);
  slider_render(&((CustomData*)s->data)->s_slider, renderer);
  slider_render(&((CustomData*)s->data)->t_slider, renderer);
  slider_render(&((CustomData*)s->data)->z_slider, renderer);

  SDL_RenderPresent(renderer);
}

void custom_handle_event(State* s, SDL_Event* e)
{
  slider_drag(&((CustomData*)s->data)->length_slider, e);
  slider_drag(&((CustomData*)s->data)->i_slider, e);
  slider_drag(&((CustomData*)s->data)->j_slider, e);
  slider_drag(&((CustomData*)s->data)->l_slider, e);
  slider_drag(&((CustomData*)s->data)->o_slider, e);
  slider_drag(&((CustomData*)s->data)->s_slider, e);
  slider_drag(&((CustomData*)s->data)->t_slider, e);
  slider_drag(&((CustomData*)s->data)->z_slider, e);
}

State* custom_update(State* s, SDL_Renderer* renderer)
{
  (void)renderer;
  return s;
}
