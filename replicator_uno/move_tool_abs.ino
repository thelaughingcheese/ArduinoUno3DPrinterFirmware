/*------------------------------
 moves tool to xyz absolute position
 xyz position specified as int32 with units in steps
 timing is specified as an unsigned int32 of microseconds of the duration of movment
 interpolation is done with basic  y=mx+b and z=nx+c
 ------------------------------*/
 
//fixed decimal only supports numbers < 0
#define FIXED_FROM_FLOAT(a) (int16_t)((a)*((int16_t)1<<14));
#define FIXED_MUL_INT(a,b) (int32_t)(((a)*(b)) >> 14);

#define delay_comp 30

void move_tool_abs(int32_t _x, int32_t _y, int32_t _z, int32_t _a, uint32_t _del){
  int32_t _x_delt = _x - tool_x;
  int32_t _y_delt = _y - tool_y;
  int32_t _z_delt = _z - tool_z;
  int32_t _a_delt = _a - tool_a;
  
  int32_t _x_start = tool_x;
  int32_t _y_start = tool_y;
  int32_t _z_start = tool_z;
  int32_t _a_start = tool_a;
  
  //float actual_ratio = 0;
  
  if(abs(_x_delt) >= abs(_y_delt) && abs(_x_delt) >= abs(_z_delt) && abs(_x_delt) >= abs(_a_delt)){        //linear interpolation for x as the max delta
    int32_t _delay_per_step = _del/abs(_x_delt) - delay_comp;
    
    //mb data for y
    float _y_slope_f = ((float)_y_delt)/(_x_delt);
    int16_t _y_slope = FIXED_FROM_FLOAT(_y_slope_f);
    int32_t _new_y = 0;
    
    //mb data for z
    float _z_slope_f = ((float)_z_delt)/(_x_delt);
    int16_t _z_slope = FIXED_FROM_FLOAT(_z_slope_f);
    int32_t _new_z = 0;
    
    //mb data for a
    float _a_slope_f = ((float)_a_delt)/(_x_delt);
    int16_t _a_slope = FIXED_FROM_FLOAT(_a_slope_f);
    int32_t _new_a = 0;

    if(_x_delt > 0){
      for(int32_t i = 0; i < _x_delt; i++){
        stepper_x.make_step(true);
        tool_x++;
        int32_t _local_x = tool_x-_x_start;
        
        //move y axis
        //_new_y = (_y_slope * tool_x)  + _y_b;
        _new_y = _y_start + FIXED_MUL_INT(_y_slope,_local_x);
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = _z_start + FIXED_MUL_INT(_z_slope,_local_x);
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = _a_start + FIXED_MUL_INT(_a_slope,_local_x);
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_x - _x + _x_delt;
        //step_delay(abs(_x_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 2);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
        //step_delay(abs(_x_delt), abs(tool_x - _x + _x_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    }
    else{
      for(int32_t i = 0; i > _x_delt; i--){
        stepper_x.make_step(false);
        tool_x--;
        int32_t _local_x = tool_x-_x_start;
        
        //move y axis
        _new_y = _y_start + FIXED_MUL_INT(_y_slope,_local_x);
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = _z_start + FIXED_MUL_INT(_z_slope,_local_x);
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = _a_start + FIXED_MUL_INT(_a_slope,_local_x);
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_x - _x + _x_delt;
        //step_delay(abs(_x_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 2);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
        //step_delay(abs(_x_delt), abs(tool_x - _x + _x_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else if( abs(_y_delt) >= abs(_z_delt) && abs(_y_delt) >= abs(_a_delt) ){          //linear interpolation for y as the max delta
    int32_t _delay_per_step = _del/abs(_y_delt) - delay_comp;

    //mbdata for x
    float _x_slope_f = ((float)_x_delt)/(_y_delt);
    int16_t _x_slope = FIXED_FROM_FLOAT(_x_slope_f);
    int32_t _new_x = 0;
    
    //mb data for z
    float _z_slope_f = ((float)_z_delt)/(_y_delt);
    int16_t _z_slope = FIXED_FROM_FLOAT(_z_slope_f);
    int32_t _new_z = 0;

    //mb data for a
    float _a_slope_f = ((float)_a_delt)/(_y_delt);
    int16_t _a_slope = FIXED_FROM_FLOAT(_a_slope_f);
    int32_t _new_a = 0;

    if(_y_delt > 0){
      for(int32_t i = 0; i < _y_delt; i++){
        stepper_y.make_step(true);
        tool_y++;
        int32_t _local_y = tool_y-_y_start;
        
        //move x axis
        _new_x = _x_start + FIXED_MUL_INT(_x_slope,_local_y);
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move z axis
        _new_z = _z_start + FIXED_MUL_INT(_z_slope,_local_y);
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = _a_start + FIXED_MUL_INT(_a_slope,_local_y);
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
       
        int32_t _abs_cur_pos = tool_y - _y + _y_delt;
        //step_delay(abs(_y_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
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
        int32_t _local_y = tool_y-_y_start;
        
        //move x axis
        _new_x = _x_start + FIXED_MUL_INT(_x_slope,_local_y);
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move z axis
        _new_z = _z_start + FIXED_MUL_INT(_z_slope,_local_y);
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        //move a axis
        _new_a = _a_start + FIXED_MUL_INT(_a_slope,_local_y);
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_y - _y + _y_delt;
        //step_delay(abs(_y_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
        //step_delay(abs(_y_delt), abs(tool_y - _y + _y_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else if( abs(_z_delt) >= abs(_a_delt) ){                                                  //linear interpolation for z as the max delta
    int32_t _delay_per_step = _del/abs(_z_delt) - delay_comp;
    
    //mbdata for x
    float _x_slope_f = ((float)_x_delt)/(_z_delt);
    int16_t _x_slope = FIXED_FROM_FLOAT(_x_slope_f);
    int32_t _new_x = 0;
    
    //mbdata for y
    float _y_slope_f = ((float)_y_delt)/(_z_delt);
    int16_t _y_slope = FIXED_FROM_FLOAT(_y_slope_f);
    int32_t _new_y = 0;

    //mbdata for a
    float _a_slope_f = ((float)_a_delt)/(_z_delt);
    int16_t _a_slope = FIXED_FROM_FLOAT(_a_slope_f);
    int32_t _new_a = 0;

    if(_z_delt > 0){
      for(int32_t i = 0; i < _z_delt; i++){
        stepper_z.make_step(true);
        tool_z++;
        int32_t _local_z = tool_z-_z_start;
        
        //move x axis
        _new_x = _x_start + FIXED_MUL_INT(_x_slope,_local_z);
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = _y_start + FIXED_MUL_INT(_y_slope,_local_z);
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move a axis
        _new_a = _a_start + FIXED_MUL_INT(_a_slope,_local_z);
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_z - _z + _z_delt;
        //step_delay(abs(_z_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
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
        int32_t _local_z = tool_z-_z_start;
        
        //move x axis
        _new_x = _x_start + FIXED_MUL_INT(_x_slope,_local_z);
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = _y_start + FIXED_MUL_INT(_y_slope,_local_z);
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move a axis
        _new_a = _a_start + FIXED_MUL_INT(_a_slope,_local_z);
        if(_new_a > tool_a){
          stepper_a.make_step(true);
          tool_a++;
        }
        else if(_new_a < tool_a){
          stepper_a.make_step(false);
          tool_a--;
        };
        
        int32_t _abs_cur_pos = tool_a - _a + _a_delt;
        //step_delay(abs(_a_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
        //step_delay(abs(_z_delt), abs(tool_z - _z + _z_delt), _delay_per_step, actual_ratio);
        
        update_state();
        
        if(need_halt){
          break;
        };
      };
    };
  }
  else{                                              //linear interpolation for a axis as max delta
    int32_t _delay_per_step = _del/abs(_a_delt) - delay_comp;
    
    //mbdata for x
    float _x_slope_f = ((float)_x_delt)/(_a_delt);
    int16_t _x_slope = FIXED_FROM_FLOAT(_x_slope_f);
    int32_t _new_x = 0;
    
    //mbdata for y
    float _y_slope_f = ((float)_y_delt)/(_a_delt);
    int16_t _y_slope = FIXED_FROM_FLOAT(_y_slope_f);
    int32_t _new_y = 0;

    //mbdata for z
    float _z_slope_f = ((float)_z_delt)/(_a_delt);
    int16_t _z_slope = FIXED_FROM_FLOAT(_z_slope_f);
    int32_t _new_z = 0;

    if(_a_delt > 0){
      for(int32_t i = 0; i < _a_delt; i++){
        stepper_a.make_step(true);
        tool_a++;
        int32_t _local_a = tool_a-_a_start;
        
        //move x axis
        _new_x = _x_start + FIXED_MUL_INT(_x_slope,_local_a);
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = _y_start + FIXED_MUL_INT(_y_slope,_local_a);
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = _z_start + FIXED_MUL_INT(_z_slope,_local_a);
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        int32_t _abs_cur_pos = tool_z - _z + _z_delt;
        //step_delay(abs(_z_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
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
        int32_t _local_a = tool_a-_a_start;
        
        //move x axis
        _new_x = _x_start + FIXED_MUL_INT(_x_slope,_local_a);
        if(_new_x > tool_x){
          stepper_x.make_step(true);
          tool_x++;
        }
        else if(_new_x < tool_x){
          stepper_x.make_step(false);
          tool_x--;
        };
        
        //move y axis
        _new_y = _y_start + FIXED_MUL_INT(_y_slope,_local_a);
        if(_new_y > tool_y){
          stepper_y.make_step(true);
          tool_y++;
        }
        else if(_new_y < tool_y){
          stepper_y.make_step(false);
          tool_y--;
        };
        
        //move z axis
        _new_z = _z_start + FIXED_MUL_INT(_z_slope,_local_a);
        if(_new_z > tool_z){
          stepper_z.make_step(true);
          tool_z++;
        }
        else if(_new_z < tool_z){
          stepper_z.make_step(false);
          tool_z--;
        };
        
        int32_t _abs_cur_pos = tool_a - _a + _a_delt;
        //step_delay(abs(_a_delt), abs(_abs_cur_pos), _delay_per_step, actual_ratio, 1);
        step_delay_micro(max(_delay_per_step-delay_comp,0));
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

