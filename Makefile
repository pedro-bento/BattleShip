PKGS = sdl2 SDL2_ttf

CC = gcc
CFLAGS = -std=c99 -Wall $(shell pkg-config --cflags $(PKGS))

LIBS = $(shell pkg-config --libs $(PKGS)) -lm

FILES =\
	src/main.c\
	src/game/ship.c\
	src/game/game.c\
	src/renderer/renderer.c\
	src/app/app.c\
	src/app/begin_state.c\
	src/app/init_state.c\
	src/app/playing_state.c\
	src/app/end_state.c\
	src/quadtree.c\
	src/system/stacktrace.c\
	src/game/player.c\
	src/ui/ui.c\
	src/game/ship_line.c\
	src/config.c\

battleship: $(FILES)
	$(CC) $(CFLAGS) -o battleship $(FILES) $(LIBS)
