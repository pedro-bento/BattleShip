#include <SDL.h>
#include <SDL_ttf.h>

#include <stdbool.h>
#include <stdint.h>

#include "config.h"
#include "system/log.h"
#include "math/vec.h"
#include "physics/ship.h"
#include "physics/player.h"
#include "physics/game.h"
#include "graphics/renderer.h"
#include "graphics/ui.h"
#include "states/configure_game.h"

int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  LOG_FAIL(!TTF_Init());
  TTF_Font* font = TTF_OpenFont("res/UbuntuMono-R.ttf", 128);
  LOG_FAIL(font);

  Settings settings =
  {
    .WINDOW_WIDTH = 800,
    .WINDOW_HEIGHT = 600,
    .font = font,
  };

  LOG_FAIL(!SDL_Init(SDL_INIT_VIDEO));

  SDL_Window* window = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, settings.WINDOW_WIDTH,
    settings.WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  LOG_FAIL(window);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  LOG_FAIL(renderer);
  LOG_FAIL(!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND));

  State* state = new_configure_game_state(&settings, renderer);
  bool quit = false;
  SDL_Event event;
  while(!quit)
  {
    state->render(state, renderer);

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
        break;
      }

      state->handle_event(state, &event);
    }

    if((state = state->update(state)) == NULL)
      quit = true;
  }

  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
