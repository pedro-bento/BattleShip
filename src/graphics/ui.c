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

Text text(Vec2i pos, int width, int heigh, const char* str, TTF_Font* font, Color color, SDL_Renderer* renderer)
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
      .x = pos.x,
      .y = pos.y, 
      .w = width,
      .h = heigh
    },
  };
}

void render_text(Text* text, SDL_Renderer* renderer)
{
  int w, h;
  LOG_FAIL(!SDL_QueryTexture(text->text, NULL, NULL, &w, &h));
  SDL_Rect src = {0, 0, w, h};
  SDL_Rect dst = {text->boundary.x - (w/2), text->boundary.y - (h/2), w, h};
  LOG_FAIL(!SDL_RenderCopy(renderer, text->text, &src, &dst));
}

void delete_text(Text* text)
{
  SDL_DestroyTexture(text->text);
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

void delete_textbox(TextBox* textbox)
{
  delete_text(&textbox->title);
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

bool button_isClick(Button* button, Vec2i pos)
{
  if(button->message.background.box.x <= pos.x &&
     pos.x <= button->message.background.box.x + button->message.background.box.w &&
     button->message.background.box.y <= pos.y &&
     pos.y <= button->message.background.box.y + button->message.background.box.h)
     return true;
  return false;
}

void delete_button(Button* button)
{
  delete_textbox(&button->message);
}

NumericInputBox numeric_input_box(Vec2i pos, int width, int height, const char* str, TTF_Font* font, Color text_color, Color background_color, SDL_Renderer* renderer, int initial_value, int min_value, int max_value)
{
  char num_text[3] = {'0' + initial_value / 10, '0' + initial_value % 10, '\0'};
  return (NumericInputBox){
    .title = texbox(vec2i(pos.x, pos.y - height/1.8), width * 1.08, height, 10, str, font, text_color, background_color, renderer),
    .number = texbox(vec2i(pos.x, pos.y + height/1.8), width * 0.25, height, 5, num_text, font, text_color, background_color, renderer),
    .minus = button(vec2i(pos.x - width * 0.215, pos.y + height/1.8), width * 0.15, height, 6, "<", font, text_color, background_color, renderer),
    .minus_minus = button(vec2i(pos.x - width * 0.425, pos.y + height/1.8), width * 0.225, height, 6, "<<", font, text_color, background_color, renderer),
    .plus = button(vec2i(pos.x + width * 0.22, pos.y + height/1.8), width * 0.15, height, 6, ">", font, text_color, background_color, renderer),
    .puls_plus = button(vec2i(pos.x + width * 0.425, pos.y + height/1.8), width * 0.225, height, 6, ">>", font, text_color, background_color, renderer),
    .value = initial_value,
    .min_value = min_value,
    .max_value = max_value,
    .text_color = text_color,
    .font = font,
  };
}

void render_numeric_input_box(NumericInputBox* nip, SDL_Renderer* renderer)
{
  render_textbox(&nip->title, renderer);
  render_textbox(&nip->number, renderer);
  render_button(&nip->minus, renderer);
  render_button(&nip->minus_minus, renderer);
  render_button(&nip->plus, renderer);
  render_button(&nip->puls_plus, renderer);
}

bool update_numeric_input_box(NumericInputBox* nip, Vec2i pos, int global_max, SDL_Renderer* renderer)
{
  bool update_number = false;

  if(button_isClick(&nip->minus, pos)){
    if(nip->value - 1 >= nip->min_value){
      nip->value -= 1;
      update_number = true;
    }
  }else if(button_isClick(&nip->minus_minus, pos)){
    if(nip->value - 3 >= nip->min_value){
      nip->value -= 3;
      update_number = true;
    }
  }else if(button_isClick(&nip->plus, pos)){
    if(1 <= global_max && nip->value + 1 <= nip->max_value){
      nip->value += 1;
      update_number = true;
    }
  }else if(button_isClick(&nip->puls_plus, pos)){
    if(3 <= global_max && nip->value + 3 <= nip->max_value){
      nip->value += 3;
      update_number = true;
    }
  }

  if(update_number){
    const SDL_Color text_color = {nip->text_color.r, nip->text_color.g, nip->text_color.b};
    char num_text[3] = {'0' + nip->value / 10, '0' + nip->value % 10, '\0'};
    SDL_Surface* surface = TTF_RenderText_Blended(nip->font, num_text, text_color);
    LOG_FAIL(surface);
    SDL_DestroyTexture(nip->number.title.text);
    nip->number.title.text = SDL_CreateTextureFromSurface(renderer, surface);
    LOG_FAIL(nip->number.title.text);
    SDL_FreeSurface(surface);
  }

  return update_number;
}

void delete_numeric_input_box(NumericInputBox* nip)
{
  delete_textbox(&nip->title);
  delete_textbox(&nip->number);
  delete_button(&nip->minus);
  delete_button(&nip->minus_minus);
  delete_button(&nip->plus);
  delete_button(&nip->puls_plus);
}
