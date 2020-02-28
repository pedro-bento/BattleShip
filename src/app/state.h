#ifndef STATE_H
#define  STATE_H

#include <SDL.h>

typedef struct State State;
typedef void (*Render)(State*, SDL_Renderer*);
typedef void (*HandleEvent)(State*, SDL_Event*);
// return 1 if should go to next state
typedef int (*Update)(State*,SDL_Renderer*);
struct State
{
  void* data;
  Render render;
  HandleEvent handle_event;
  Update update;
};

#endif
