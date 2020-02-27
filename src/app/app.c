#include "app.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "../game/game.h"
#include "../renderer/renderer.h"
#include "state.h"
#include "begin_game_state.h"
#include "init_game_state.h"
#include "playing_game_state.h"
#include "end_game_state.h"

void app_run()
{
  Game game;
  game_init_empty(&game);
  int shouldQuit = 0;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_WIDTH + FOOTER_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  TTF_Init();

  State* game_states[] = {
    begin_state_create(renderer),
  };

  size_t stateID = 0, nextState = 0;
  SDL_Event e;
  while(!shouldQuit && !nextState)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_QUIT)
        shouldQuit = 1;
      if(game_states[stateID]->handle_event(game_states[stateID], &e))
        nextState = 1;
    }
    game_states[stateID]->render(game_states[stateID], renderer);
  }

  init_game_state(&game, renderer, &shouldQuit);
  playing_game_state(&game, renderer, &shouldQuit);
  end_game_state(&game, renderer, &shouldQuit);

  if(game.state == PLAYER1_WIN) printf("\nPLAYER 1 WON!\n");
  else printf("\nPLAYER 2 WON!\n");

  game_free(&game);
  begin_state_destroy(game_states[0]);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
