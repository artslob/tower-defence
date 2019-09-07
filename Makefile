OBJS = bg.c  game.c  init.c  main.c  startscreen.c  tower.c  wave.c

# compiler
CC = gcc

# -w suppresses all warnings
COMPILER_FLAGS = -Werror=implicit-function-declaration -Wno-int-conversion -Wno-format -Wno-incompatible-pointer-types

# specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

# the name of the exectuable
OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
