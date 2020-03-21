// In an attempt to minimize cache misses
// and increase overhaul program efficiency for
// future server (network) use while retaining
// code readability I have followed an approach
// that is mix of object-oriented and data-oriented

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdint.h>

#include "config.h"
#include "system/log.h"
#include "math/vec.h"
#include "physics/ship.h"
#include "graphics/renderer.h"

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

  Ship ship =
  {
      .top_left     = vec2i(0, 0),
      .bottom_right = vec2i(4, 4),
      .shot_count   = 0,
      .states       =
      {
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 2},
      },
  };

  bool quit = false;
  SDL_Event event;
  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT) quit = true;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    render_ship(&ship, renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(250);

    ship_rotate_90(&ship, true);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
