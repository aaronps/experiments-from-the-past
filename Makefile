all: old-puzzle

old-puzzle: old-puzzle.c
	$(CC) `sdl-config --libs --cflags` -o old-puzzle old-puzzle.c

