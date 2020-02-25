#include "renderer.h"

typedef struct
{
  int r;
  int b;
  int g;
} Color;

Color ship_good = {.r = 0, .g = 255, .b = 0};
Color ship_hit = {.r = 255, .g = 0, .b = 0};
Color ship_preview = {.r = 255, .g = 255, .b = 0};
Color color_shot = {.r = 255, .g = 0, .b = 255};

void render_grid(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  for (int i = 1; i < MAP_LENGTH; ++i)
  {
     SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_WIDTH);
     SDL_RenderDrawLine(renderer, 0, i * CELL_WIDTH, SCREEN_WIDTH, i * CELL_WIDTH);
   }
   SDL_RenderDrawLine(renderer, 0, MAP_LENGTH * CELL_WIDTH, SCREEN_WIDTH, MAP_LENGTH * CELL_WIDTH);
}

void render_ships(SDL_Renderer* renderer, Game* game, int isOpponent)
{
  Player player = isOpponent == 0 ? game->current_player :
    game->current_player == PLAYER1 ? PLAYER2 : PLAYER1;
  for(int x = 0; x < MAP_LENGTH; ++x)
  {
    for(int y = 0; y < MAP_LENGTH; ++y)
    {
      char state = game_player_get_cell(game, player, vec2(y,x));
      if(state == STATE_GOOD && !isOpponent){
        SDL_SetRenderDrawColor(renderer, ship_good.r, ship_good.g, ship_good.b, 255);
        SDL_Rect rect = { .x = x * CELL_WIDTH, .y = y * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH};
        SDL_RenderFillRect(renderer, &rect);
      }else if(state == STATE_HIT){
        SDL_SetRenderDrawColor(renderer, ship_hit.r, ship_hit.g, ship_hit.b, 255);
        SDL_Rect rect = { .x = x * CELL_WIDTH, .y = y * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH};
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }
}

void render_current_player(SDL_Renderer* renderer, Game* game)
{
  render_grid(renderer);
  render_ships(renderer, game, 0);
}

void render_ship(SDL_Renderer* renderer, Ship* ship)
{
  for(int x = 0; x < MAP_LENGTH; ++x)
    for(int y = 0; y < MAP_LENGTH; ++y)
      if(ship_contains(ship, vec2(y,x)) != '\0')
      {
        SDL_SetRenderDrawColor(renderer, ship_preview.r, ship_preview.g, ship_preview.b, 255);
        SDL_Rect rect = { .x = x * CELL_WIDTH, .y = y * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH};
        SDL_RenderFillRect(renderer, &rect);
      }
}

void render_opponent(SDL_Renderer* renderer, Game* game)
{
  render_grid(renderer);
  render_ships(renderer, game, 1);
}

void render_shot(SDL_Renderer* renderer, Vec2 shot)
{
  SDL_SetRenderDrawColor(renderer, color_shot.r, color_shot.g, color_shot.b, 255);
  SDL_Rect rect = { .x = shot.y * CELL_WIDTH, .y = shot.x * CELL_WIDTH,
    .w = CELL_WIDTH, .h = CELL_WIDTH};
  SDL_RenderFillRect(renderer, &rect);
}

void render_all(SDL_Renderer* renderer, Game* game)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  for (int i = 1; i <= MAP_LENGTH; ++i)
  {
     SDL_RenderDrawLine(renderer, i * CELL_WIDTH/2, 0, i * CELL_WIDTH/2, SCREEN_WIDTH/2);
     SDL_RenderDrawLine(renderer, 0, i * CELL_WIDTH/2, SCREEN_WIDTH/2, i * CELL_WIDTH/2);
   }
   SDL_RenderDrawLine(renderer, 0, MAP_LENGTH * CELL_WIDTH/2, SCREEN_WIDTH/2, MAP_LENGTH * CELL_WIDTH/2);

   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   for (int i = 0; i < MAP_LENGTH; ++i)
   {
      SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2 + i * CELL_WIDTH/2, SCREEN_WIDTH/2,
        SCREEN_WIDTH/2 + i * CELL_WIDTH/2, SCREEN_WIDTH);
      SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, SCREEN_WIDTH/2 + i * CELL_WIDTH/2,
        SCREEN_WIDTH, SCREEN_WIDTH/2 + i * CELL_WIDTH/2);
    }
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, SCREEN_WIDTH/2 + MAP_LENGTH * CELL_WIDTH/2,
      SCREEN_WIDTH, SCREEN_WIDTH/2 + MAP_LENGTH * CELL_WIDTH/2);

    Player player = PLAYER1;
    for(int x = 0; x < MAP_LENGTH; ++x)
    {
      for(int y = 0; y < MAP_LENGTH; ++y)
      {
        char state = game_player_get_cell(game, player, vec2(y,x));
        if(state == STATE_GOOD){
          SDL_SetRenderDrawColor(renderer, ship_good.r, ship_good.g, ship_good.b, 255);
          SDL_Rect rect = { .x = x * CELL_WIDTH/2, .y = y * CELL_WIDTH/2, .w = CELL_WIDTH/2, .h = CELL_WIDTH/2};
          SDL_RenderFillRect(renderer, &rect);
        }else if(state == STATE_HIT){
          SDL_SetRenderDrawColor(renderer, ship_hit.r, ship_hit.g, ship_hit.b, 255);
          SDL_Rect rect = { .x = x * CELL_WIDTH/2, .y = y * CELL_WIDTH/2, .w = CELL_WIDTH/2, .h = CELL_WIDTH/2};
          SDL_RenderFillRect(renderer, &rect);
        }
      }
    }

    player = PLAYER2;
    for(int x = 0; x < MAP_LENGTH; ++x)
    {
      for(int y = 0; y < MAP_LENGTH; ++y)
      {
        char state = game_player_get_cell(game, player, vec2(y,x));
        if(state == STATE_GOOD){
          SDL_SetRenderDrawColor(renderer, ship_good.r, ship_good.g, ship_good.b, 255);
          SDL_Rect rect = { .x = x * CELL_WIDTH/2 + SCREEN_WIDTH/2, .y = y * CELL_WIDTH/2 + SCREEN_WIDTH/2, .w = CELL_WIDTH/2, .h = CELL_WIDTH/2};
          SDL_RenderFillRect(renderer, &rect);
        }else if(state == STATE_HIT){
          SDL_SetRenderDrawColor(renderer, ship_hit.r, ship_hit.g, ship_hit.b, 255);
          SDL_Rect rect = { .x = x * CELL_WIDTH/2 + SCREEN_WIDTH/2, .y = y * CELL_WIDTH/2 + SCREEN_WIDTH/2, .w = CELL_WIDTH/2, .h = CELL_WIDTH/2};
          SDL_RenderFillRect(renderer, &rect);
        }
      }
    }
}

void render_square(SDL_Renderer* renderer, Vec2 top_left, Vec2 bottom_right)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  SDL_RenderDrawLine(renderer, top_left.x * CELL_WIDTH, top_left.y * CELL_WIDTH,
    top_left.x * CELL_WIDTH, bottom_right.y * CELL_WIDTH);
  SDL_RenderDrawLine(renderer, bottom_right.x * CELL_WIDTH, top_left.y * CELL_WIDTH,
    bottom_right.x * CELL_WIDTH, bottom_right.y * CELL_WIDTH);

  SDL_RenderDrawLine(renderer, top_left.x * CELL_WIDTH, top_left.y * CELL_WIDTH,
    bottom_right.x * CELL_WIDTH, top_left.y * CELL_WIDTH);
  SDL_RenderDrawLine(renderer, top_left.x * CELL_WIDTH, bottom_right.y * CELL_WIDTH,
    bottom_right.x * CELL_WIDTH, bottom_right.y * CELL_WIDTH);
}

void render_quadtree(SDL_Renderer* renderer, QT* qt)
{
  if(qt == NULL) return;

  render_square(renderer, qt->top_left, qt->bottom_right);

  render_quadtree(renderer, qt->t_left);
  render_quadtree(renderer, qt->t_right);
  render_quadtree(renderer, qt->b_left);
  render_quadtree(renderer, qt->b_right);
}
