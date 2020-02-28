#include "ui.h"

void button_render(const Button* button, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, 255);
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

void textbox_render(const TextBox* textbox, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, textbox->backgroud_color.r, textbox->backgroud_color.g, textbox->backgroud_color.b, 255);
  SDL_RenderFillRect(renderer, &textbox->pos_rect);
  SDL_RenderCopy(renderer, textbox->text, NULL, &textbox->text_rect);
}
