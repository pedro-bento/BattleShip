// In an attempt to minimize cache misses
// and overhaul program efficiency for future
// server (network) use while retaining code
// readability I have followed a mix of
// object-oriented and data-oriented approach

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdint.h>

#include "system/log.h"

typedef struct
{
  int16_t x;
  int16_t y;
} Vec2i;

#define CELL_SIZE 30
#define MAX_SHIP_SIZE 5
typedef char CellState;
#define CellState_EMPTY 0
#define CellState_GOOD  1
#define CellState_HIT   2
#define CellState_MISS  3
typedef struct
{
  Vec2i top_left;
  Vec2i bottom_right;
  uint8_t shot_count;
  CellState states[MAX_SHIP_SIZE][MAX_SHIP_SIZE];
} Ship;

void render_ship(Ship* ship, SDL_Renderer* renderer)
{
  // collect all rects (cells) and render everything in a single batch
  // maximum number of cells a ship can occupy
  SDL_Rect rects[MAX_SHIP_SIZE * MAX_SHIP_SIZE];
  size_t count = 0;
  for(size_t x = ship->top_left.x; x <= ship->bottom_right.x; ++x)
  {
    for(size_t y = ship->top_left.y; y <= ship->bottom_right.y; ++y)
    {
      // TODO: implement 2 batches, one for state_good other for state_hit
      if(ship->states[x][y] == CellState_GOOD || ship->states[x][y] == CellState_HIT)
      {
        rects[count].x = y * CELL_SIZE;
        rects[count].y = x * CELL_SIZE;
        rects[count].w = rects[count].h = CELL_SIZE;
        ++count;
      }
    }
  }

  LOG_FAIL(SDL_SetRenderDrawColor(renderer, 8, 155, 100, 255) == 0);
  LOG_FAIL(SDL_RenderFillRects(renderer, rects, count) == 0);
}

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

  Ship ship =
  {
      .top_left     = (Vec2i){.x = 0, .y = 0},
      .bottom_right = (Vec2i){.x = 4, .y = 4},
      .shot_count   = 0,
      .states       =
      {
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
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

    SDL_SetRenderDrawColor(renderer, 51, 65, 133, 255);
    SDL_RenderClear(renderer);
    render_ship(&ship, renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
