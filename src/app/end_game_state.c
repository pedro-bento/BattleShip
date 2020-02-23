#include "end_game_state.h"
#include "../renderer/renderer.h"

void end_game_state(Game* game, SDL_Renderer* renderer, int* shouldQuit)
{
  SDL_Event e;
  while(!*shouldQuit)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_QUIT){
        *shouldQuit = 1;
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    render_all(renderer, game);
    SDL_RenderPresent(renderer);
  }
}
