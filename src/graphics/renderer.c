#include "renderer.h"
#include "color.h"
#include "../config.h"
#include "../system/log.h"
#include "../system/quadtree.h"
#include "../math/vec.h"
#include "../math/math.h"
#include "../physics/ship.h"

static inline void set_render_color(Color color, SDL_Renderer* renderer)
{
  LOG_FAIL(!SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a));
}

void render_rects(const SDL_Rect* rects, int count, Color color, SDL_Renderer* renderer)
{
  set_render_color(color, renderer);
  LOG_FAIL(!SDL_RenderFillRects(renderer, rects, count));
}

void render_ship(Ship* ship, SDL_Renderer* renderer, Settings* settings, bool is_preview, float scale, int xOffset, int yOffset)
{
  size_t min = MIN(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t max = MAX(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t map_offset = (max - min) / 2;

  // collect all rects (cells) and render everything in a single batch
  // maximum number of cells a ship can occupy is the size of the bitmap
  SDL_Rect cells_good[MAX_SHIP_WIDTH * MAX_SHIP_WIDTH];
  SDL_Rect cells_hit[MAX_SHIP_WIDTH * MAX_SHIP_WIDTH];
  SDL_Rect cells_miss[MAX_SHIP_WIDTH * MAX_SHIP_WIDTH];

  size_t count_good = 0;
  size_t count_hit  = 0;
  size_t count_miss  = 0;

  const int begin_x = MAX(ship->top_left.x, 0);
  const int end_x   = ship->bottom_right.x;

  const int begin_y = MAX(ship->top_left.y, 0);
  const int end_y   = ship->bottom_right.y;

  const int offset_x = ship->top_left.x < 0 ? -ship->top_left.x : 0;
  const int offset_y = ship->top_left.y < 0 ? -ship->top_left.y : 0;

  for(int x = begin_x; x <= end_x; ++x)
  {
    for(int y = begin_y; y <= end_y; ++y)
    {
      switch(ship->bitmap.states[x - begin_x + offset_x][y - begin_y + offset_y])
      {
        case SHIP_STATE_GOOD :{
          cells_good[count_good].x = map_offset + y * settings->CELL_SIZE * scale + xOffset;
          cells_good[count_good].y = x * settings->CELL_SIZE * scale + yOffset;
          cells_good[count_good].w = cells_good[count_good].h = settings->CELL_SIZE * scale;
          ++count_good;
        } break;

        case SHIP_STATE_HIT :{
          cells_hit[count_hit].x = map_offset + y * settings->CELL_SIZE * scale + xOffset;
          cells_hit[count_hit].y = x * settings->CELL_SIZE * scale + yOffset;
          cells_hit[count_hit].w = cells_hit[count_hit].h = settings->CELL_SIZE * scale;
          ++count_hit;
        } break;

        case SHIP_STATE_MISS :{
          cells_miss[count_miss].x = map_offset + y * settings->CELL_SIZE * scale + xOffset;
          cells_miss[count_miss].y = x * settings->CELL_SIZE * scale + yOffset;
          cells_miss[count_miss].w = cells_miss[count_miss].h = settings->CELL_SIZE * scale;
          ++count_miss;
        } break;
      }
    }
  }

  if(is_preview){
    render_rects(cells_good, count_good, COLOR_FLUORESCENT_YELLOW_A, renderer);
  }else{
    render_rects(cells_good, count_good, COLOR_RADIOACTIVE_GREEN_A, renderer);
    render_rects(cells_hit, count_hit, COLOR_CRIMSON_RED_A, renderer);
    render_rects(cells_miss, count_miss, COLOR_SAINT_PATRICK_BLUE_A, renderer);
  }
}

void render_shot(Vec2i pos, SDL_Renderer* renderer, Settings* settings)
{
  size_t min = MIN(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t max = MAX(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t offset = (max - min) / 2;

  SDL_Rect rect = {
    .x = pos.y * settings->CELL_SIZE + offset,
    .y = pos.x * settings->CELL_SIZE,
    .w = settings->CELL_SIZE,
    .h = settings->CELL_SIZE
  };

  set_render_color(COLOR_FLUORESCENT_YELLOW_A, renderer);
  SDL_RenderFillRect(renderer, &rect);
}

void render_ship_preview(Ship* ship, SDL_Renderer* renderer, Settings* settings)
{
  render_ship(ship, renderer, settings, true, 1, 0, 0);
}

bool not_rendered(Ship* eval, Ship* rendered[], int rendered_count)
{
  for(int i = 0; i < rendered_count; ++i)
    if(rendered[i] == eval)
      return false;
  return true;
}

#ifdef A

void render_player0(Player* player, SDL_Renderer* renderer, Settings* settings, float scale, int xOffset, int yOffset)
{
  Ship* rendered[(settings->MAP_SIZE * settings->MAP_SIZE) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH)];
  int rendered_count = 0;

  for(size_t x = 0; x < settings->MAP_SIZE; x++)
  {
    for(size_t y = 0; y < settings->MAP_SIZE; y++)
    {
      if(player->map[x][y].ship != NULL)
      {
        if(not_rendered(player->map[x][y].ship, rendered, rendered_count))
        {
          rendered[rendered_count] = player->map[x][y].ship;
          rendered_count++;
          render_ship(player->map[x][y].ship, renderer, settings, false, scale, xOffset, yOffset);
        }
      }
    }
  }
}

#else

void render_player0(Player* player, SDL_Renderer* renderer, Settings* settings, float scale, int xOffset, int yOffset)
{
  Ship* rendered[(settings->MAP_SIZE * settings->MAP_SIZE) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH)];
  int rendered_count = 0;

  for(size_t x = 0; x < settings->MAP_SIZE; x++)
  {
    for(size_t y = 0; y < settings->MAP_SIZE; y++)
    {
      QT_Node* node = qt_find(player->map, vec2i(x,y));
      if(node == NULL) continue;
      Cell* cell = (Cell*)node->data;
      if(cell->ship == NULL) continue;
      Ship* ship = cell->ship;

      if(not_rendered(ship, rendered, rendered_count))
      {
        rendered[rendered_count] = ship;
        rendered_count++;
        render_ship(ship, renderer, settings, false, scale, xOffset, yOffset);
      }
    }
  }
}

#endif

void render_player(Player* player, SDL_Renderer* renderer, Settings* settings)
{
  render_player0(player, renderer, settings, 1, 0, 0);
}

#ifdef A

void render_opponent(Player* player, SDL_Renderer* renderer, Settings* settings)
{
  size_t min = MIN(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t max = MAX(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t map_offset = (max - min) / 2;

  size_t max_size = settings->MAP_SIZE * settings->MAP_SIZE;
  SDL_Rect cells_hit[max_size];
  SDL_Rect cells_miss[max_size];

  size_t count_hit  = 0;
  size_t count_miss  = 0;

  for(int x = 0; x < settings->MAP_SIZE; ++x)
  {
    for(int y = 0; y < settings->MAP_SIZE; ++y)
    {
      switch(player->map[x][y].shot_state)
      {
        case SHOT_STATE_HIT :{
          cells_hit[count_hit].x = map_offset + y * settings->CELL_SIZE;
          cells_hit[count_hit].y = x * settings->CELL_SIZE;
          cells_hit[count_hit].w = cells_hit[count_hit].h = settings->CELL_SIZE;
          ++count_hit;
        } break;

        case SHOT_STATE_MISS :{
          cells_miss[count_miss].x = map_offset + y * settings->CELL_SIZE;
          cells_miss[count_miss].y = x * settings->CELL_SIZE;
          cells_miss[count_miss].w = cells_miss[count_miss].h = settings->CELL_SIZE;
          ++count_miss;
        } break;
      }
    }
  }

  render_rects(cells_hit, count_hit, COLOR_CRIMSON_RED_A, renderer);
  render_rects(cells_miss, count_miss, COLOR_SAINT_PATRICK_BLUE_A, renderer);
}

#else

void quadtree_collect_shot_state(QT* qt, Settings* settings, SDL_Rect cells_hit[], size_t* count_hit, SDL_Rect cells_miss[], size_t* count_miss)
{
  if(qt == NULL) return;
  quadtree_collect_shot_state(qt->t_left, settings, cells_hit, count_hit, cells_miss, count_miss);
  quadtree_collect_shot_state(qt->t_right, settings, cells_hit, count_hit, cells_miss, count_miss);
  quadtree_collect_shot_state(qt->b_left, settings, cells_hit, count_hit, cells_miss, count_miss);
  quadtree_collect_shot_state(qt->b_right, settings, cells_hit, count_hit, cells_miss, count_miss);
  if(qt->node == NULL) return;

  SHOT_STATE shot_state = ((Cell*)(qt->node->data))->shot_state;

  size_t min = MIN(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t max = MAX(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t map_offset = (max - min) / 2;

  switch(shot_state)
  {
    case SHOT_STATE_HIT :{
      cells_hit[*count_hit].x = map_offset + qt->node->pos.y * settings->CELL_SIZE;
      cells_hit[*count_hit].y = qt->node->pos.x * settings->CELL_SIZE;
      cells_hit[*count_hit].w = cells_hit[*count_hit].h = settings->CELL_SIZE;
      *count_hit += 1;
    } break;

    case SHOT_STATE_MISS :{
      cells_miss[*count_miss].x = map_offset + qt->node->pos.y * settings->CELL_SIZE;
      cells_miss[*count_miss].y = qt->node->pos.x * settings->CELL_SIZE;
      cells_miss[*count_miss].w = cells_miss[*count_miss].h = settings->CELL_SIZE;
      *count_miss += 1;
    } break;

    default : break;
  }
}

void render_opponent(Player* player, SDL_Renderer* renderer, Settings* settings)
{
  size_t max_size = settings->MAP_SIZE * settings->MAP_SIZE;
  SDL_Rect cells_hit[max_size];
  SDL_Rect cells_miss[max_size];

  size_t count_hit = 0;
  size_t count_miss = 0;

  quadtree_collect_shot_state(player->map, settings, cells_hit, &count_hit, cells_miss, &count_miss);

  render_rects(cells_hit, count_hit, COLOR_CRIMSON_RED_A, renderer);
  render_rects(cells_miss, count_miss, COLOR_SAINT_PATRICK_BLUE_A, renderer);
}

#endif

void render_grid0(SDL_Renderer* renderer, Settings* settings, float scale, int xOffset, int yOffset)
{
  size_t min = MIN(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t max = MAX(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t offset = (max - min) / 2;
  set_render_color(COLOR_RADIOACTIVE_GREEN, renderer);
  for(size_t i = 0; i <= settings->MAP_SIZE; ++i)
    SDL_RenderDrawLine(renderer, xOffset + offset + i * settings->CELL_SIZE * scale, yOffset, xOffset + offset + i * settings->CELL_SIZE * scale, min * scale + yOffset);
  for(size_t i = 0; i <= settings->MAP_SIZE; ++i)
    SDL_RenderDrawLine(renderer, xOffset + offset, yOffset + i * settings->CELL_SIZE * scale, xOffset + offset + min * scale, yOffset + i * settings->CELL_SIZE * scale);
}

void render_grid(SDL_Renderer* renderer, Settings* settings)
{
  render_grid0(renderer, settings, 1, 0, 0);
}

void render_final(Game* game, SDL_Renderer* renderer, Settings* settings)
{
  size_t min = MIN(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t max = MAX(settings->WINDOW_WIDTH, settings->WINDOW_HEIGHT);
  size_t offset = (max - min) / 2;
  int xOffset = settings->WINDOW_WIDTH * 0.5;
  int yOffset = settings->WINDOW_HEIGHT * 0.25;
  render_grid0(renderer, settings, 0.5, -(offset/2), yOffset);
  render_grid0(renderer, settings, 0.5, xOffset-(offset/2), yOffset);
  render_player0(game_get_player_by_id(game, PLAYER1), renderer, settings, 0.5, -(offset/2), yOffset);
  render_player0(game_get_player_by_id(game, PLAYER2), renderer, settings, 0.5, xOffset-(offset/2), yOffset);
}
