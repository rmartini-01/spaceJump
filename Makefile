CC = gcc 
CFLAGS = -W -Wall -g -std=c99 -g `sdl2-config --cflags `
LIBS = `sdl2-config --libs` -lSDL2_ttf -lm

INCLUDES = -I./SDL2_ttf -I./SDL2_image -I./SDL_ttf
EXEC = Game

SRC = Game.c Player.c Platforms.c Textures.c Sdl2-light.c World.c

OBJ = $(SRC:%.c=%.o)

all : $(EXEC)

Game: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $@ $(LIBS) 
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean: 
	rm -rf *.o *- $(EXEC) 

mrproper: clean
	rm -rf $(EXEC) 
