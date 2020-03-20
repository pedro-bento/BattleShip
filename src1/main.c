// In an attempt to minimize cache misses
// and overhaul program efficiency for future
// server (network) use while retaining code
// readability I have followed a mix of
// object-oriented and data-oriented approach

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "system/log.h"

int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  LOG_FAIL(SDL_Init(SDL_INIT_VIDEO) == 0);

  SDL_Window* window =
    SDL_CreateWindow("BattleShip", 0, 0, 800, 600, SDL_WINDOW_SHOWN);
  LOG_FAIL(window);

  SDL_Renderer* renderer =
    SDL_CreateRenderer(window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  LOG_FAIL(renderer);

  bool quit = false;
  SDL_Event event;
  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT) quit = true;
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
