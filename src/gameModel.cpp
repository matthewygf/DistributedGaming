#include "gameModel.h"


using namespace std;



GameModel::GameModel(Camera *newCamera, TileMap * newTileMap)
{
  //WorldMap;
  theCamera = newCamera;
  tile = newTileMap;
  cout<<"modelInitialised"<<endl;
  setInstance();
  
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
      c.setState(0);
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
      m.setState(0);
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
    //cats[i].update();
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
    //mice[i].update();
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
       bool c = testCollision(wall,cPos,0.5);
       int d = cats[i].getMovingDirection();
       if(c==1){
          cats[i].setOppositeDirection();//first turn around

          int new_d = generateRandom(0,3);
          while(new_d == d){ //newdirection
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
      bool c = testCollision(c2Pos, cPos,0.5);
      int d = cats[i].getMovingDirection();
      if(c==1){
         cats[i].setOppositeDirection();
         
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
      bool c = testCollision(m2Pos, mPos,0.5);
      int d = mice[i].getMovingDirection();
      if(c==1){
        mice[i].setOppositeDirection();
        
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
         mice.erase(mice.begin() + j);
         cout<<"cat  "<<c_id<<" caught Mouse "<<m_id<<endl;
         cats[i].setOppositeDirection();
        int d = cats[i].getMovingDirection();
          int new_d = generateRandom(0,3);
          while(new_d == d){
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
         mice[i].ateCheese();
         cheese.erase(cheese.begin() + j);
         mice[i].setOppositeDirection();
        
          int new_d = generateRandom(0,3);
          while(new_d == d){
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

void GameModel::runAi(int id)
{
  cout<<"got result from Client, tell animals to go into this state"<<endl;
  
  cout<<"cats[0] was in state "<<cats[0].getState()<<endl;
  cats[0].setState(id);
  cats[0].goToState();
  
  //switch(id){
    //case 0 :
     //animals->goToStates(0);
     //cout<<"this is case zero"<<endl;
     //break;
    //default:
     //cout<<"in default state"<<endl;
     //animals->goToStates(patrol state);
    // break;
  //}
  
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
  cout<<"cat Size is "<<catsSize<<endl;
  return catsSize;
}

int GameModel::getMiceSize()
{
  int miceSize = instanceModel->getNumOfMice();
  cout<<"mice Size is "<<miceSize<<endl;
  return miceSize;
}

void GameModel::doAiCalculation(int id)
{
  instanceModel->runAi(id);
}

vector<Cat> GameModel::getCatsForClient()
{
  return instanceModel->getCats();

}
vector<Mouse> GameModel::getMiceForClient()
{

  return instanceModel->getMice();
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
//this is to handle the client
void *GameModel::clientHandler(void *client)
{
   //Get the socket descriptor
    int socket = *(int*)client;
    int read_size;
    char const *message; 
    char const *test;
    //char client_message[2000]; 
    //char *d;
    //memset(client_message, 0, sizeof(client_message));
    int Buf;
    int i;
    vector<Cat> c;
    c = getCatsForClient();
 
    message = "Hey there! you are now connected to the server\n";
    write(socket , message , strlen(message));

    int a = getCatsSize();
    int net_a =  htonl(a);
    printf("establishing connections \n"); 
    sleep(2); 
    printf("connections success \n");
    
    //send all the prerequired information here.
    if( send(socket, (const char*)&net_a, sizeof(a), 0)<0){
     perror("send");
     }
    cout<<"send to client"<<endl;

    test = "Hey there! now send cats informations\n";
    write(socket , test , strlen(test));
    //for(int i = 0; i<a ; i++)
    //{
    // sleep(2);
     //if( send(socket, (const char*)&net_a, sizeof(a), 0)<0){
      //perror("send");
    // }
      //cout<<"send cats entity id to client"<<endl;
      //sleep(2);
    //}

    /**In the while loop constantly receiving message from client
     Ai calculations for which states to go in.
     possibly received by int.
     switch case:
      if client tells its 1:
         animal->goesToFirstState();
      if client tells its 2:
         animal->goesToSecondState();**/

    cout<<"receiving int from client"<<endl;
   //however we not allowed to go more than 1 second, so keep recving until connected.
   while((read_size = recv(socket, &Buf, sizeof(Buf), 0))>0)
   {
      i = ntohl(Buf);
      doAiCalculation(i);
   }
   



 
   // while( (read_size = recv(socket , client_message , sizeof(client_message) , 0)) > 0 )
    //{
                //end of string marker
	//	client_message[read_size] = '\0';
          //      d = client_message;
            //    cout<<d<<endl;
                
              //  doAiCalculation(1);

		
		//clear the message buffer
		//memset(client_message, 0, 2000);
    //}
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
        close(socket);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
        close(socket);
        pthread_exit(NULL);
        
    }

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




