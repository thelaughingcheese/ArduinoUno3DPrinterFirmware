/*--------------------------
holds info and controls stepping

set type to true if is direct stepper driver aka diy driver
--------------------------*/

#include <Arduino.h>
#include "digitalWriteFast.h"

class stepper_handle{
private:
  int stepper_pin_1;
  int stepper_pin_2;
  boolean type;

  void set_state();
  /*----------------
  1 - on on
  2 - on off
  3 - off off
  4 - off on
  ----------------*/
  int state;
  
public:
  stepper_handle(int,int,boolean);
  void make_step(boolean);
};

stepper_handle::stepper_handle( int _pin_1, int _pin_2, boolean type){
  stepper_pin_1 = _pin_1;
  stepper_pin_2 = _pin_2;
  this->type = type;
  
  pinMode(_pin_1,OUTPUT);
  pinMode(_pin_2,OUTPUT);
  
  if(this->type){
    state = 1;
    set_state();
  }
};

void stepper_handle::set_state(){
  switch(state){
    case(1):{
      digitalWriteFast(stepper_pin_1,HIGH);
      digitalWriteFast(stepper_pin_2,HIGH);
      break;
    };
    case(2):{
      digitalWriteFast(stepper_pin_1,HIGH);
      digitalWriteFast(stepper_pin_2,LOW);
      break;
    };
    case(3):{
      digitalWriteFast(stepper_pin_1,LOW);
      digitalWriteFast(stepper_pin_2,LOW);
      break;
    };
    case(4):{
      digitalWriteFast(stepper_pin_1,LOW);
      digitalWriteFast(stepper_pin_2,HIGH);
      break;
    };
  };
};

void stepper_handle::make_step( boolean _dir ){
  if(!type){
    digitalWriteFast(stepper_pin_1, _dir);
    digitalWriteFast(stepper_pin_2, HIGH);
    digitalWriteFast(stepper_pin_2, LOW);
    return;
  }
  
  //1 for forward 0 for backward
  if (_dir){
    if (state == 4){
      state = 1;
    }
    else{
      state++;
    };
    set_state();
  }
  else{  
    if (state == 1){
      state = 4;
    }
    else{
      state--;
    };
    set_state();
  };
};

