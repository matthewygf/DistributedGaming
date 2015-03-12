#include "gameModel.h"
#include <stdio.h>
#include <iostream>


using namespace std;



GameModel::GameModel(Camera *newCamera, TileMap * newTileMap)
{
  //Map;
  theCamera = newCamera;
  tile = newTileMap;
  //bots;
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

void GameModel::gameSetUp(){
    initCamera();
    tile->initTexture();
}


void GameModel::drawSnowMan() {


	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}



void GameModel::drawTile()
{
   tile->render();
}

