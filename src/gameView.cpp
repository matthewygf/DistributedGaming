#include "gameView.h"

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
using namespace std;

GameView::GameView(GameController *newGameController, GameModel *newGameModel)
{
  theGameController = newGameController;
  theGameModel = newGameModel;
  width = 800;
  height = 600;
  winTitle = "GAME_TEST";
  
  cout<<"viewInitialised"<<endl;
}

GameView::~GameView()
{
  delete instanceView;
  delete instanceController;
  delete theGameController;
  delete theGameModel;
  delete winTitle;
  cout<<"deleting everything within View"<<endl;
}


void GameView::initLights()
{
 // initialise lighting
  glEnable(GL_LIGHT0);	
  GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
  GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

void GameView::init()
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_NORMALIZE);
   glShadeModel(GL_SMOOTH);
   initLights();
   glEnable(GL_LIGHTING);
   theGameModel->gameSetUp();
   
  
}

void GameView::display()
{
 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glFlush();
   
   //drawscenes
   glLoadIdentity();
    //updateTheGameSetting
   update();
 
   //camera lookAt

   gluLookAt(pos_x, pos_y, pos_z,
	    pos_x + theGameModel->getLPosition_x(),
	    theGameModel->getLPosition_y(),
	    pos_z+theGameModel->getLPosition_z(),
	    0.0, 1.0,  0.0);
	    
   glRotatef(theGameModel->getAngle(),0.0,1.0,0.0); //camera angle
   
	
        theGameModel->drawTile();
   
   
    glutSwapBuffers();    
}




void GameView::reshape(int w, int h) {
  
  if(h==0)
      h = 1;
  float aspect = w * 1.0/h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45.0,aspect,0.1,100);
  glMatrixMode(GL_MODELVIEW);
}

void GameView::setWindowResolution(int w, int h) {
  width = w;
  height = h;
}

void GameView::animate(int t) {
  glutPostRedisplay();
  glutTimerFunc(16, timerWrapper, 0); //reset display
}

void GameView::setWindowTitle(const char* title)
{
  winTitle = title;
}

// void method access via wrapper
GameView *GameView::instanceView = NULL;
GameController *GameView::instanceController = NULL;

void GameView::setInstanceObject() {
  instanceView = this; //wrap around itself
  instanceController = theGameController; //wrap around the controller
  cout<<"setinstanceobject"<<endl;
}

void GameView::displayWrapper() {
  instanceView->display();
}

void GameView::reshapeWrapper(int w, int h) {
  instanceView->reshape(w,h);
}

void GameView::timerWrapper(int t) {
  instanceView->animate(t);
}

//void GameView::menuWrapper(int item) {
  //instanceController->menu(item);
//}

//void GameView::mouseWrapper(int button, int state, int x, int y) {
 // instanceController->mouse(button, state, x, y);
//}

void GameView::keyboardWrapper(unsigned char key, int x, int y) {
  instanceController->keyboard(key, x, y);
}

void GameView::specialInputWrapper(int key, int x, int y) {
  instanceController->specialInput(key, x, y);
}

void GameView::upFunctionInputWrapper(int key, int x, int y){
  instanceController->specialFunctionInput(key,x,y);
}

void GameView::update() {
  pos_x = theGameModel->getPosition_x();
  pos_y = theGameModel->getPosition_y();  
  pos_z = theGameModel->getPosition_z();
}


int GameView::render(int argc, char *argv[])
{
  setInstanceObject();
  pthread_getconcurrency();
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow(winTitle);
  glutInitWindowSize(width,height);
  
  //init GL  
  init();
  
  glutDisplayFunc(displayWrapper);
  glutReshapeFunc(reshapeWrapper);
  glutTimerFunc(16,timerWrapper,0);
  
  //add keyboard/mouse listener
  //glutMouseFunc(mouseWrapper);
  glutKeyboardFunc(keyboardWrapper);
  glutSpecialFunc(specialInputWrapper);
  glutSpecialUpFunc(upFunctionInputWrapper);
  glutMainLoop();

  return 0;
}





