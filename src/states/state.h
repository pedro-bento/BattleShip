#ifndef STATE_H
#define STATE_H

#include <SDL.h>

typedef struct State State;

// Function pointer typedefs for generic State structure
typedef void (*Render)(State*, SDL_Renderer*);
typedef void (*HandleEvent)(State*, SDL_Event*);
typedef State* (*Update)(State*); // returns next state

// State
// generic structure for game states
// used in main game loop
// stores generic pointer for state data and render, handle_event and update function pointers
struct State
{
  void* data;
  Render render;
  HandleEvent handle_event;
  Update update;
};

#endif
