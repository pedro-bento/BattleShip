#!/bin/bash

gcc -Wall src/main.c src/game/ship.c src/game/game.c src/renderer/renderer.c src/app/app.c src/app/init_game_state.c src/app/playing_game_state.c src/app/end_game_state.c src/quadtree.c src/stacktrace.c $(pkg-config --cflags --libs sdl2)
