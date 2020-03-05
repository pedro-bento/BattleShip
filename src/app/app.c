#include "app.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "../game/game.h"
#include "../renderer/renderer.h"
#include "state.h"
#include "begin_state.h"
#include "init_state.h"
#include "playing_state.h"
#include "end_state.h"

void app_run()
{
  Game game;
  game_init_empty(&game);
  int shouldQuit = 0;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  TTF_Init();

  State* game_states[] = {
    begin_state_create(renderer),
    init_state_create(&game, renderer),
    playing_state_create(&game, renderer),
    end_state_create(&game),
  };

  SDL_Event e;
  size_t stateID = 0, maxID = 3;
  while(!shouldQuit && stateID <= maxID)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_QUIT)
        shouldQuit = 1;
      game_states[stateID]->handle_event(game_states[stateID], &e);
    }

    game_states[stateID]->render(game_states[stateID], renderer);

    if(game_states[stateID]->update(game_states[stateID], renderer))
      stateID++;
  }

  // Just for debug
  if(game.state == PLAYER1_WIN) printf("\nPLAYER 1 WON!\n");
  else printf("\nPLAYER 2 WON!\n");

  game_free(&game);
  begin_state_destroy(game_states[0]);
  init_state_destroy(game_states[1]);
  playing_state_destroy(game_states[2]);
  end_state_destroy(game_states[3]);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
