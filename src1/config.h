#ifndef CONFIG_H
#define CONFIG_H

#define MAX_SHIP_WIDTH 5

#include <SDL_ttf.h>

typedef struct
{
  int WINDOW_WIDTH;
  int WINDOW_HEIGHT;
  int CELL_SIZE;
  int MAP_SIZE;
  int NUM_OF_SHIPS;
  TTF_Font* font;
} Settings;

#endif // CONFIG_H
