#include <SDL_ttf.h>

#include "begin_state.h"
#include "../ui/ui.h"
#include "../config.h"
#include "../system/stacktrace.h"
#include "init_state.h"
#include "../game/game.h"
#include "custom_state.h"

typedef enum
{
  CURRENT,
  INIT,
  CUSTOM,
} NextState;

typedef struct
{
  Button classic;
  Button tetris;
  Button custom;
  NextState next;
} BeginData;

void begin_render(State* s, SDL_Renderer* renderer);
void begin_handle_event(State* s, SDL_Event* e);
State* begin_update(State* s, SDL_Renderer* renderer);

State* begin_state_create(SDL_Renderer* renderer)
{
  State* begin = malloc(sizeof(State));
  trace_assert(begin);
  BeginData* data = malloc(sizeof(BeginData));
  trace_assert(data);

  SDL_Color text_color = {255, 255, 255};
  SDL_Color backgroud_color = {0, 0, 0};

  SDL_Surface* surface_classic = TTF_RenderText_Solid(ubuntu_mono, "Classic", text_color);
  SDL_Texture* classic_message = SDL_CreateTextureFromSurface(renderer, surface_classic);

  data->classic = button(vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.2),
    180, 60, 10, backgroud_color, classic_message);

  SDL_Surface* surface_tetris = TTF_RenderText_Solid(ubuntu_mono, "Tetris", text_color);
  SDL_Texture* tetris_message = SDL_CreateTextureFromSurface(renderer, surface_tetris);

  data->tetris = button(vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.35),
    180, 60, 10, backgroud_color, tetris_message);

  SDL_Surface* surface_custom = TTF_RenderText_Solid(ubuntu_mono, "Custom", text_color);
  SDL_Texture* custom_message = SDL_CreateTextureFromSurface(renderer, surface_custom);

  data->custom = button(vec2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5),
    180, 60, 10, backgroud_color, custom_message);

  data->next = CURRENT;

  begin->data = (void*)data;
  begin->render = &begin_render;
  begin->handle_event = &begin_handle_event;
  begin->update = &begin_update;

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
  button_render(&data->tetris, renderer);
  button_render(&data->custom, renderer);
  SDL_RenderPresent(renderer);
}

void begin_handle_event(State* s, SDL_Event* e)
{
  if(e->type == SDL_MOUSEBUTTONDOWN){
    if(button_isClick(&((BeginData*)s->data)->classic, vec2(e->button.x, e->button.y))){
      ((BeginData*)s->data)->next = INIT;
      config_classic();
    }else if(button_isClick(&((BeginData*)s->data)->tetris, vec2(e->button.x, e->button.y))){
      ((BeginData*)s->data)->next = INIT;
      config_tetris();
    }else if(button_isClick(&((BeginData*)s->data)->custom, vec2(e->button.x, e->button.y))){
      ((BeginData*)s->data)->next = CUSTOM;
    }
  }
}

State* begin_update(State* s, SDL_Renderer* renderer)
{
  switch(((BeginData*)s->data)->next)
  {
    case INIT: {
      begin_state_destroy(s);
      Game* game = game_create();
      return init_state_create(game, renderer);
    };

    case CUSTOM: {
      begin_state_destroy(s);
      return custom_state_create(renderer);
    };

    default : break;
  }

  return s;
}
