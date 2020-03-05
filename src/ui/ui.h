#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "../math/vec2.h"

typedef struct
{
  SDL_Texture* text;
  SDL_Rect pos_rect;
  SDL_Rect text_rect;
  SDL_Color backgroud_color;
} Button;

Button button(Vec2 pos, int width, int height, int padding, SDL_Color color, SDL_Texture* text);
void button_render(const Button* button, SDL_Renderer* renderer);
int button_isClick(Button* button, Vec2 pos);

typedef struct
{
  SDL_Texture* text;
  SDL_Rect pos_rect;
  SDL_Rect text_rect;
  SDL_Color backgroud_color;
} TextBox;

TextBox textbox(Vec2 pos, int width, int height, int padding, SDL_Color color, SDL_Texture* text);
void textbox_render(const TextBox* textbox, SDL_Renderer* renderer);

#endif
