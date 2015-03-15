# Makefile
CC = gcc
CPP = g++
F77 = f77
F9X = gfortran
LD = g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglut -lm -lpthread




# files to be compiled
FILES = src/main.cpp src/tileMap/tileMap.cpp src/gameModel.cpp src/gameController.cpp src/gameView.cpp src/camera/camera.cpp supports/stb_image.h src/rawModel/rawModel.cpp src/rawModel/loader.cpp 
AUXFILES := 
# output file
OUTPUT = game

# target which compiles executable
all : $(FILES)
	$(CPP) $(AUXFILES) $(CFLAGS) $(FILES) $(LIBS) -o $(OUTPUT)

clean :
	rm -f $(OUTPUT)
