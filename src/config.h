#ifndef CONFIG_H
#define CONFIG_H

#include "game/ship.h"

typedef struct
{
  int length;
  ShipType type;
} ShipTemplate;

#define MAX_NUM_OF_SHIPS 8

extern int MAP_LENGTH;
extern int NUM_OF_SHIPS;
extern ShipTemplate ship_templates[MAX_NUM_OF_SHIPS];

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
extern int CELL_WIDTH;

void config_classic();
void config_tetris();

#endif // CONFIG_H
