#include "config.h"

int MAP_LENGTH;
int NUM_OF_SHIPS;
ShipTemplate ship_templates[MAX_NUM_OF_SHIPS];
int CELL_WIDTH;
TTF_Font* ubuntu_mono;

void config_init()
{
  ubuntu_mono = TTF_OpenFont("res/UbuntuMono-R.ttf", 64);
}

void config_classic()
{
  MAP_LENGTH = 10;
  NUM_OF_SHIPS = 5;
  CELL_WIDTH = SCREEN_WIDTH < SCREEN_HEIGHT ? (SCREEN_WIDTH / MAP_LENGTH) : (SCREEN_HEIGHT / MAP_LENGTH);

  const int length[5] = {5, 4, 3, 3, 2};
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
  {
    ship_templates[i].length = length[i];
    ship_templates[i].type = I;
  }
}

void config_tetris()
{
  // NES tetris area is 200 (20x10) here we're using ceil(srqt(200)) = 15
  // so that map is square and it's length is divisible by SCREEN_HEIGHT = 600
  MAP_LENGTH = 15;
  NUM_OF_SHIPS = 7;
  CELL_WIDTH = SCREEN_WIDTH < SCREEN_HEIGHT ? (SCREEN_WIDTH / MAP_LENGTH) : (SCREEN_HEIGHT / MAP_LENGTH);

  const ShipType type[7] = {I, J, L, O, S, T, Z};
  for(size_t i = 0; i < NUM_OF_SHIPS; i++)
  {
    ship_templates[i].length = 0;
    ship_templates[i].type = type[i];
  }
}
