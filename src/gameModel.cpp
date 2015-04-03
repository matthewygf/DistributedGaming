#include "gameModel.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <cmath>

using namespace std;



GameModel::GameModel(Camera *newCamera, TileMap * newTileMap)
{
  //WorldMap;
  theCamera = newCamera;
  tile = newTileMap;
  cout<<"modelInitialised"<<endl;
  
}

GameModel::~GameModel()
{
   delete theCamera;
   delete tile;

   cout<<"deleting things in model"<<endl;
}

// getter
float GameModel::getPosition_x(){
 return position_x;
}
float GameModel::getPosition_y(){
 return position_y;
}
float GameModel::getPosition_z(){
 return position_z;
}

float GameModel::getLPosition_x(){
 return lposition_x;
}

float GameModel::getLPosition_y(){
 return lposition_y;
}

float GameModel::getLPosition_z(){
 return lposition_z;
}

float GameModel::getAngle(){
 return angle;
}

float GameModel::getDeltaAngle()
{
   return deltaAngle;
}

float GameModel::getDeltaMove()
{
   return deltaMove;
}

int GameModel::getWindowWidth() {
  return width;
}

int GameModel::getWindowHeight() {
  return height;
}

float GameModel::getCameraPos_x(){
  position_x = theCamera->getPos_x();
  return position_x;
}

float GameModel::getCameraPos_y(){
  position_y = theCamera->getPos_y();
  return position_y;
}

float GameModel::getCameraPos_z(){
  position_z = theCamera->getPos_z();
  return position_z;
}

void GameModel::getCameraPos(){
  getCameraPos_x();
  getCameraPos_y();
  getCameraPos_z();
}

float GameModel::getCameraLookAtPos_x(){
  lposition_x = theCamera->getLookAtPos_x();
  return lposition_x;
}

float GameModel::getCameraLookAtPos_y(){
  lposition_y = theCamera->getLookAtPos_y();
  return lposition_y;
}

float GameModel::getCameraLookAtPos_z(){
  lposition_z = theCamera->getLookAtPos_z();
  return lposition_z;
}

void GameModel::getCameraLookAtPos(){
  getCameraLookAtPos_x();
  getCameraLookAtPos_y();
  getCameraLookAtPos_z();
}

float GameModel::getCameraAngle(){
  angle = theCamera->getCameraAngle();
  return angle;
}

void GameModel::getWallsPos(){
  wallsPos = tile->getWallsPos();
}

// setter

void GameModel::setPosition_x(float new_x){
 position_x = new_x;
}
void GameModel::setPosition_y(float new_y){
 position_y = new_y;
}
void GameModel::setPosition_z(float new_z){
 position_z = new_z;
}

void GameModel::setLPosition_x(float newLookAt_x){
 lposition_x = newLookAt_x;
}

void GameModel::setLPosition_y(float newLookAt_y){
 lposition_y = newLookAt_y;
}

void GameModel::setLPosition_z(float newLookAt_z){
 lposition_z = newLookAt_z;
}

void GameModel::setAngle(float newAngle){
 angle=newAngle;
}

void GameModel::setDeltaAngle(float dAngle){
   deltaAngle = dAngle;
}

void GameModel::setDeltaMove(float move){
    deltaMove = move;
}

void GameModel::setWindowResolution(int new_width, int new_height) {
  width = new_width;
  height = new_height;
}

void GameModel::setCameraPos(float new_x, float new_y, float new_z){
    theCamera->setPos_x(new_x);
    theCamera->setPos_y(new_y);
    theCamera->setPos_z(new_z);
}

void GameModel::setCameraLookAtPos(float newLookAt_x, float newLookAt_y, float newLookAt_z){
    theCamera->setLookAtPos_x(newLookAt_x);
    theCamera->setLookAtPos_y(newLookAt_y);
    theCamera->setLookAtPos_z(newLookAt_z);
}

void GameModel::setCameraAngle(float newAngle){
    theCamera->setCameraAngle(newAngle);
}

void GameModel::initCamera(){
    getCameraPos();
    getCameraLookAtPos();
    getCameraAngle();
}

void GameModel::initAnimals()
{
  //random generate some animals
  //generates cats n mouse according to ID.
  for(int i = 0 ; i<(tileWidth/2); i++){
  int r = generateRandom(0,1);
  Animal a(r);
  animals.push_back(a);
  }
  //initialise mouse n cats
  initCnM();

}

void GameModel::initCnM()
{
  for (unsigned int i = 0; i<animals.size();i++)
  {
    //if the id = 0
    if(animals[i].getId()==0){
      Cat c;
      float x = generateRandom(2,tileWidth-3);
      float y = generateRandom(2,tileHeight-5);
      int dir = generateRandom(0,3);
      for(unsigned int j = 0; j<wallsPos.size();j++){
           //make sure the cats positions are not same as anywalls
         while(x == wallsPos[j].x && y ==wallsPos[j].y){
            x = generateRandom(2,tileWidth-3);
            y = generateRandom(2,tileHeight-5);
        }
      }
      //inital position& moving direction
      c.setMovingDirection(dir);
      c.setPosition(x,y,0.5);
      cats.push_back(c);
    }else{
      Mouse m;
      float x = generateRandom(2,tileWidth-3);
      float y = generateRandom(2,tileHeight-5);
       int dir = generateRandom(0,3);
      for(unsigned int j = 0; j<wallsPos.size();j++){
         while(x == wallsPos[j].x && y ==wallsPos[j].y){
            x = generateRandom(2,tileWidth-3);
            y = generateRandom(2,tileHeight-5);
        }
      }
      m.setMovingDirection(dir);
      m.setPosition(x,y,0.5);
      mice.push_back(m);
   }
  }
  cout<<cats.size()<<endl;
  cout<<mice.size()<<endl;
}



void GameModel::gameSetUp(){
    initCamera();
    tile->initTexture();
    getTileSettings();
    getWallsPos();
    initAnimals();
}

void GameModel::getTileSettings(){
  tileWidth = tile->getWidth();
  tileHeight= tile->getHeight();
}

void GameModel::drawTile()
{
   tile->render();
}

void GameModel::drawCats()
{
    for (unsigned int i = 0; i<cats.size();i++){   
    glPushMatrix();
    glTranslatef(cats[i].getPositionX(),cats[i].getPositionY(),cats[i].getPositionZ());
    cats[i].render();
    cats[i].update();
    glPopMatrix();
  }
}

void GameModel::drawMouse()
{
 for (unsigned int i = 0; i<mice.size();i++){ 
    glPushMatrix();
    glTranslatef(mice[i].getPositionX(),mice[i].getPositionY(),cats[i].getPositionZ());
    mice[i].render();
    //ai update.
    mice[i].update();
    glPopMatrix();
  }
}

void GameModel::drawBots()
{
  drawCats();
  drawMouse();
}

void GameModel::runCollision()
{
    catCollideWalls(wallsPos, cats);
    mouseCollideWalls(wallsPos, mice);
    catCollideCats(cats);
    mouseCollideMice(mice);
    //cout<<"testing collision"<<endl;
}
int GameModel::generateRandom(int start, int end)
{
    random_device                  rand_dev;
    mt19937                        generator(rand_dev());
    uniform_int_distribution<int>  distr(start, end);
    int result = distr(generator);
    return result;
    
}

void GameModel::catCollideWalls(vector<Vector3>& walls, vector<Cat>& cats)
{
  //vector3 is a position
  //getThePosition of the Cat and test against walls
  //for each cat, test against each walls
  for(unsigned int i=0;i<cats.size();i++){
    for(unsigned int j=0; j<walls.size();j++){
       Vector3 cPos = cats[i].getPosition();
       Vector3 wall = walls[j];
       bool c = testCollision(wall,cPos);
       if(c==1){
          int d = cats[i].getMovingDirection();
          cats[i].setOppositeDirection();//stop()
          int new_d = generateRandom(0,3);
          while(new_d == d){
              new_d = generateRandom(0,3);
          }    
          cats[i].setMovingDirection(new_d);
          //cout<<"collision at cat "<<i<<" with wall "<<j<<endl;
          //cout<<"Position of cat "<<cPos<<" ,wall position is "<<wall<<endl;
         }
       //pass the result back to cat's AI. so it realise it hits wall and need to change its direction
     }  
  }
}

void GameModel::mouseCollideWalls(vector<Vector3>& walls,vector<Mouse>& mice)
{
  for(unsigned int i=0;i<mice.size();i++){
    for(unsigned int j=0;j<walls.size();j++){
      Vector3 mPos = mice[i].getPosition();
      bool c = testCollision(walls[j],mPos);
      if(c==1){
          int d = mice[i].getMovingDirection();
          mice[i].setOppositeDirection();//stop()
          int new_d = generateRandom(0,3);
          while(new_d == d){
              new_d = generateRandom(0,3);
          }    
          mice[i].setMovingDirection(new_d);
        //cout<<"collision at mouse "<<i<<" with wall "<<j<<endl;
        //cout<<"Position of mouse"<<mPos<<" ,wall position is "<<walls[j]<<endl;
      } 
    }
  }
 //need to pass the result back to mouse's AI.
}

void GameModel::catCollideCats(vector<Cat>& cats)
{
  for(unsigned int i=0; i<cats.size();i++){
    Vector3 cPos = cats[i].getPosition();
    for(unsigned int j=0; j<cats.size();j++){
      if(i!=j){ // except itself.
      Vector3 c2Pos = cats[j].getPosition();
      bool c = testCollision(c2Pos, cPos);
      if(c==1){
         int d = cats[i].getMovingDirection();
          cats[i].setOppositeDirection();//stop()
          int new_d = generateRandom(0,3);
          while(new_d == d){
              new_d = generateRandom(0,3);
          }    
          cats[i].setMovingDirection(new_d);
        //cout<<"collision at cat "<<i<<" with another cat "<<j<<endl;
        //cout<<"Position of cat"<<cPos<<" ,another cat position is "<<c2Pos<<endl;
      } 
    }else{}
   }
  }
}


void GameModel::mouseCollideMice(vector<Mouse>& mice)
{
  for(unsigned int i=0; i<mice.size();i++){
    Vector3 mPos = mice[i].getPosition();
    for(unsigned int j=0; j<mice.size();j++){
      if(i!=j){ // except itself.
      Vector3 m2Pos = mice[j].getPosition();
      bool c = testCollision(m2Pos, mPos);
      if(c==1){
        int d = mice[i].getMovingDirection();
          mice[i].setOppositeDirection();//stop()
          int new_d = generateRandom(0,3);
          while(new_d == d){
              new_d = generateRandom(0,3);
          }    
          mice[i].setMovingDirection(new_d);
        //cout<<"collision at mouse "<<i<<" with another mouse "<<j<<endl;
        //cout<<"Position of mouse"<<mPos<<" ,another mouse position is "<<m2Pos<<endl;
      } 
    }else{}
   }
  }

}


bool GameModel::testCollision(Vector3& a, Vector3& b)
{
  //give a little space
  float halfWidthBox = 0.5; 
  float halfHeightBox = 0.5;
  if(abs(a.x - b.x)>(halfWidthBox + halfWidthBox)) return false;
  if(abs(a.y - b.y)>(halfHeightBox + halfHeightBox)) return false;
  return true;
}

