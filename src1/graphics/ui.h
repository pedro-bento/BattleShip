#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "color.h"
#include "../math/vec.h"

typedef struct
{
  SDL_Rect box;
  Color color;
} Box;

Box box(Vec2i pos, int width, int heigh, Color color);
void render_box(Box* box, SDL_Renderer* renderer);

typedef struct
{
  SDL_Texture* text;
  SDL_Rect boundary;
} Text;

Text text(Vec2i pos, int width, int heigh,
  const char* str, TTF_Font* font, Color color, SDL_Renderer* renderer);
void render_text(Text* text, SDL_Renderer* renderer);

typedef struct
{
  Box background;
  Text title;
} TextBox;

TextBox texbox(Vec2i pos, int width, int heigh, int padding, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer);
void render_textbox(TextBox* textbox, SDL_Renderer* renderer);

typedef struct
{
  TextBox message;
} Button;

Button button(Vec2i pos, int width, int heigh, int padding, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer);
void render_button(Button* button, SDL_Renderer* renderer);
bool button_isClick(Button* button, Vec2i pos);

typedef struct
{
  TextBox title;
  TextBox number;
  Button minus;
  Button minus_minus;
  Button plus;
  Button puls_plus;
  int value;
  int min_value;
  int max_value;
} NumericInputBox;

NumericInputBox numeric_input_box(Vec2i pos, int width, int height, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer, int min_value, int max_value);

void render_numeric_input_box(NumericInputBox* nip, SDL_Renderer* renderer);

#endif
