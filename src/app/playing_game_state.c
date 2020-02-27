#include "playing_game_state.h"
#include "../math/vec2.h"
#include "../renderer/renderer.h"
#include "../ui/ui.h"

// handles inputs & returns new position of shot
Vec2 playing_handle_events(Game* game, GamePlayer* player, SDL_Keycode key, Vec2 shot);

Vec2 move_shot(Vec2 vec, Vec2 dxy);

void playing_game_state(Game* game, SDL_Renderer* renderer, int* shouldQuit)
{
  Vec2 shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);
  GamePlayer player = PLAYER1;

  TTF_Font* ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
  SDL_Color text_color = {255, 255, 255};

  SDL_Surface* surface_player1 = TTF_RenderText_Solid(ubuntu_mono, "Shoot player 1!", text_color);
  SDL_Texture* player1_message = SDL_CreateTextureFromSurface(renderer, surface_player1);

  SDL_Surface* surface_player2 = TTF_RenderText_Solid(ubuntu_mono, "Shoot player 2!", text_color);
  SDL_Texture* player2_message = SDL_CreateTextureFromSurface(renderer, surface_player2);

  TextBox player1_text = {.text = player1_message,
    .pos_rect = { .x = SCREEN_WIDTH/2-200, .y = SCREEN_HEIGHT+FOOTER_HEIGHT-60, .w = 400, .h = 60},
    .text_rect = { .x = SCREEN_WIDTH/2-190, .y = SCREEN_HEIGHT+FOOTER_HEIGHT-50, .w = 380, .h = 40},
    .backgroud_color = {0, 0, 0}};

  TextBox player2_text = {.text = player2_message,
    .pos_rect = { .x = SCREEN_WIDTH/2-200, .y = SCREEN_HEIGHT+FOOTER_HEIGHT-60, .w = 400, .h = 60},
    .text_rect = { .x = SCREEN_WIDTH/2-190, .y = SCREEN_HEIGHT+FOOTER_HEIGHT-50, .w = 380, .h = 40},
    .backgroud_color = {0, 0, 0}};

  SDL_Event e;
  while(game->state == PLAYING && !*shouldQuit)
  {
    while(SDL_PollEvent(&e))
    {
      if(e.type == SDL_KEYDOWN)
        shot = playing_handle_events(game, &player, e.key.keysym.sym, shot);
      else if(e.type == SDL_QUIT)
        *shouldQuit = 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    render_opponent(renderer, game, player == PLAYER1 ? PLAYER2 : PLAYER1);
    render_shot(renderer, shot);
    if(player == PLAYER1) textbox_render(&player1_text, renderer);
    else textbox_render(&player2_text, renderer);
    SDL_RenderPresent(renderer);
  }
}

Vec2 playing_handle_events(Game* game, GamePlayer* player, SDL_Keycode key, Vec2 shot)
{
  switch(key)
  {
    case SDLK_w: case SDLK_UP: {
      shot = move_shot(shot, vec2(-1,0));
    } break;

    case SDLK_a: case SDLK_LEFT: {
      shot = move_shot(shot, vec2(0,-1));
    } break;

    case SDLK_s: case SDLK_DOWN: {
      shot = move_shot(shot, vec2(1,0));
    } break;

    case SDLK_d: case SDLK_RIGHT: {
      shot = move_shot(shot, vec2(0,1));
    } break;

    case SDLK_RETURN: {
      game_player_shoot(game, *player, shot);
      shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);
      *player = *player == PLAYER1 ? PLAYER2 : PLAYER1;
    } break;
  }
  return shot;
}

Vec2 move_shot(Vec2 vec, Vec2 dxy)
{
  Vec2 prev = vec;
  vec = add(vec, dxy);

  if(vec.x < 0 || vec.x >= MAP_LENGTH || vec.y < 0 || vec.y >= MAP_LENGTH)
     return prev;
  return vec;
}
