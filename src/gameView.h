#ifndef GAMEVIEW_h
#define GAMEVIEW_h

#include "gameModel.h"
#include "gameController.h"

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
    //frame
    int frame;
    //camera
    float pos_x, pos_y, pos_z;
    float lpos_x,lpos_y,lpos_z;
    float ang;
    
    void init();
    void initLights();
    void update();
    void reset();

};

#endif
