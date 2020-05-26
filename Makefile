PKGS = sdl2 SDL2_ttf
CC = gcc
CFLAGS = -std=c99 -Wall -O2 $(shell pkg-config --cflags $(PKGS))
LIBS = -lm $(shell pkg-config --libs $(PKGS))

FILES =\
	src/system/log.c\
	src/system/quadtree.c\
	src/physics/ship.c\
	src/physics/player.c\
	src/physics/game.c\
	src/graphics/color.c\
	src/graphics/renderer.c\
	src/graphics/ui.c\
	src/states/first.c\
	src/states/placing_ships.c\
	src/states/configure_game.c\
	src/states/fight.c\
	src/states/results.c\

battleship: $(FILES)
	$(CC) $(CFLAGS) -o battleship src/main.c $(FILES) $(LIBS)

battleship_a: $(FILES)
	$(CC) $(CFLAGS) -o battleship_a src/maina.c $(FILES) $(LIBS)
