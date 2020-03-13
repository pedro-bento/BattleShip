#include "ui.h"
#include "../math/math.h"

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

Slider slider(Vec2 pos, int width, int height, int max_value)
{
  return (Slider){
    .drag = 0,
    .value = 0,
    .max_value = max_value,
    .pos_rect = (SDL_Rect){
      .x = pos.x - (width/2),
      .y = pos.y - (height/2),
      .w = width,
      .h = height,
    },
  };
}

void slider_render(const Slider* slider, SDL_Renderer* renderer)
{
  // draw static rect
  const SDL_Color static_rect_color = {.r = 130, .g = 130, .b = 130};
  const float static_rect_height = slider->pos_rect.h * 0.25f;
  const SDL_Rect static_rect = {
    .x = slider->pos_rect.x,
    .y = slider->pos_rect.y - static_rect_height * 0.5f,
    .w = slider->pos_rect.w,
    .h = static_rect_height,
  };

  SDL_SetRenderDrawColor(renderer, static_rect_color.r, static_rect_color.g, static_rect_color.b, 255);
  SDL_RenderFillRect(renderer, &static_rect);

  // draw movable_rect
  const SDL_Color movable_rect_color = {.r = 70, .g = 70, .b = 70};
  const float movable_rect_ratio = slider->value / slider->max_value;
  const int movable_rect_width = slider->pos_rect.w * 0.1f;
  const SDL_Rect movable_rect = {
    .x = slider->pos_rect.x + movable_rect_ratio * (slider->pos_rect.w - movable_rect_width),
    .y = slider->pos_rect.y - slider->pos_rect.h * 0.5f,
    .w = movable_rect_width,
    .h = slider->pos_rect.h,
  };

  SDL_SetRenderDrawColor(renderer, movable_rect_color.r, movable_rect_color.g, movable_rect_color.b, 255);
  SDL_RenderFillRect(renderer, &movable_rect);
}

void slider_drag(Slider* slider, SDL_Event* event)
{
  if(!slider->drag){
    if(event->type == SDL_MOUSEBUTTONDOWN){
      Vec2 pos = vec2(event->button.x, event->button.y);
      if(slider->pos_rect.x <= pos.x && pos.x <= slider->pos_rect.x + slider->pos_rect.w &&
          slider->pos_rect.y <= pos.y && pos.y <= slider->pos_rect.y + slider->pos_rect.h){
          slider->drag = 1;
      }
    }
   }else{
     switch(event->type){
       case SDL_MOUSEBUTTONUP: {
           slider->drag = 0;
       } break;

       case SDL_MOUSEMOTION: {
           const float x = MIN(MAX(event->button.x - slider->pos_rect.x, 0.0f), slider->pos_rect.w);
           const float ratio = x / (float) slider->pos_rect.w;
           slider->value = ratio * slider->max_value;
       } break;
     }
  }
}
