#include "app.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "../game/game.h"
#include "../renderer/renderer.h"
#include "state.h"
#include "begin_state.h"
#include "custom_state.h"

void app_run()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  TTF_Init();

  SDL_Event e;
  int isQuit = 0;
  State* current_state = begin_state_create(renderer);

  while(!isQuit)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_QUIT) isQuit = 1;
      current_state->handle_event(current_state, &e);
    }

    current_state->render(current_state, renderer);

    current_state = current_state->update(current_state, renderer);
    if(current_state == NULL) isQuit = 1;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
