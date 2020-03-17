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

typedef struct
{
  int drag;
  float value;
  float max_value;
  SDL_Rect pos_rect;
} Slider;

Slider slider(Vec2 pos, int width, int height, int max_value);
void slider_render(const Slider* slider, SDL_Renderer* renderer);
void slider_drag(Slider* slider, SDL_Event* e);

typedef struct
{
  Slider sld;
  TextBox num;
  TextBox text;
} SliderField;

SliderField sliderfield(Vec2 pos, int width, int height, int max_value, const char* str, SDL_Renderer* renderer);
void sliderfield_render(SliderField* slider, SDL_Renderer* renderer);
void sliderfield_drag(SliderField* slider, SDL_Event* e);

#endif
