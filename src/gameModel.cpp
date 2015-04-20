#include "gameModel.h"


using namespace std;

struct arg_struct {
    int socket;
    vector<Cat> c;
    vector<Mouse> m;
};


GameModel::GameModel(Camera *newCamera, TileMap * newTileMap)
{
  //WorldMap;
  theCamera = newCamera;
  tile = newTileMap;
  cout<<"modelInitialised"<<endl;
  setInstance();
  client = 0;
  
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

void GameModel::getCheesePos(){
  cheesePos = tile->getCheesePos();
}


vector <Cat> GameModel::getCats(){
 return cats;
}

vector <Mouse> GameModel::getMice(){
  return mice;
}

vector <int> GameModel::getMiceEaten()
{
  return miceEatenId;
}

vector <int> GameModel::getCatAteMiceVector()
{
  return catAteMice;
}

vector <int> GameModel::getMiceAteCheese()
{
  return miceAteCheese;
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
  //distribute these animals.
  //random generate some animals
  //generates cats n mouse according to ID.
  for(int i = 0 ; i<(tileWidth/2); i++){
  int r = generateRandom(0,1);
  Animal a(r);
  a.setEntityId(i);
  animals.push_back(a);
  }
  //initialise mouse n cats
  initCnM();

}



void GameModel::initCnM()
{
  float speed = 0.01;
  for (unsigned int i = 0; i<animals.size();i++)
  {

    //if the id = 0 identity cats or mice
    //to pass down the entity ID;
    int e = animals[i].getEntityId();
    if(animals[i].getId()==0){
      Cat c;
      float x = generateRandom(2,tileWidth-3);
      float y = generateRandom(2,tileHeight-5);
      
      int dir = generateRandom(0,3);
      for(unsigned int j = 0; j<wallsPos.size();j++){
           //make sure the cats positions are not same as anywalls
         while (x == wallsPos[j].x && y ==wallsPos[j].y){
             
            x += 0.5 ;
            y += 0.5 ;
        }
      }
      //inital position& moving direction
      c.setMovingDirection(dir);
      c.setEntityId(e);
      c.setPosition(x,y,0.5);
      //c.setState(0);
      c.setSpeed(speed);
      cats.push_back(c);
      //cout<<"Cats has entity IDs :"<< c.getEntityId()<<endl;
    }else{
      Mouse m;
      float x = generateRandom(2,tileWidth-3);
      float y = generateRandom(2,tileHeight-5);
      int dir = generateRandom(0,3);
      for(unsigned int j = 0; j<wallsPos.size();j++){
         while(x == wallsPos[j].x && y ==wallsPos[j].y){
              x+=0.5;
              y+=0.5;
            //x = generateRandom(2,tileWidth-3);
            //y = generateRandom(2,tileHeight-5);
        }
      }
      m.setMovingDirection(dir);
      m.setEntityId(e);
      m.setPosition(x,y,0.5);
      m.setSpeed(0.02);
      //m.setState(0);
      mice.push_back(m);
      //cout<<"Mice has entity IDs :"<< m.getEntityId()<<endl;
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
    getCheesePos();
    initAnimals();
    
}

int GameModel::getNumOfAnimals()
{
   return animals.size();
}

int GameModel::getNumOfCats()
{
   return cats.size();
}

int GameModel::getNumOfMice()
{
   return mice.size();
}

int GameModel::getNumOfMiceEaten()
{
  return miceEatenId.size();
}

int GameModel::getNumOfCatAteMice()
{
  return catAteMice.size();
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
   if(cats.size()>0){
    for (unsigned int i = 0; i<cats.size();i++){   
    glPushMatrix();
    glTranslatef(cats[i].getPositionX(),cats[i].getPositionY(),cats[i].getPositionZ());
    cats[i].render();
    //ai update to check its states
    cats[i].goToState();
    glPopMatrix();
  }
 }else{}
}

void GameModel::drawMouse()
{
 if(mice.size()>0){
 for (unsigned int i = 0; i<mice.size();i++){ 
    glPushMatrix();
    glTranslatef(mice[i].getPositionX(),mice[i].getPositionY(),cats[i].getPositionZ());
    mice[i].render();
    mice[i].goToState();
    glPopMatrix();
  }
}else{cout<<"all mouse are eaten"<<endl;}
}


void GameModel::drawCheese()
{
  if(cheesePos.size()>0){
    for(unsigned int i = 0; i<cheesePos.size();i++){
       glPushMatrix();
       glTranslatef(cheesePos[i].x,cheesePos[i].y,cheesePos[i].z);
       glColor3f(1.0,1.0,0.0);
       tile->cheese();
      glPopMatrix();
    }
  }
}



void GameModel::drawBots()
{
  //check numbers!!!!
  if(cats.size() >0){ 
   drawCats();
   }else{}
  if(mice.size() >0){
   drawMouse();
  }else{}
}

void GameModel::runCollision()
{
    if(cats.size()>0){
    catCollideWalls(wallsPos, cats);
    //mouseCollideWalls(wallsPos, mice);
    catCollideCats(cats);
    //mouseCollideMice(mice);
    //catsCaughtMice(cats,mice);
    //mouseAteCheese(cheesePos,mice);
   }
    
   if(mice.size()>0){
    //catCollideWalls(wallsPos, cats);
    mouseCollideWalls(wallsPos, mice);
    //catCollideCats(cats);
    mouseCollideMice(mice);
    //catsCaughtMice(cats,mice);
    mouseAteCheese(cheesePos,mice);
   }
  
   if(cats.size()>0 && mice.size()>0){
    //catCollideWalls(wallsPos, cats);
    //mouseCollideWalls(wallsPos, mice);
    //catCollideCats(cats);
    //mouseCollideMice(mice);
    catsCaughtMice(cats,mice);
    //mouseAteCheese(cheesePos,mice);
   }
}

int GameModel::generateRandom(int start, int end)
{
    int result = start + (rand() % (int)(end - start + 1));
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
       bool c = testCollision(wall,cPos,0.5);
       int d = cats[i].getMovingDirection();
       if(c==1){
          cats[i].setOppositeDirection();//first turn around

          int new_d = generateRandom(0,3);
          while(d == new_d){ //newdirection
              new_d = generateRandom(0,3);
          }    
          //only set new direction when not equal to old direction
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
      bool c = testCollision(walls[j],mPos,0.5);
      int d = mice[i].getMovingDirection();
      if(c==1){
          mice[i].setOppositeDirection();

          int new_d = generateRandom(0,3);
          while(d == new_d){
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
      bool c = testCollision(c2Pos, cPos,0.5);
      int d = cats[i].getMovingDirection();
      if(c==1){
         cats[i].setOppositeDirection();
         
          int new_d = generateRandom(0,3);
          while(d == new_d){
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
      bool c = testCollision(m2Pos, mPos,0.5);
      int d = mice[i].getMovingDirection();
      if(c==1){
        mice[i].setOppositeDirection();
        
          int new_d = generateRandom(0,3);
          while(d==new_d){
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

void GameModel::catsCaughtMice(vector<Cat>& cats, vector<Mouse>& mice)
{
  
   for(unsigned int i=0; i<cats.size();i++){
    Vector3 cPos = cats[i].getPosition();
    for(unsigned int j=0; j<mice.size();j++){
      Vector3 mPos = mice[j].getPosition();
      bool c = testCollision(cPos, mPos,0.5);
      if(c==1){
         int c_id = cats[i].getEntityId();
         int m_id = mice[j].getEntityId();
         cats[i].caught();
         //game model need to know which cat has eaten a mice.
         catAteMice.push_back(c_id);
         miceEatenId.push_back(m_id);
         mice.erase(mice.begin() + j);
         cout<<"cat  "<<c_id<<" caught Mouse "<<m_id<<endl;
         cats[i].setOppositeDirection();
         int d = cats[i].getMovingDirection();
         int new_d = generateRandom(0,3);
          while(d == new_d){
              new_d = generateRandom(0,3);
          }    
          cats[i].setMovingDirection(new_d);
      } 
   }
  }
}

void GameModel::mouseAteCheese(vector<Vector3>& cheese, vector<Mouse>& mice)
{
   
   for(unsigned int i=0; i<mice.size();i++){
    Vector3 mPos = mice[i].getPosition();
    for(unsigned int j=0; j<cheese.size();j++){
      Vector3 cPos = cheese[j];
      bool c = testCollision(cPos, mPos,0.25);
      int d = mice[i].getMovingDirection();
      if(c==1){
         //cheese ate
         cout<<"mice "<<mice[i].getEntityId()<<" ate cheese"<<endl;
         mice[i].ateCheese();
         miceAteCheese.push_back(mice[i].getEntityId());
         cheese.erase(cheese.begin() + j);
         mice[i].setOppositeDirection();
          int new_d = generateRandom(0,3);
          while(d == new_d){
              new_d = generateRandom(0,3);
          }    
          mice[i].setMovingDirection(new_d);
      } 
   }
  }
}

bool GameModel::testCollision(Vector3& a, Vector3& b, float width)
{
  //give a little space
  float halfWidthBox = width; 
  float halfHeightBox = width;
  if(abs(a.x - b.x)>(halfWidthBox + halfWidthBox)) return false;
  if(abs(a.y - b.y)>(halfHeightBox + halfHeightBox)) return false;
  return true;
}

void GameModel::increaseClient()
{
   client += 1;
}


// void method access via wrapper
GameModel *GameModel::instanceModel = NULL;


void GameModel::setInstance()
{
   instanceModel = this;
}


int GameModel::getAnimalSize()
{
  int animalSize = instanceModel->getNumOfAnimals();
  cout<<"animal Size is "<<animalSize<<endl;
  return animalSize;
}

int GameModel::getCatsSize()
{
  int catsSize = instanceModel->getNumOfCats();
  //cout<<"cat Size is "<<catsSize<<endl;
  return catsSize;
}

int GameModel::getMiceSize()
{
  int miceSize = instanceModel->getNumOfMice();
  //cout<<"mice Size is "<<miceSize<<endl;
  return miceSize;
}

int GameModel::getMiceEatenSize()
{
  int miceEatenSize = instanceModel->getNumOfMiceEaten();
  //cout<<"mice Size is "<<miceSize<<endl;
  return miceEatenSize;
}

int GameModel::getCatAteMiceSize()
{
  int catAteMiceS = instanceModel->getNumOfCatAteMice();
  //cout<<"mice Size is "<<miceSize<<endl;
  return catAteMiceS;
}



vector<Cat> GameModel::getCatsForClient()
{
  return instanceModel->getCats();

}
vector<Mouse> GameModel::getMiceForClient()
{

  return instanceModel->getMice();
}
vector <int> GameModel::getMiceEatenForClient()
{
  return instanceModel->getMiceEaten();
}

vector <int> GameModel::getCatAteMiceForClient()
{
  return instanceModel->getCatAteMiceVector();
}

vector <int> GameModel::getMiceAteCheeseForClient()
{
  return instanceModel->getMiceAteCheese();
}
void GameModel::registerClient()
{
  return instanceModel->increaseClient();
}

//modified from C++ tutorial point
void *GameModel::serverHandler(void *)
{
   //pass in a server class here.
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    pthread_t worker_thread;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    int yes=1;
    int rv;
    int port;
    char ipstr[INET6_ADDRSTRLEN];
    vector<string> vClientIPs; // client ip string vector


    memset(&hints, 0, sizeof hints); //make sure the struct hints is empty.
    hints.ai_family = AF_UNSPEC;  //unspecified IPV4 or IPV6
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = AI_PASSIVE; // use my IP

    //get address info
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        pthread_exit(NULL);
    }
    
     //create socket
     for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            close(sockfd);
            continue;
        }
        //bind sockets
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        if (listen(sockfd, BACKLOG) == -1) {
           perror("listen");
           close(sockfd);
           continue;
         }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
       pthread_exit(NULL);
    }

    freeaddrinfo(servinfo); // all done with this structure

    
    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        //accept the client
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        
        
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

       //tosetNon-block.
       //int flags;
       //flags = fcntl(new_fd,F_GETFL,0);
       //assert(flags != -1);
       //fcntl(new_fd, F_SETFL, flags | O_NONBLOCK);
       registerClient();
       cout<<"server: got a connection "<<endl;

       //get the client addresses
       getpeername(new_fd, (struct sockaddr*)&their_addr, &sin_size);
       


      // deal with both IPv4 and IPv6:
      if (their_addr.ss_family == AF_INET) {
       struct sockaddr_in *s = (struct sockaddr_in *)&their_addr;
       port = ntohs(s->sin_port);
       inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
      } else { // AF_INET6
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&their_addr;
        port = ntohs(s->sin6_port);
        inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
     }

      cout << "Connection accepted from "  << ipstr <<  " using port " << port << endl;
      vClientIPs.push_back(ipstr); //insert client ip
      

      
           //create a thread for each client
         if (pthread_create(&worker_thread, NULL, clientHandler, (void *)&new_fd) != 0) 
           {
			perror("Could not create a worker thread");
			pthread_exit(NULL);
	   }

        
    }
   
   pthread_exit(NULL);
}



//modified from https://gist.github.com/5821760.git is included in the supports folder
//this is to handle each client
void *GameModel::clientHandler(void *client)
{
  int b = 0;
  int net_b = htonl(b);
  int socket = *(int*)client;
  while(instanceModel->client<2)
  {
    cout<<"waiting for 2 clients to connect"<<endl;
    if(send(socket, (const char*)&net_b, sizeof(b), MSG_NOSIGNAL)<0)
      {perror("error");}
     sleep(2);
  }
  cout<<"ready"<<endl;
  b=1;
  net_b = htonl(b);
  sleep(1);
  if(send(socket, (const char*)&net_b, sizeof(b), MSG_NOSIGNAL)<0)
      {perror("error");}
  
  //call a method to split animals into 2;
      

    /*
   //Get the socket descriptor
    int socket = *(int*)client;
    int read_size;
    char const *message; 
    //char const *info;
    char const *e_cats;
    char const *e_mice;
    char const *client_mice_eaten;
    char const *client_cat_eaten_mice;
    char const *client_mice_ate_cheese;
    char client_message[2000]; 
    memset(client_message, 0, sizeof(client_message));
    int b,a,catAteMiceSize,net_a,net_b,Buf,net_Buf,aiSize,net_ai;
    int old_a = 0;
    int temp = 0;
    int tempCheese=0;
    vector<Cat> c;
    vector<Mouse> m;
    vector<int>   current_mice_eaten; //to keep track of the mice eaten size.
    vector<int>   current_cat_has_eaten_mice;
    vector<int>   current_mice_ate_cheese;

    c = getCatsForClient(); //get the cats in the model
    m = getMiceForClient(); //get the mice in the model
    current_mice_eaten = getMiceEatenForClient(); //get mice eaten in the model.
    current_cat_has_eaten_mice = getCatAteMiceForClient();
    current_mice_ate_cheese = getMiceAteCheeseForClient();
    
    string entity_ids_for_cats;
    string entity_ids_for_mice = "m";
    string entity_Cat_Eaten_Mice = "c";
    string entity_mice_ate_cheese;
    
    message = "Hey there! you are now connected to the server.\n ";
    write(socket , message , strlen(message));
    
    printf("establishing connections \n"); 
    printf("connections success \n");

    //send all the cats entity ID to client
   for(unsigned int i = 0; i<c.size();i++){
      int j = c[i].getEntityId();
      stringstream ss;
      ss << j;
      string str = ss.str();
      entity_ids_for_cats.append(str);
     if(i != c.size()-1){
      entity_ids_for_cats.append(",");}
   }
   //cout<<"entity_ids_for_cats = "<<entity_ids_for_cats<<endl;
   e_cats = entity_ids_for_cats.c_str();

   for(unsigned int i = 0; i<m.size();i++){
      int j = m[i].getEntityId();
      stringstream ss;
      ss << j;
      string str = ss.str();
      entity_ids_for_mice.append(str);
     if(i != m.size()-1){
      entity_ids_for_mice.append(",");}
     }
   // cout<<"entity_ids_for_mice = "<<entity_ids_for_mice<<endl;
 
   e_mice = entity_ids_for_mice.c_str();
   sleep(1);
   
   //send all the mice entity ID to client
   
   write(socket , e_cats , strlen(e_cats));
   cout<<"sending cats entitys id"<<endl;
   write(socket , e_mice , strlen(e_mice));
   cout<<"sending mice entitys id"<<endl;

   sleep(1);
    //start the loop here to send n recv from client
    //first update how many cats n mice in the model.
    while((read_size = recv(socket, &Buf, sizeof(Buf), 0))>0){
    net_Buf = ntohl(Buf);
    cout<<net_Buf<<endl;

    b = getMiceSize();
    net_b =  htonl(b);
    a = getMiceEatenSize();
    net_a = htonl(a);
    catAteMiceSize = getCatAteMiceSize();
    //net_catAteMiceSize = htonl(catAteMiceSize);
    string mice_eaten;
    current_mice_eaten = getMiceEatenForClient();
    current_cat_has_eaten_mice = getCatAteMiceForClient();
    current_mice_ate_cheese = getMiceAteCheeseForClient();

    //dont need to send cats size as cats wont die.
    //only mice.
    if(send(socket, (const char*)&net_b, sizeof(b), MSG_NOSIGNAL)<0)
      {perror("error");}

   //send the size of the mice eaten.
   if(send(socket, (const char*)&net_a, sizeof(a), MSG_NOSIGNAL)<0)
      {perror("error");}
    
    if(a != 0 && (abs(a-old_a))!=0){
     for(unsigned int i = old_a; i<current_mice_eaten.size();i++){
      int j = current_mice_eaten[i];
      stringstream ss;
      ss << j;
      string str = ss.str();
      mice_eaten.append(str);
     if(i != current_mice_eaten.size()-1){
       mice_eaten.append(",");}
     }
    client_mice_eaten = mice_eaten.c_str();
    write(socket , client_mice_eaten , strlen(client_mice_eaten));
    cout<<"mice that got eaten sent"<<endl;
    }else{cout<<"current no mouse has been eaten"<<endl;}

   if(catAteMiceSize != 0 && (abs(catAteMiceSize - temp))!=0){
     for(int i = temp; i<catAteMiceSize;i++){
      int j = current_cat_has_eaten_mice[i];
      stringstream ss;
      ss << j;
      string str = ss.str();
      entity_Cat_Eaten_Mice.append(str);
     if(i != catAteMiceSize-1){
       entity_Cat_Eaten_Mice.append(",");}
     }
    client_cat_eaten_mice = entity_Cat_Eaten_Mice.c_str();
    write(socket , client_cat_eaten_mice , strlen(client_cat_eaten_mice));
    cout<<"cat that ate mouse sent"<<endl;
   }else{cout<<"current no cat has eaten a mouse"<<endl;}

  sleep(3);
  int mac_size = current_mice_ate_cheese.size();
  int net_mac_size = htonl(mac_size);;
  cout<<"mac_size "<<mac_size<< " send"<<endl;
  if(send(socket, (const char*)&net_mac_size, sizeof(mac_size), MSG_NOSIGNAL)<0)
      {perror("error");}
   
  if(current_mice_ate_cheese.size() != 0 && 
     (fabs(current_mice_ate_cheese.size() - tempCheese))!=0){
    for(unsigned int i = tempCheese; i<current_mice_ate_cheese.size();i++){
     int j = current_mice_ate_cheese[i];
     stringstream ss;
      ss << j;
      string str = ss.str();
     entity_mice_ate_cheese.append(str);
     if(i != current_mice_ate_cheese.size()-1){
       entity_mice_ate_cheese.append(",");
     }
    }
    client_mice_ate_cheese = entity_mice_ate_cheese.c_str();
    write(socket,client_mice_ate_cheese,strlen(client_mice_ate_cheese));
   }else{cout<<"current no cheese has been eaten"<<endl;}   


    old_a = a;
    temp = catAteMiceSize;
    tempCheese = current_mice_ate_cheese.size();
    //doAiCalculation
    recv(socket, &net_ai, sizeof(net_ai), 0);
    aiSize = ntohl(net_ai);
    
    char s[aiSize+1];
    string a;
    int bufRead;
    memset(s,0,sizeof(s));
    if(aiSize>0){
      bufRead=(recv(socket,&s,aiSize,0)); 
      s[bufRead] = '\0';   
      a = s;
    }
 
    //splitUpthe strings
    vector<string> catsNStates;
    vector<string> miceNStates;
    string split = "m";
    string catsStates = a.substr(0, a.find(split));
    string miceStates = a.substr(a.find(split)+1, a.length());
    cout<<"CatsStates : "<<catsStates<<endl;
    cout<<"MiceStates : "<<miceStates<<endl;

   ///////////////////////////////////////store the stores to set.
    string delimiter = ",";
    size_t pos = 0;
    string token;
    while ((pos = catsStates.find(delimiter)) != string::npos) {
       token = catsStates.substr(0, pos);
       //cout << token << endl;
       catsNStates.push_back(token);
       catsStates.erase(0, pos + delimiter.length());
     }
     catsNStates.push_back(catsStates);
   /////////////////////////////////////////////////////////////////////
     while ((pos = miceStates.find(delimiter)) != string::npos) {
       token = miceStates.substr(0, pos);
       //cout << token << endl;
       miceNStates.push_back(token);
       miceStates.erase(0, pos + delimiter.length());
     }
     miceNStates.push_back(miceStates);

///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////finally need to set states.
    for(unsigned int i=0; i<catsNStates.size();i++){
     string x = catsNStates[i];
     string delimiter = ":";
     size_t pos = 0;
     string etoken;
     while ((pos = x.find(delimiter)) != string::npos) {
       etoken = x.substr(0, pos);
       //catsNStates.push_back(token);
       x.erase(0, pos + delimiter.length());
     }
      for(unsigned int j=0; j<c.size();j++)
      {
        int value = atoi(etoken.c_str());
        int s     = atoi(x.c_str());
        if(value == instanceModel->cats[j].getEntityId())
	{
          instanceModel->cats[j].setState(s);
         //cout << etoken << endl;
         //cout<<x<<endl;
          cout<<"cat entity "<<instanceModel->cats[j].getEntityId()<<" state : "<<instanceModel->cats[j].getState()<<endl;
        }
      }
    }
   
    if(miceNStates.size()>0)
    {
     for(unsigned int i=0; i<miceNStates.size();i++){
     string x = miceNStates[i];
     string delimiter = ":";
     size_t pos = 0;
     string etoken;
     while ((pos = x.find(delimiter)) != string::npos) {
       etoken = x.substr(0, pos);
       x.erase(0, pos + delimiter.length());
     }
      for(unsigned int j=0; j<m.size();j++)
      {
        int value = atoi(etoken.c_str());
        int s     = atoi(x.c_str());
        if(value == instanceModel->mice[j].getEntityId())
	{
          instanceModel->mice[j].setState(s);
         //cout << etoken << endl;
         //cout<<x<<endl;
          cout<<"mouse entity "<<instanceModel->mice[j].getEntityId()<<" state : "<<instanceModel->mice[j].getState()<<endl;
        }
      }
    }
   }






    sleep(3); 
    
   }
   
   if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
        close(socket);
    }
    else if(read_size == -1)
    {
        puts("recv failed");
        puts("Client disconnected");
        //fflush(stdout);
        close(socket);   
    }
 
   


   

    /**In the while loop constantly receiving message from client
     Ai calculations for which states to go in.
     possibly received by int.
     switch case:
      if client tells its 1:
         animal->goesToFirstState();
      if client tells its 2:
         animal->goesToSecondState();**/
   

   return 0;
}


//server thread
void GameModel::createThreads()
{
   pthread_t serverThread;
   int rc;
   
      rc = pthread_create(&serverThread, NULL, 
                          serverHandler, NULL);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
}




