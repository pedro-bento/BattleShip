#include "app.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "../game/game.h"
#include "../renderer/renderer.h"
#include "begin_game_state.h"
#include "init_game_state.h"
#include "playing_game_state.h"
#include "end_game_state.h"


/* TODO: implemente rendering with general State struct */
typedef struct State State;
typedef void (*Render)(State*);
typedef void (*HandleEvent)(State*, SDL_Event*);
struct State
{
  void* data;
  Render render;
  HandleEvent handle_event;
};


void app_run()
{
  Game game;
  game_init_empty(&game);
  int shouldQuit = 0;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_WIDTH + FOOTER_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  TTF_Init();

  begin_game_state(renderer, &shouldQuit);
  init_game_state(&game, renderer, &shouldQuit);
  playing_game_state(&game, renderer, &shouldQuit);
  end_game_state(&game, renderer, &shouldQuit);

  if(game.state == PLAYER1_WIN) printf("\nPLAYER 1 WON!\n");
  else printf("\nPLAYER 2 WON!\n");

  game_free(&game);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
