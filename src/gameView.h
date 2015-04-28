#ifndef GAMEVIEW_h
#define GAMEVIEW_h
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "gameModel.h"
#include "gameController.h"
#include "../include/vbo/src/Timer.h"
#include <sstream>
#include <vector>
#include "../include/matrix/src/Vectors.h"
#include "../include/frustumG/frustumG.h"
#include "bots/animal.h"
#include <iostream>
#include <fstream>
#include "bots/cat.h"
#include "bots/mouse.h"
using namespace std;
class GameView
{       
    public:
    //constructor
    GameView(GameController *newGameController, GameModel *newGameModel);

    virtual~GameView();

    
    //initialise glut for graphics window
    int render(int argc, char *argv[]);
    
    //check positions
    void checkPos();
    
    //drawstrings on screen
    void drawString(const char *str, int x, int y, float color[4], void *font);

    //fpscount
    void countFPS();
    //display the informations
    void showInfo();
    void showScores();
    
    //setters
    void setInstanceObject();
    void setWindowResolution(int w, int h);
    void setWindowTitle(const char* title);

    
    
    //glut methods
    virtual void display();
    virtual void reshape(int w, int h);
    virtual void animate(int t);
    
    //wrapper methods
    static void displayWrapper();
    static void reshapeWrapper(int w, int h);
    static void timerWrapper (int t);
    static void keyboardWrapper(unsigned char key, int x, int y);
    static void specialInputWrapper(int key, int x, int y);
    static void upFunctionInputWrapper(int key, int x, int y);
    
    private:
    static GameView *instanceView;
    static GameController *instanceController;
    
    GameController *theGameController;
    GameModel *theGameModel;
    
    int width, height;
    const char* winTitle;
    void *font;
    static const int   TEXT_WIDTH      = 8;
    static const int   TEXT_HEIGHT     = 13;
    //frame
    int frame;
    int frameCount;
    //camera
    float pos_x, pos_y, pos_z;
    float lpos_x,lpos_y,lpos_z;
    float a;
    float nearP;
    float farP;
    float angle; 
    float aspect;
    float ang;
    float deltaAngle;
    float deltaMove;
    //GL initialise methods
    void init();
    void initLights();
    void update();
    void reset();
    //for the measuring time
    Timer t1,t2,total,run;
    float drawAndAiTime, physicsTime,totalTime,runTime;
    vector<Cat> cats;
    vector<Mouse> mice;
    

};

#endif
