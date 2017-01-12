/*
 * Bomb.cpp
 *
 *  Created on: 2016. 3. 11.
 *      Author: SanglaeKim
 */
#include <stdio.h>
#include <stdint.h>
#include <iostream>
using namespace std;

typedef enum sig{UP_SIG, DOWN_SIG, ARM_SIG, TICK_SIG}Sig;
class Event { public: Sig m_sig;};

class Bomb;

class State{
public:
  void dispatch(Bomb *context, Event *event)const{}
};

class SettingState : public State {
public:
  void dispatch(Bomb *context, Event *event);
};

class TimingState : public State {
public:
  void dispatch(Bomb *context, Event *event);
};

class Bomb{
private:
  State const *m_state;
  uint8_t m_timeout, m_code, m_defuse;
private:
  void tran(State const *target){m_state = target;}
private:
  static SettingState const setting;
  static TimingState const timing;

  friend class SettingState;
  friend class TimingState;
public:
  Bomb(uint8_t defuse) :m_defuse(defuse){}
  void init();
  void dispatch(Event *event){m_state->dispatch(this, event);};
};

// the initial value of the timeout
#define INIT_TIMEOUT 30
SettingState const Bomb::setting;
TimingState const Bomb::timing;

void Bomb::init() {
  m_timeout = INIT_TIMEOUT;
  tran(&Bomb::setting);
}


void SettingState::dispatch(Bomb *context, Event *event){
  switch(event->m_sig){
  case UP_SIG:
    if(context->m_timeout < 60 ){
      ++context->m_timeout;
      //BSP_display(context->m_timeout);
    }
    break;
  case DOWN_SIG:
    if(context->m_timeout > 1){
      --context->m_timeout;
      //BSP_display(context->m_timeout);
    }
    break;
  case ARM_SIG:
    context->m_code = 0;
    context->tran(&Bomb::timing);
    break;
  case TICK_SIG:
    break;
  default:
    printf("This is a default case!!!\n");
    break;
  }
}

void TimingState::dispatch(Bomb *context, Event *event){
  switch(event->m_sig){
  case UP_SIG:
    context->m_code <<= 1;
    context->m_code |= 1;
    break;
  case DOWN_SIG:
    context->m_code <<= 1;
    break;
  case ARM_SIG:
    printf("code: %x, defuse: %x\n", context->m_code, context->m_defuse);
    if (context->m_code == context->m_defuse) {
      printf("going back to seeting state!!\n");
      context->tran(&Bomb::setting); // transition to "setting"
    }
    break;
  case TICK_SIG:
    --context->m_timeout;
    //BSP_display(context->m_timeout);
    if (context->m_timeout == 0) {
      //BSP_boom(); // destroy the bomb
    }
    break;
  default:
    printf("This is a default case!!!\n");
    break;
  }
}

int main(){


  //init_btn_interrupt();
  //init_timer_interrupt();
  //init_sw_interrupt();

  Bomb myBomb(0x7);
  myBomb.init();

  while(1){
    //Event event;
    //        if(onUp) {
    //          event.m_sig = UP_SIG;
    //          myBomb.dispatch(&event); onUp = 0;}
    //        if(onDown) {
    //          event.m_sig = DOWN_SIG;
    //          myBomb.dispatch(&event); onDown = 0;}
    //        if(onTimer){
    //          event.m_sig = ARM_SIG;
    //          myBomb.dispatch(&event); onTimer = 0;}
    //        if(onSw1){
    //          event.m_sig = TICK_SIG;
    //          myBomb.dispatch(&event); onSw1 = 0;}
  }
  return 0;
}



//  int five_sec_count = 0;
//  init_btn_interrupt();
//  init_timer_interrupt();
//
//  printf("Hello Bomb\n");
//  Bomb3 theBomb(7);
//  theBomb.init();
//  theBomb.onUP();
//  theBomb.onDOWN();
//  theBomb.onARM();
