#include "config.h"

int MAP_LENGTH;
int NUM_OF_SHIPS;
int CELL_WIDTH;

void config_classic()
{
  MAP_LENGTH = 10;
  NUM_OF_SHIPS = 5;
  CELL_WIDTH = SCREEN_WIDTH < SCREEN_HEIGHT ?
    (SCREEN_WIDTH / MAP_LENGTH) :
    (SCREEN_HEIGHT / MAP_LENGTH);
}

void config_tetris()
{
  // NES tetris area is 200 (20x10) here we're using ceil(srqt(200)) = 15
  // so that map is square and it's length is divisible by SCREEN_HEIGHT = 600 
  MAP_LENGTH = 15;
  NUM_OF_SHIPS = 7;
  CELL_WIDTH = SCREEN_WIDTH < SCREEN_HEIGHT ?
    (SCREEN_WIDTH / MAP_LENGTH) :
    (SCREEN_HEIGHT / MAP_LENGTH);
}
