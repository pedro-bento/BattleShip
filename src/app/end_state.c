#include "end_state.h"
#include "../renderer/renderer.h"
#include "../system/stacktrace.h"

typedef struct
{
  Game* game;
} EndData;

void end_render(State* s, SDL_Renderer* renderer);
void end_handle_event(State* s, SDL_Event* e);
State* end_update(State* s, SDL_Renderer* renderer);

State* end_state_create(Game* game)
{
  State* end = malloc(sizeof(State));
  trace_assert(end);
  EndData* data = malloc(sizeof(EndData));
  trace_assert(data);

  data->game = game;

  end->data = (void*)data;
  end->render = &end_render;
  end->handle_event = &end_handle_event;
  end->update = &end_update;

  return end;
}

void end_state_destroy(State* state)
{
  free(state->data);
  free(state);
}

void end_render(State* s, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  render_all(renderer, ((EndData*)s->data)->game);
  SDL_RenderPresent(renderer);
}

void end_handle_event(State* s, SDL_Event* e)
{
  (void)s;
  (void)e;
}

State* end_update(State* s, SDL_Renderer* renderer)
{
  (void)renderer;
  return s;
}
