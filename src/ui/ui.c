#include "ui.h"

Button button(Vec2 pos, int width, int height, int padding, SDL_Color color, SDL_Texture* text)
{
  return (Button){
    .text = text,
    .pos_rect = (SDL_Rect){
      .x = pos.x - (width/2),
      .y = pos.y - (height/2),
      .w = width,
      .h = height,
    },
    .text_rect = (SDL_Rect){
      .x = pos.x - (width/2) + padding,
      .y = pos.y - (height/2) + padding,
      .w = width - (2*padding),
      .h = height - (2*padding),
    },
    .backgroud_color = color,
  };
}

void button_render(const Button* button, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, button->backgroud_color.r,
    button->backgroud_color.g, button->backgroud_color.b, 255);
  SDL_RenderFillRect(renderer, &button->pos_rect);
  SDL_RenderCopy(renderer, button->text, NULL, &button->text_rect);
}

int button_isClick(Button* button, Vec2 pos)
{
  if(button->pos_rect.x <= pos.x && pos.x <= button->pos_rect.x + button->pos_rect.w &&
     button->pos_rect.y <= pos.y && pos.y <= button->pos_rect.y + button->pos_rect.h)
     return 1;
  return 0;
}

TextBox textbox(Vec2 pos, int width, int height, int padding, SDL_Color color, SDL_Texture* text)
{
  return (TextBox){
    .text = text,
    .pos_rect = (SDL_Rect){
      .x = pos.x - (width/2),
      .y = pos.y - (height/2),
      .w = width,
      .h = height,
    },
    .text_rect = (SDL_Rect){
      .x = pos.x - (width/2) + padding,
      .y = pos.y - (height/2) + padding,
      .w = width - (2*padding),
      .h = height - (2*padding),
    },
    .backgroud_color = color,
  };
}

void textbox_render(const TextBox* textbox, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, textbox->backgroud_color.r,
    textbox->backgroud_color.g, textbox->backgroud_color.b, 255);
  SDL_RenderFillRect(renderer, &textbox->pos_rect);
  SDL_RenderCopy(renderer, textbox->text, NULL, &textbox->text_rect);
}
