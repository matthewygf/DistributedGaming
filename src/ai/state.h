#ifndef STATE_H
#define STATE_H
//modified from State.h in supports directories from 'WestWorld1' 
//by Mat Buckland 2002 (fup@ai-junkie.com) 
//------

class Animal;

class State
{
  public:
  virtual ~State(){}
  
  //execute when state is entered
  virtual void Enter(Animal*) = 0;

  //execute when state's normal update function
  virtual void Execute(Animal*) = 0;
 
  virtual void Exit(Animal*) = 0;

};

#endif
