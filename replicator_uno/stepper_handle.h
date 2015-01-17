/*--------------------------
holds info and controls stepping
--------------------------*/

#include <Arduino.h>

class stepper_handle{
private:
  int stepper_pin_1;
  int stepper_pin_2;
  void set_state();
  /*----------------
  1 - on on
  2 - on off
  3 - off off
  4 - off on
  ----------------*/
  int state;
  
public:
  stepper_handle(int,int);
  void make_step(boolean);
};

stepper_handle::stepper_handle( int _pin_1, int _pin_2 ){
  stepper_pin_1 = _pin_1;
  stepper_pin_2 = _pin_2;
  
  pinMode(_pin_1,OUTPUT);
  pinMode(_pin_2,OUTPUT);
  
  state = 1;
  set_state();
};

void stepper_handle::set_state(){
  switch(state){
    case(1):{
      digitalWrite(stepper_pin_1,HIGH);
      digitalWrite(stepper_pin_2,HIGH);
      break;
    };
    case(2):{
      digitalWrite(stepper_pin_1,HIGH);
      digitalWrite(stepper_pin_2,LOW);
      break;
    };
    case(3):{
      digitalWrite(stepper_pin_1,LOW);
      digitalWrite(stepper_pin_2,LOW);
      break;
    };
    case(4):{
      digitalWrite(stepper_pin_1,LOW);
      digitalWrite(stepper_pin_2,HIGH);
      break;
    };
  };
};

void stepper_handle::make_step( boolean _dir ){
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
