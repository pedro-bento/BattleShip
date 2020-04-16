#include "ui.h"
#include "../system/log.h"

static inline void set_render_color(Color color, SDL_Renderer* renderer)
{
  LOG_FAIL(!SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a));
}

Box box(Vec2i pos, int width, int heigh, Color color)
{
  return (Box)
  {
    .box = (SDL_Rect)
    {
      .x = pos.x - width/2,
      .y = pos.y - heigh/2,
      .w = width,
      .h = heigh
    },

    .color = color,
  };
}

void render_box(Box* box, SDL_Renderer* renderer)
{
  set_render_color(box->color, renderer);
  LOG_FAIL(!SDL_RenderFillRect(renderer, &box->box));
}

Text text(Vec2i pos, int width, int heigh,
  const char* str, TTF_Font* font, Color color, SDL_Renderer* renderer)
{
  SDL_Color text_color = (SDL_Color) {.r = color.r, .g = color.g, .b = color.b };
  SDL_Surface *surface = TTF_RenderText_Blended(font, str, text_color);
  LOG_FAIL(surface);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  LOG_FAIL(texture);
  SDL_FreeSurface(surface);

  return (Text)
  {
    .text = texture,
    .boundary = (SDL_Rect)
    {
      .x = pos.x - width/2,
      .y = pos.y - heigh/2,
      .w = width,
      .h = heigh
    },
  };
}

void render_text(Text* text, SDL_Renderer* renderer)
{
  LOG_FAIL(!SDL_RenderCopy(renderer, text->text, NULL, &text->boundary));
}

TextBox texbox(Vec2i pos, int width, int heigh, int padding, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer)
{
  return (TextBox)
  {
    .background = box(pos, width, heigh, background_color),
    .title = text(pos, width - padding, heigh - padding, str, font, text_color, renderer),
  };
}

void render_textbox(TextBox* tb, SDL_Renderer* renderer)
{
  render_box(&tb->background, renderer);
  render_text(&tb->title, renderer);
}

Button button(Vec2i pos, int width, int heigh, int padding, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer)
{
  return (Button)
  {
    .message = texbox(pos, width, heigh, padding, str, font, text_color, background_color, renderer),
  };
}

void render_button(Button* button, SDL_Renderer* renderer)
{
  render_textbox(&button->message, renderer);
}
