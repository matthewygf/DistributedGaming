# Makefile
CC = gcc
CPP = g++
F77 = f77
F9X = gfortran
LD = g++
CFLAGS =  -Wall -g 
LIBS = -lGL -lGLU -lglut -lm -lpthread


# files to be compiled
FILES = src/main.cpp src/tileMap/tileMap.cpp src/gameModel.cpp src/gameController.cpp src/gameView.cpp src/camera/camera.cpp include/stb_image.h src/bots/animal.cpp src/bots/cat.cpp src/bots/mouse.cpp include/matrix/src/Matrices.cpp  include/vbo/src/Timer.cpp src/ai/animalStates.cpp 

AUXFILES := 

# output file
OUTPUT = game

# target which compiles executable
all : $(FILES)
	$(CPP) $(AUXFILES) $(CFLAGS) $(FILES) $(LIBS) -o $(OUTPUT)

clean :
	rm -f $(OUTPUT)
