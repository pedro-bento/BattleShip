#ifndef CONFIG_H
#define CONFIG_H

#define MAX_SHIP_WIDTH 5
#define MAX_MAP_SIZE 40
#define MIN_MAP_SIZE 20

#include <SDL_ttf.h>
#include "physics/ship.h"

typedef struct
{
  int WINDOW_WIDTH;
  int WINDOW_HEIGHT;
  int CELL_SIZE;
  int MAP_SIZE;
  int NUM_OF_SHIPS;
  int ships[(MAX_MAP_SIZE * MAX_MAP_SIZE) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH)];
  TTF_Font* font;
} Settings;

#endif // CONFIG_H
