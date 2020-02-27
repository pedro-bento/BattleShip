#ifndef STATE_H
#define  STATE_H

#include <SDL.h>

typedef struct State State;
typedef void (*Render)(State*, SDL_Renderer*);
// return 1 if should go to next state
typedef int (*HandleEvent)(State*, SDL_Event*);
struct State
{
  void* data;
  Render render;
  HandleEvent handle_event;
};

#endif
