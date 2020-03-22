// In an attempt to minimize cache misses
// and increase overhaul program efficiency for
// future server (network) use while retaining
// code readability I have followed an approach
// that is mix of object-oriented and data-oriented

#include <SDL.h>
// #include <SDL_ttf.h>

#include "config.h"
#include "system/log.h"
#include "engine.h"

int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  LOG_FAIL(!SDL_Init(SDL_INIT_VIDEO));

  SDL_Window* window =
    SDL_CreateWindow("BattleShip", 0, 0,
      WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  LOG_FAIL(window);

  SDL_Renderer* renderer =
    SDL_CreateRenderer(window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  LOG_FAIL(renderer);

  engine_run(renderer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
