# Makefile
CC = g++
CFLAGS = -Wall
<<<<<<< HEAD
LIBS = -lGL -lGLU -lglut -lGLEW -lm -lpthread
=======
LIBS = -lGL -lGLU -lglut -lm -lpthread
>>>>>>> 9852c9abd3ab8a9c8887e383d54efba095de248a

# files to be compiled
FILES = src/main.cpp src/tileMap/tileMap.cpp src/gameModel.cpp src/gameController.cpp src/gameView.cpp src/camera/camera.cpp supports/stb_image.h  
AUXFILES := 
# output file
OUTPUT = game

# target which compiles executable
all : $(FILES)
	$(CC) $(AUXFILES) $(CFLAGS) $(FILES) $(LIBS) -o $(OUTPUT)

clean :
	rm -f $(OUTPUT)
