#include "playing_state.h"
#include "../math/vec2.h"
#include "../renderer/renderer.h"
#include "../ui/ui.h"
#include "../system/stacktrace.h"
#include "end_state.h"

// handles inputs & returns new position of shot
Vec2 playing_handle_events(Game* game, GamePlayer* player, SDL_Keycode key, Vec2 shot);
Vec2 move_shot(Vec2 vec, Vec2 dxy);

typedef struct
{
  Game* game;
  TextBox text1;
  TextBox text2;
  GamePlayer current_player;
  Vec2 shot;
} PlayingData;

void playing_render(State* s, SDL_Renderer* renderer);
void playing_handle_event(State* s, SDL_Event* e);
State* playing_update(State* s, SDL_Renderer* renderer);

State* playing_state_create(Game* game, SDL_Renderer* renderer)
{
  State* playing = malloc(sizeof(State));
  trace_assert(playing);
  PlayingData* data = malloc(sizeof(PlayingData));
  trace_assert(data);

  data->game = game;

  TTF_Font* ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
  SDL_Color text_color = {255, 255, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(ubuntu_mono, "Shoot player 1!", text_color);
  SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);

  data->text1 = textbox(vec2(SCREEN_WIDTH * 0.875, SCREEN_HEIGHT * 0.085),
    180, 60, 10, (SDL_Color){.r = 0, .g = 0, .b = 0}, message);

  SDL_Surface* surface2 = TTF_RenderText_Solid(ubuntu_mono, "Shoot player 2!", text_color);
  SDL_Texture* message2 = SDL_CreateTextureFromSurface(renderer, surface2);

  data->text2 = textbox(vec2(SCREEN_WIDTH * 0.875, SCREEN_HEIGHT * 0.085),
    180, 60, 10, (SDL_Color){.r = 0, .g = 0, .b = 0}, message2);

  data->current_player = PLAYER1;

  data->shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);

  playing->data = (void*)data;
  playing->render = &playing_render;
  playing->handle_event = &playing_handle_event;
  playing->update = &playing_update;

  return playing;
}

void playing_state_destroy(State* state)
{
  free(state->data);
  free(state);
}

void playing_render(State* s, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  render_opponent(renderer, ((PlayingData*)s->data)->game,
    ((PlayingData*)s->data)->current_player == PLAYER1 ? PLAYER2 : PLAYER1);
  render_shot(renderer, ((PlayingData*)s->data)->shot);
  if(((PlayingData*)s->data)->current_player == PLAYER1)
    textbox_render(&((PlayingData*)s->data)->text1, renderer);
  else
    textbox_render(&((PlayingData*)s->data)->text2, renderer);
  SDL_RenderPresent(renderer);
}

void playing_handle_event(State* s, SDL_Event* e)
{
  if(e->type == SDL_KEYDOWN)
  {
    switch(e->key.keysym.sym)
    {
      case SDLK_w: case SDLK_UP: {
        ((PlayingData*)s->data)->shot =
          move_shot(((PlayingData*)s->data)->shot, vec2(-1,0));
      } break;

      case SDLK_a: case SDLK_LEFT: {
        ((PlayingData*)s->data)->shot =
          move_shot(((PlayingData*)s->data)->shot, vec2(0,-1));
      } break;

      case SDLK_s: case SDLK_DOWN: {
        ((PlayingData*)s->data)->shot =
          move_shot(((PlayingData*)s->data)->shot, vec2(1,0));
      } break;

      case SDLK_d: case SDLK_RIGHT: {
        ((PlayingData*)s->data)->shot =
          move_shot(((PlayingData*)s->data)->shot, vec2(0,1));
      } break;

      case SDLK_RETURN: {
        game_player_shoot(((PlayingData*)s->data)->game,
          ((PlayingData*)s->data)->current_player, ((PlayingData*)s->data)->shot);

        ((PlayingData*)s->data)->shot = vec2(MAP_LENGTH/2,MAP_LENGTH/2);

        ((PlayingData*)s->data)->current_player =
          ((PlayingData*)s->data)->current_player == PLAYER1 ? PLAYER2 : PLAYER1;
      } break;
    }
  }
}

State* playing_update(State* s, SDL_Renderer* renderer)
{
  (void)renderer;

  if(((PlayingData*)s->data)->game->state == PLAYING)
    return s;

  Game* game =  ((PlayingData*)s->data)->game;
  playing_state_destroy(s);
  return end_state_create(game);
}

Vec2 move_shot(Vec2 vec, Vec2 dxy)
{
  Vec2 prev = vec;
  vec = add(vec, dxy);

  if(vec.x < 0 || vec.x >= MAP_LENGTH || vec.y < 0 || vec.y >= MAP_LENGTH)
     return prev;
  return vec;
}
