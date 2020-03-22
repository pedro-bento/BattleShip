#ifndef CONFIG_H
#define CONFIG_H

#define CELL_SIZE 15 // should be inside a Game_Settings struct
#define MAX_MAP_SIZE 40
#define MAX_NUMBER_OF_SHIPS ((MAX_MAP_SIZE * MAX_MAP_SIZE) / (MAX_SHIP_WIDTH * MAX_SHIP_WIDTH))

#define MAX_SHIP_WIDTH 5

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#endif // CONFIG_H
