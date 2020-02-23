#include "app.h"

#include <SDL.h>

#include "../game/game.h"
#include "../renderer/renderer.h"
#include "init_game_state.h"
#include "playing_game_state.h"
#include "end_game_state.h"

void app_run()
{
  Game game;
  game_init(&game);
  int shouldQuit = 0;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_WIDTH + FOOTER_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  init_game_state(&game, renderer, &shouldQuit);
  playing_game_state(&game, renderer, &shouldQuit);
  end_game_state(&game, renderer, &shouldQuit);

  if(game.state == PLAYER1_WIN) printf("\nPLAYER 1 WON!\n");
  else printf("\nPLAYER 2 WON!\n");

  game_free(&game);

  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  // SDL_Quit(); // malloc_consolidation error?????
}
