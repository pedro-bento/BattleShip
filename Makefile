PKGS = sdl2 SDL2_ttf
CC = gcc
CFLAGS = -std=c99 -Wall $(shell pkg-config --cflags $(PKGS))
LIBS = $(shell pkg-config --libs $(PKGS))

FILES =\
	src1/main.c\
	src1/system/log.c\
	src1/math/vec.c\
	src1/physics/ship.c\
	src1/physics/player.c\
	src1/physics/game.c\
	src1/graphics/color.c\
	src1/graphics/renderer.c\
	src1/graphics/ui.c\
	src1/states/first.c\
	src1/states/placing_ships.c\
	src1/states/configure_game.c\
	src1/states/fight.c\
	src1/states/results.c\

battleship: $(FILES)
	$(CC) $(CFLAGS) -o battleship $(FILES) $(LIBS)
