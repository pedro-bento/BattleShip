#include "renderer.h"
#include "color.h"
#include "../config.h"
#include "../system/log.h"
#include "../math/vec.h"
#include "../physics/ship.h"

void render_rects(const SDL_Rect* rects, int count, Color color, SDL_Renderer* renderer)
{
  LOG_FAIL(!SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a));
  LOG_FAIL(!SDL_RenderFillRects(renderer, rects, count));
}

void render_ship(Ship* ship, SDL_Renderer* renderer)
{
  // collect all rects (cells) and render everything in a single batch
  // maximum number of cells a ship can occupy is the size of the bitmap
  SDL_Rect cells_good[MAX_SHIP_WIDTH * MAX_SHIP_WIDTH];
  SDL_Rect cells_hit[MAX_SHIP_WIDTH * MAX_SHIP_WIDTH];

  size_t count_good = 0;
  size_t count_hit  = 0;

  const size_t begin_x = ship->top_left.x;
  const size_t end_x   = ship->bottom_right.x;

  const size_t begin_y = ship->top_left.y;
  const size_t end_y   = ship->bottom_right.y;

  for(size_t x = begin_x; x <= end_x; ++x)
  {
    for(size_t y = begin_y; y <= end_y; ++y)
    {
      switch(ship->states[x - begin_x][y - begin_y])
      {
        case SHIP_STATE_GOOD :{
          cells_good[count_good].x = y * CELL_SIZE;
          cells_good[count_good].y = x * CELL_SIZE;
          cells_good[count_good].w = cells_good[count_good].h = CELL_SIZE;
          ++count_good;
        } break;

        case SHIP_STATE_HIT :{
          cells_hit[count_hit].x = y * CELL_SIZE;
          cells_hit[count_hit].y = x * CELL_SIZE;
          cells_hit[count_hit].w = cells_hit[count_hit].h = CELL_SIZE;
          ++count_hit;
        } break;
      }
    }
  }

  render_rects(cells_good, count_good, COLOR_RADIOACTIVE_GREEN, renderer);
  render_rects(cells_hit, count_hit, COLOR_CRIMSON_RED, renderer);
}

void render_player(Player* player, SDL_Renderer* renderer)
{
  for(size_t i = 0; i < player->ships_count; ++i)
    render_ship(&player->ships[i], renderer);
}
