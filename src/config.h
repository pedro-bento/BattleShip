#ifndef CONFIG_H
#define CONFIG_H

#include "game/ship.h"

// #define NDEBUG

extern int MAP_LENGTH;
extern int NUM_OF_SHIPS;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

extern int CELL_WIDTH;

// classic BattleShip
static const short ship_length[5] = {5, 4, 3, 2, 2};
// tetris BattleShip
static const ShipType ship_type[7] = {I, J, L, O, S, T, Z};

void config_classic();
void config_tetris();

#endif // CONFIG_H
