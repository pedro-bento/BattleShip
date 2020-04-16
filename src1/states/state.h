#ifndef STATE_H
#define STATE_H

#include <SDL.h>
#include <stdbool.h>

typedef struct State State;
typedef void (*Render)(State*, SDL_Renderer*);
typedef void (*HandleEvent)(State*, SDL_Event*);
typedef bool (*Update)(State*); // returns 'true' on state change
struct State
{
  void* data;
  Render render;
  HandleEvent handle_event;
  Update update;
};

#endif
