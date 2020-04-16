#include "renderer.h"
#include "../math/math.h"

void render_quadtree(SDL_Renderer* renderer, QT* qt);

SDL_Color green  = {.r = 0,   .g = 255, .b = 0};
SDL_Color red    = {.r = 255, .g = 0,   .b = 0};
SDL_Color yellow = {.r = 255, .g = 255, .b = 0};
SDL_Color purple = {.r = 255, .g = 0,   .b = 255};

void render_grid(SDL_Renderer* renderer)
{
  int min = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  for (int i = 1; i <= MAP_LENGTH; ++i)
  {
     SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, min);
     SDL_RenderDrawLine(renderer, 0, i * CELL_WIDTH, min, i * CELL_WIDTH);
  }
}

void render_rect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void render_ships(SDL_Renderer* renderer, Game* game, GamePlayer player, int isOpp)
{
  for(int x = 0; x < MAP_LENGTH; ++x)
  {
    for(int y = 0; y < MAP_LENGTH; ++y)
    {
      char state = game_player_get_map_state(game, player, vec2(y,x));
      if(state == GOOD && !isOpp)
        render_rect(renderer, (SDL_Rect){.x = x * CELL_WIDTH,
          .y = y * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH}, green);
      else if(state == HIT)
        render_rect(renderer, (SDL_Rect){.x = x * CELL_WIDTH,
          .y = y * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH}, red);
    }
  }
}

void render_game_player(SDL_Renderer* renderer, Game* game, GamePlayer player)
{
  render_grid(renderer);
  render_ships(renderer, game, player, 0);
}

void render_ship(SDL_Renderer* renderer, Ship* ship)
{
  for(int x = 0; x < MAP_LENGTH; ++x)
    for(int y = 0; y < MAP_LENGTH; ++y)
      if(ship_contains(ship, vec2(y,x)) != EMPTY)
        render_rect(renderer, (SDL_Rect){.x = x * CELL_WIDTH,
          .y = y * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH}, yellow);
}

void render_opponent(SDL_Renderer* renderer, Game* game, GamePlayer player)
{
#ifndef NDEBUG
    if(player == PLAYER1) render_quadtree(renderer, game->player1.map);
    else render_quadtree(renderer, game->player2.map);
#else
    render_grid(renderer);
#endif

  render_ships(renderer, game, player, 1);
}

void render_shot(SDL_Renderer* renderer, Vec2 shot)
{
  render_rect(renderer, (SDL_Rect){.x = shot.y * CELL_WIDTH,
    .y = shot.x * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH}, purple);
}

void render_all(SDL_Renderer* renderer, Game* game)
{
  int min = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  for (int i = 1; i <= MAP_LENGTH; ++i)
  {
     SDL_RenderDrawLine(renderer, i * CELL_WIDTH/2, 0, i * CELL_WIDTH/2, min/2);
     SDL_RenderDrawLine(renderer, 0, i * CELL_WIDTH/2, min/2, i * CELL_WIDTH/2);
   }
   SDL_RenderDrawLine(renderer, 0, MAP_LENGTH * CELL_WIDTH/2, min/2, MAP_LENGTH * CELL_WIDTH/2);

   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   for (int i = 0; i <= MAP_LENGTH; ++i)
   {
      SDL_RenderDrawLine(renderer, min/2 + i * CELL_WIDTH/2, min/2,
        min/2 + i * CELL_WIDTH/2, SCREEN_HEIGHT);
      SDL_RenderDrawLine(renderer, min/2, min/2 + i * CELL_WIDTH/2, min,
        min/2 + i * CELL_WIDTH/2);
    }

    GamePlayer player = PLAYER1;
    for(int x = 0; x < MAP_LENGTH; ++x)
    {
      for(int y = 0; y < MAP_LENGTH; ++y)
      {
        char state = game_player_get_map_state(game, player, vec2(y,x));
        if(state == GOOD){
          render_rect(renderer, (SDL_Rect){.x = x * CELL_WIDTH/2,
            .y = y * CELL_WIDTH/2, .w = CELL_WIDTH/2, .h = CELL_WIDTH/2}, green);
        }else if(state == HIT){
          render_rect(renderer, (SDL_Rect){.x = x * CELL_WIDTH/2,
            .y = y * CELL_WIDTH/2, .w = CELL_WIDTH/2, .h = CELL_WIDTH/2}, red);
        }
      }
    }

    player = PLAYER2;
    for(int x = 0; x < MAP_LENGTH; ++x)
    {
      for(int y = 0; y < MAP_LENGTH; ++y)
      {
        char state = game_player_get_map_state(game, player, vec2(y,x));
        if(state == GOOD){
          render_rect(renderer, (SDL_Rect){.x = min/2 + x * CELL_WIDTH/2,
            .y = min/2 + y * CELL_WIDTH/2, .w = CELL_WIDTH/2,
            .h = CELL_WIDTH/2}, green);
        }else if(state == HIT){
          render_rect(renderer, (SDL_Rect){.x = min/2 + x * CELL_WIDTH/2,
            .y = min/2 + y * CELL_WIDTH/2, .w = CELL_WIDTH/2,
            .h = CELL_WIDTH/2}, red);
        }
      }
    }
}

void render_square(SDL_Renderer* renderer, Vec2 top_left, Vec2 bottom_right)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  SDL_RenderDrawLine(renderer, top_left.y * CELL_WIDTH, top_left.x * CELL_WIDTH,
    top_left.y * CELL_WIDTH, bottom_right.x * CELL_WIDTH);
  SDL_RenderDrawLine(renderer, bottom_right.y * CELL_WIDTH, top_left.x * CELL_WIDTH,
    bottom_right.y * CELL_WIDTH, bottom_right.x * CELL_WIDTH);

  SDL_RenderDrawLine(renderer, top_left.y * CELL_WIDTH, top_left.x * CELL_WIDTH,
    bottom_right.y * CELL_WIDTH, top_left.x * CELL_WIDTH);
  SDL_RenderDrawLine(renderer, top_left.y * CELL_WIDTH, bottom_right.x * CELL_WIDTH,
    bottom_right.y * CELL_WIDTH, bottom_right.x * CELL_WIDTH);
}

void render_quadtree(SDL_Renderer* renderer, QT* qt)
{
  if(qt == NULL) return;
  if(qt->t_left == NULL && qt->t_right == NULL &&
     qt->b_left == NULL && qt->b_right == NULL)
     render_square(renderer, qt->top_left, qt->bottom_right);

  render_quadtree(renderer, qt->t_left);
  render_quadtree(renderer, qt->t_right);
  render_quadtree(renderer, qt->b_left);
  render_quadtree(renderer, qt->b_right);
}
