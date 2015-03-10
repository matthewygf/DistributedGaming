# Makefile
CC = g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglut -lm -lpthread

# files to be compiled
FILES = src/main.cpp src/tileMap.cpp src/gameModel.cpp src/gameController.cpp src/gameView.cpp src/camera.cpp supports/stb_image.h
AUXFILES := 
# output file
OUTPUT = game

# target which compiles executable
all : $(FILES)
	$(CC) $(AUXFILES) $(CFLAGS) $(FILES) $(LIBS) -o $(OUTPUT)

clean :
	rm -f $(OUTPUT)
