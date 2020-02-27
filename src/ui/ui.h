#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "../math/vec2.h"

typedef struct
{
  SDL_Texture* text;
  SDL_Rect text_rect;
  SDL_Rect pos_rect;
  SDL_Color color;
} Button;

void button_render(const Button* button, SDL_Renderer* renderer);
int button_isClick(Button* button, Vec2 pos);

typedef struct
{
  SDL_Texture* text;
  SDL_Rect text_rect;
  SDL_Rect pos_rect;
  SDL_Color backgroud_color;
} TextBox;

void textbox_render(const TextBox* textbox, SDL_Renderer* renderer);

#endif
