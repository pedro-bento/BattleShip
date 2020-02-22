#!/bin/bash

gcc -Wall src/main.c src/game/ship.c src/game/game.c src/renderer/renderer.c src/app.c $(pkg-config --cflags --libs sdl2)
