#ifndef TSTATEMACHINE_H
#define TSTATEMACHINE_H


//slightly modifed from below and is included in the supports libraries folder for credits
//------------------------------------------------------------------------
//
//  Name:   StateMachine.h
//
//  Desc:   State machine class. Inherit from this class and create some 
//          states to give your agents FSM functionality
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <cassert>
#include <string>
#include <typeinfo>
#include "templateState.h"
#include <iostream>
using namespace std;


template <class entity_type>
class TStateMachine
{
  private:

     //a pointer to the agent that owns this instance
     entity_type*          agent;

     TState<entity_type>*   currentState;
  
     //a record of the last state the agent was in
     TState<entity_type>*   previousState;

     //this is called every time the FSM is updated
     TState<entity_type>*   globalState;
  

  public:

       TStateMachine(entity_type* owner):agent(owner),
                                   currentState(NULL),
                                   previousState(NULL),
                                   globalState(NULL)
      {}

       virtual ~TStateMachine(){}

      //use these methods to initialize the FSM
      void SetCurrentState(TState<entity_type>* s){currentState = s;}
      void SetGlobalState(TState<entity_type>* s) {globalState = s;}
      void SetPreviousState(TState<entity_type>* s){previousState = s;}
  
     //call this to update the FSM
     void  Update()const
     {
       //cout<<"updating states"<<endl;
    //if a global state exists, call its execute method, else do nothing
       if(globalState)   globalState->Execute(agent);

    //same for the current state
       if (currentState) currentState->Execute(agent);
     }

  //change to a new state
    void  ChangeState(TState<entity_type>* newState)
     {
        assert(newState && 
           "<StateMachine::ChangeState>: trying to change to NULL state");

    //keep a record of the previous state
         previousState = currentState;

    //call the exit method of the existing state
         currentState->Exit(agent);

    //change state to the new state
         currentState = newState;

    //call the entry method of the new state
       currentState->Enter(agent);
     }

  //change state back to the previous state
      void  RevertToPreviousState()
       {
         ChangeState(previousState);
       }

  //returns true if the current state's type is equal to the type of the
  //class passed as a parameter. 
      bool  isInState(const TState<entity_type>& st)const
         {
          return typeid(*currentState) == typeid(st);
         }

  TState<entity_type>*  CurrentState()  const{return currentState;}
  TState<entity_type>*  GlobalState()   const{return globalState;}
  TState<entity_type>*  PreviousState() const{return previousState;}
};




#endif
