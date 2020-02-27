#include <SDL_ttf.h>

#include "begin_game_state.h"
#include "../ui/ui.h"
#include "../config.h"

void begin_game_state(SDL_Renderer* renderer, int* shouldQuit)
{
  TTF_Font* ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
  SDL_Color text_color = {255, 255, 255};
  SDL_Surface* surface_message = TTF_RenderText_Solid(ubuntu_mono, "classic", text_color);
  SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface_message);

  Button b = { .pos_rect = { .x = SCREEN_HEIGHT/2-90,
                         .y = SCREEN_HEIGHT/3-30,
                         .w = 180,
                         .h = 60},
               .text_rect = {.x = SCREEN_HEIGHT/2-80,
                 .y = SCREEN_HEIGHT/3-20,
                 .w = 160,
                 .h = 40},
               .text = message,
               .color = {0,0,0} };

  SDL_Event e;
  while(!*shouldQuit)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_QUIT){
        *shouldQuit = 1;
      }else if(e.type == SDL_MOUSEBUTTONDOWN){
        if(button_isClick(&b, vec2(e.button.x, e.button.y)))
          return;
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    button_render(&b, renderer);
    SDL_RenderPresent(renderer);
  }
}
