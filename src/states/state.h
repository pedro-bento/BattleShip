#ifndef STATE_H
#define STATE_H

#include <SDL.h>

typedef struct State State;
typedef void (*Render)(State*, SDL_Renderer*);
typedef void (*HandleEvent)(State*, SDL_Event*);
typedef State* (*Update)(State*); // returns next state
struct State
{
  void* data;
  Render render;
  HandleEvent handle_event;
  Update update;
};

#endif
