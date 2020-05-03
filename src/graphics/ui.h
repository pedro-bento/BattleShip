#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "color.h"
#include "../math/vec.h"

// Box
// structure that represents a colored box
typedef struct
{
  SDL_Rect box;
  Color color;
} Box;

// box
// returns an initialized Box
Box box(Vec2i pos, int width, int heigh, Color color);

// render_box
// renders the colored box on the screen
void render_box(Box* box, SDL_Renderer* renderer);

// Text
// structure that represents text
typedef struct
{
  SDL_Texture* text;
  SDL_Rect boundary;
} Text;

// text
// returns an initialized Text
Text text(Vec2i pos, int width, int heigh, const char* str, TTF_Font* font, Color color, SDL_Renderer* renderer);

// render_text
// renders the text on the screen
void render_text(Text* text, SDL_Renderer* renderer);

// delete_text
// frees the SDL texture
void delete_text(Text* text);

// TextBox
// structure that represents text with a background
typedef struct
{
  Box background;
  Text title;
} TextBox;

// textbox
// returns an initialized TextBox
TextBox texbox(Vec2i pos, int width, int heigh, int padding, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer);

// render_textbox
// renders the textbox on the screen
void render_textbox(TextBox* textbox, SDL_Renderer* renderer);

// delete_textbox
// frees the SDL texture
void delete_textbox(TextBox* textbox);

// Button
// structure that represents a button
typedef struct
{
  TextBox message;
} Button;

// button
// returns an initialized Button
Button button(Vec2i pos, int width, int heigh, int padding, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer);

// render_button
// renders the button on the screen
void render_button(Button* button, SDL_Renderer* renderer);

// button_isClick
// returns true if the point 'pos' is inside the button boundary
bool button_isClick(Button* button, Vec2i pos);

// delete_button
// frees the SDL texture
void delete_button(Button* button);

// NumericInputBox
// structure that represents a input box
// contains a title, a value and buttons to interact and change that value
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
  Color text_color;
  TTF_Font* font;
} NumericInputBox;

// numeric_input_box
// returns an initialized NumericInputBox
NumericInputBox numeric_input_box(Vec2i pos, int width, int height, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer, int initial_value, int min_value, int max_value);

// render_numeric_input_box
// renders the numeric_input_box on the screen
void render_numeric_input_box(NumericInputBox* nip, SDL_Renderer* renderer);

// update_numeric_input_box
// updates the value given a 'pos' and a 'global_max'
// returns true if update was accomplished
bool update_numeric_input_box(NumericInputBox* nip, Vec2i pos, int global_max, SDL_Renderer* renderer);

// delete_numeric_input_box
// frees all the SDL textures
void delete_numeric_input_box(NumericInputBox* nip);

#endif
