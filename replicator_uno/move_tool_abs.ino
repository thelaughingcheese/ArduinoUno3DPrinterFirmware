/*------------------------------
 moves tool to xyz absolute position
 xyz position specified as int32 with units in steps
 timing is specified as an unsigned int32 of microseconds of the duration of movment
 interpolation is done with basic  y=mx+b and z=nx+c
 ------------------------------*/

#define delay_comp 20

void move_tool_abs(int32_t _x, int32_t _y, int32_t _z, int32_t _a, uint32_t _del){
  int32_t _x_delt = _x - tool_x;
  int32_t _y_delt = _y - tool_y;
  int32_t _z_delt = _z - tool_z;
  int32_t _a_delt = _a - tool_a;
  
  float actual_ratio = 0;
  
  if(abs(_x_delt) >= abs(_y_delt) && abs(_x_delt) >= abs(_z_delt) && abs(_x_delt) >= abs(_a_delt)){        //linear interpolation for x as the max delta
    uint32_t _delay_per_step = _del/abs(_x_delt) - delay_comp;
    
    //mb data for y
    float _y_slope = ((float)_y_delt)/(_x_delt);
    int32_t _y_b = ((_y * _x_delt) - (_y_delt * _x))/_x_delt;
    int32_t _new_y = 0;
    
    //mb data for z
    float _z_slope = ((float)_z_delt)/(_x_delt);
    int32_t _z_b = ((_z * _x_delt) - (_z_delt * _x))/_x_delt;
    int32_t _new_z = 0;
    
    //mb data for a
    float _a_slope = ((float)_a_delt)/(_x_delt);
    int32_t _a_b = ((_a * _x_delt) - (_a_delt * _x))/_x_delt;;
    int32_t _new_a = 0;

    if(_x_delt > 0){
      for(int32_t i = 0; i < _x_delt; i++){
        stepper_x.make_step(true);
        tool_x++;
        
        //move y axis
        //_new_y = (_y_slope * tool_x)  + _y_b;
        _new_y = ((_y_delt * tool_x )+(_x_delt * _y_b))/_x_delt;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = ((_z_delt * tool_x )+(_x_delt * _z_b))/_x_delt;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = ((_a_delt * tool_x )+(_x_delt * _a_b))/_x_delt;
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_x - _x + _x_delt;
        step_delay(abs(_x_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 2);
        
        //step_delay(abs(_x_delt), abs(tool_x - _x + _x_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    }
    else{
      for(int32_t i = 0; i > _x_delt; i--){
        digitalWrite(5,HIGH);
        stepper_x.make_step(false);
        tool_x--;
        
        //move y axis
        _new_y = ((_y_delt * tool_x )+(_x_delt * _y_b))/_x_delt;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = ((_z_delt * tool_x )+(_x_delt * _z_b))/_x_delt;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = ((_a_delt * tool_x )+(_x_delt * _a_b))/_x_delt;
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_x - _x + _x_delt;
        step_delay(abs(_x_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 2);
        
        //step_delay(abs(_x_delt), abs(tool_x - _x + _x_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else if( abs(_y_delt) >= abs(_z_delt) && abs(_y_delt) >= abs(_a_delt) ){          //linear interpolation for y as the max delta
    uint32_t _delay_per_step = _del/abs(_y_delt) - delay_comp;
    
    //mbdata for x
    float _x_slope = ((float)_x_delt)/(_y_delt);
    int32_t _x_b = ((_x * _y_delt) - (_x_delt * _y))/_y_delt;
    int32_t _new_x = 0;
    
    //mb data for z
    float _z_slope = ((float)_z_delt)/(_y_delt);
    int32_t _z_b = ((_z * _y_delt) - (_z_delt * _y))/_y_delt;;
    int32_t _new_z = 0;

    //mb data for a
    float _a_slope = ((float)_a_delt)/(_y_delt);
    int32_t _a_b = ((_a * _y_delt) - (_a_delt * _y))/_y_delt;
    int32_t _new_a = 0;

    if(_y_delt > 0){
      for(int32_t i = 0; i < _y_delt; i++){
        stepper_y.make_step(true);
        tool_y++;
        
        //move x axis
        _new_x = ((_x_delt * tool_y )+(_y_delt * _x_b))/_y_delt;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move z axis
        _new_z = ((_z_delt * tool_y )+(_y_delt * _z_b))/_y_delt;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = ((_a_delt * tool_y )+(_y_delt * _a_b))/_y_delt;
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_y - _y + _y_delt;
        step_delay(abs(_y_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        
        //step_delay(abs(_y_delt), abs(tool_y - _y + _y_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
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
        _new_x = ((_x_delt * tool_y )+(_y_delt * _x_b))/_y_delt;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move z axis
        _new_z = ((_z_delt * tool_y )+(_y_delt * _z_b))/_y_delt;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = ((_a_delt * tool_y )+(_y_delt * _a_b))/_y_delt;
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_y - _y + _y_delt;
        step_delay(abs(_y_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        
        //step_delay(abs(_y_delt), abs(tool_y - _y + _y_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else if( abs(_z_delt) >= abs(_a_delt) ){                                                  //linear interpolation for z as the max delta
    uint32_t _delay_per_step = _del/abs(_z_delt) - delay_comp;
    
    //mbdata for x
    float _x_slope = ((float)_x_delt)/(_z_delt);
    int32_t _x_b = ((_x * _z_delt) - (_x_delt * _z))/_z_delt;
    int32_t _new_x = 0;
    
    //mbdata for y
    float _y_slope = ((float)_y_delt)/(_z_delt);
    int32_t _y_b = ((_y * _z_delt) - (_y_delt * _z))/_z_delt;
    int32_t _new_y = 0;

    //mbdata for a
    float _a_slope = ((float)_a_delt)/(_z_delt);
    int32_t _a_b = ((_a * _z_delt) - (_a_delt * _z))/_z_delt;
    int32_t _new_a = 0;

    if(_z_delt > 0){
      for(int32_t i = 0; i < _z_delt; i++){
        stepper_z.make_step(true);
        tool_z++;
        
        //move x axis
        _new_x = ((_x_delt * tool_z )+(_z_delt * _x_b))/_z_delt;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = ((_y_delt * tool_z )+(_z_delt * _y_b))/_z_delt;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move a axis
        _new_a = ((_a_delt * tool_z )+(_z_delt * _a_b))/_z_delt;
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_z - _z + _z_delt;
        step_delay(abs(_z_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        
        //step_delay(abs(_z_delt), abs(tool_z - _z + _z_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
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
        _new_x = ((_x_delt * tool_z )+(_z_delt * _x_b))/_z_delt;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = ((_y_delt * tool_z )+(_z_delt * _y_b))/_z_delt;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move a axis
        _new_a = ((_a_delt * tool_z )+(_z_delt * _a_b))/_z_delt;
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_a - _a + _a_delt;
        step_delay(abs(_a_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        
        //step_delay(abs(_z_delt), abs(tool_z - _z + _z_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else{                                              //linear interpolation for a axis as max delta
    uint32_t _delay_per_step = _del/abs(_a_delt) - delay_comp;
    
    //mbdata for x
    float _x_slope = ((float)_x_delt)/(_a_delt);
    int32_t _x_b = ((_x * _a_delt) - (_x_delt * _a))/_a_delt;
    int32_t _new_x = 0;
    
    //mbdata for y
    float _y_slope = ((float)_y_delt)/(_a_delt);
    int32_t _y_b = ((_y * _a_delt) - (_y_delt * _a))/_a_delt;
    int32_t _new_y = 0;

    //mbdata for z
    float _z_slope = ((float)_z_delt)/(_a_delt);
    int32_t _z_b = ((_z * _a_delt) - (_z_delt * _a))/_a_delt;
    int32_t _new_z = 0;

    if(_a_delt > 0){
      for(int32_t i = 0; i < _a_delt; i++){
        stepper_a.make_step(true);
        tool_a++;
        
        //move x axis
        _new_x = ((_x_delt * tool_a )+(_a_delt * _x_b))/_a_delt;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = ((_y_delt * tool_a )+(_a_delt * _y_b))/_a_delt;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = ((_z_delt * tool_a )+(_a_delt * _z_b))/_a_delt;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        int32_t _abs_cur_pos = tool_z - _z + _z_delt;
        step_delay(abs(_z_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        
        //step_delay(abs(_z_delt), abs(tool_z - _z + _z_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    }
    else{
      for(int32_t i = 0; i > _a_delt; i--){
        stepper_a.make_step(false);
        tool_a--;
        
        //move x axis
        _new_x = ((_x_delt * tool_a )+(_a_delt * _x_b))/_a_delt;
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = ((_y_delt * tool_a )+(_a_delt * _y_b))/_a_delt;
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = ((_z_delt * tool_a )+(_a_delt * _z_b))/_a_delt;
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        int32_t _abs_cur_pos = tool_a - _a + _a_delt;
        step_delay(abs(_a_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        
        //step_delay(abs(_z_delt), abs(tool_z - _z + _z_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    };
  };
  need_halt = false;
};

