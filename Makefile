PKGS = sdl2

CC = gcc
CFLAGS = -Wall $(shell pkg-config --cflags $(PKGS))

LIBS = $(shell pkg-config --libs $(PKGS)) -lm

FILES =\
	src/main.c\
	src/game/ship.c\
	src/game/game.c\
	src/renderer/renderer.c\
	src/app/app.c\
	src/app/init_game_state.c\
	src/app/playing_game_state.c\
	src/app/end_game_state.c\
	src/quadtree.c\
	src/system/stacktrace.c\
	src/game/player.c\

battleship: $(FILES)
	$(CC) $(CFLAGS) -o battleship $(FILES) $(LIBS)
