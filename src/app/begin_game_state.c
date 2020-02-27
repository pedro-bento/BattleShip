#include <SDL_ttf.h>

#include "begin_game_state.h"
#include "../ui/ui.h"
#include "../config.h"
#include "../system/stacktrace.h"

typedef struct
{
  Button classic;
  Button custom;
} BeginData;

void begin_render(State* s, SDL_Renderer* renderer);
int begin_handle_event(State* s, SDL_Event* e);

State* begin_state_create(SDL_Renderer* renderer)
{
  State* begin = malloc(sizeof(State));
  trace_assert(begin);
  BeginData* data = malloc(sizeof(BeginData));
  trace_assert(data);

  TTF_Font* ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
  SDL_Color text_color = {255, 255, 255};

  SDL_Surface* surface_classic = TTF_RenderText_Solid(ubuntu_mono, "classic", text_color);
  SDL_Texture* classic_message = SDL_CreateTextureFromSurface(renderer, surface_classic);

  data->classic.pos_rect.x = SCREEN_WIDTH/2-90;
  data->classic.pos_rect.y = SCREEN_HEIGHT/3-30;
  data->classic.pos_rect.w = 180;
  data->classic.pos_rect.h = 60;

  data->classic.text_rect.x = SCREEN_HEIGHT/2-80;
  data->classic.text_rect.y = SCREEN_HEIGHT/3-20;
  data->classic.text_rect.w = 160;
  data->classic.text_rect.h = 40;

  data->classic.text = classic_message;

  data->classic.color.r = 0;
  data->classic.color.g = 0;
  data->classic.color.b = 0;

  SDL_Surface* surface_custom = TTF_RenderText_Solid(ubuntu_mono, "custom", text_color);
  SDL_Texture* custom_message = SDL_CreateTextureFromSurface(renderer, surface_custom);

  data->custom.pos_rect.x = SCREEN_WIDTH/2-90;
  data->custom.pos_rect.y = (1.5 * SCREEN_HEIGHT)/3-30;
  data->custom.pos_rect.w = 180;
  data->custom.pos_rect.h = 60;

  data->custom.text_rect.x = SCREEN_HEIGHT/2-80;
  data->custom.text_rect.y = (1.5 * SCREEN_HEIGHT)/3-20;
  data->custom.text_rect.w = 160;
  data->custom.text_rect.h = 40;

  data->custom.text = custom_message;

  data->custom.color.r = 0;
  data->custom.color.g = 0;
  data->custom.color.b = 0;

   begin->data = (void*)data;
   begin->render = &begin_render;
   begin->handle_event = &begin_handle_event;
   return begin;
}

void begin_state_destroy(State* state)
{
  free(state->data);
  free(state);
}

void begin_render(State* s, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  BeginData* data = (BeginData*)s->data;
  button_render(&data->classic, renderer);
  button_render(&data->custom, renderer);
  SDL_RenderPresent(renderer);
}

int begin_handle_event(State* s, SDL_Event* e)
{
  if(e->type == SDL_MOUSEBUTTONDOWN)
    if(button_isClick(&((BeginData*)s->data)->classic, vec2(e->button.x, e->button.y)))
      return 1;
  return 0;
}
