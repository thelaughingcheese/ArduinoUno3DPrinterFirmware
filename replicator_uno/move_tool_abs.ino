/*------------------------------
 moves tool to xyz absolute position
 xyz position specified as int32 with units in steps
 timing is specified as an unsigned int32 of microseconds of the duration of movment
 interpolation is done with basic  y=mx+b and z=nx+c
 ------------------------------*/

void move_tool_abs(int32_t _x, int32_t _y, int32_t _z, uint32_t _del){
  int32_t _x_delt = _x - tool_x;
  int32_t _y_delt = _y - tool_y;
  int32_t _z_delt = _z - tool_z;
  
  if(abs(_x_delt) >= abs(_y_delt) && abs(_x_delt) >= abs(_z_delt)){        //linear interpolation for x as the max delta
    uint32_t _delay_per_step = _del/abs(_x_delt);
    
    //mb data for y
    float _y_slope = (_y_delt)/(_x_delt);
    int32_t _y_b = _y - (_y_slope * _x);
    int32_t _new_y = 0;
    
    //mb data for z
    float _z_slope = (_z_delt)/(_x_delt);
    int32_t _z_b = _z - (_z_slope * _x);
    int32_t _new_z = 0;

    if(_x_delt > 0){
      for(int32_t i = 0; i < _x_delt; i++){
        stepper_x.make_step(true);
        tool_x++;
        
        //move y axis
        _new_y = (_y_slope * tool_x)  + _y_b;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = (_z_slope * tool_x)  + _z_b;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        delay((_delay_per_step - (_delay_per_step % 1000))/1000);
        if ((_delay_per_step % 1000) > 0){
          delayMicroseconds(_delay_per_step % 1000);
        };
        
        check_s_buffer();
        
        if(need_halt){
          break;
        };
      };
    }
    else{
      for(int32_t i = 0; i > _x_delt; i--){
        stepper_x.make_step(false);
        tool_x--;
        
        //move y axis
        _new_y = (_y_slope * tool_x)  + _y_b;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = (_z_slope * tool_x)  + _z_b;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        delay((_delay_per_step - (_delay_per_step % 1000))/1000);
        if ((_delay_per_step % 1000) > 0){
          delayMicroseconds(_delay_per_step % 1000);
        };
        
        check_s_buffer();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else if( abs(_y_delt) >= abs(_z_delt) ){          //linear interpolation for y as the max delta
    uint32_t _delay_per_step = _del/abs(_y_delt);
    
    //mbdata for x
    float _x_slope = (_x_delt)/(_y_delt);
    int32_t _x_b = _x - (_x_slope * _y);
    int32_t _new_x = 0;
    
    //mb data for z
    float _z_slope = (_z_delt)/(_y_delt);
    int32_t _z_b = _z - (_z_slope * _y);
    int32_t _new_z = 0;

    if(_y_delt > 0){
      for(int32_t i = 0; i < _y_delt; i++){
        stepper_y.make_step(true);
        tool_y++;
        
        //move x axis
        _new_x = (_x_slope * tool_y)  + _x_b;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move z axis
        _new_z = (_z_slope * tool_y)  + _z_b;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        delay((_delay_per_step - (_delay_per_step % 1000))/1000);
        if ((_delay_per_step % 1000) > 0){
          delayMicroseconds(_delay_per_step % 1000);
        };
        
        check_s_buffer();
        
        if(need_halt){
          break;
        };
      };
    }
    else{
      for(int32_t i = 0; i > _y_delt; i--){
        stepper_y.make_step(false);
        tool_y--;
        
        //move x axis
        _new_x = (_x_slope * tool_y)  + _x_b;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move z axis
        _new_z = (_z_slope * tool_y)  + _z_b;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        delay((_delay_per_step - (_delay_per_step % 1000))/1000);
        if ((_delay_per_step % 1000) > 0){
          delayMicroseconds(_delay_per_step % 1000);
        };
        
        check_s_buffer();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else{                                                  //linear interpolation for z as the max delta
    uint32_t _delay_per_step = _del/abs(_z_delt);
    
    //mbdata for x
    float _x_slope = (_x_delt)/(_z_delt);
    int32_t _x_b = _x - (_x_slope * _z);
    int32_t _new_x = 0;
    
    //mbdata for y
    float _y_slope = (_y_delt)/(_z_delt);
    int32_t _y_b = _x - (_x_slope * _z);
    int32_t _new_y = 0;

    if(_z_delt > 0){
      for(int32_t i = 0; i < _z_delt; i++){
        stepper_z.make_step(true);
        tool_z++;
        
        //move x axis
        _new_x = (_x_slope * tool_z)  + _x_b;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = (_y_slope * tool_z)  + _y_b;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        delay((_delay_per_step - (_delay_per_step % 1000))/1000);
        if ((_delay_per_step % 1000) > 0){
          delayMicroseconds(_delay_per_step % 1000);
        };
        
        check_s_buffer();
        
        if(need_halt){
          break;
        };
      };
    }
    else{
      for(int32_t i = 0; i > _z_delt; i--){
        stepper_z.make_step(false);
        tool_z--;
        
        //move x axis
        _new_x = (_x_slope * tool_z)  + _x_b;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = (_y_slope * tool_z)  + _y_b;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        delay((_delay_per_step - (_delay_per_step % 1000))/1000);
        if ((_delay_per_step % 1000) > 0){
          delayMicroseconds(_delay_per_step % 1000);
        };
        
        check_s_buffer();
        
        if(need_halt){
          break;
        };
      };
    };
  };
  need_halt = false;
};

