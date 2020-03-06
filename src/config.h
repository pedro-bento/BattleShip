#ifndef CONFIG_H
#define CONFIG_H

// #define NDEBUG

// acording to BattleShip rules
#define MAP_LENGTH 10
#define NUM_OF_SHIPS 7

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
static const int CELL_WIDTH = SCREEN_WIDTH < SCREEN_HEIGHT ?
  (SCREEN_WIDTH / MAP_LENGTH) : (SCREEN_HEIGHT / MAP_LENGTH);

#endif // CONFIG_H
