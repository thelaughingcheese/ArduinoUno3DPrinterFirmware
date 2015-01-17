/*------------------
reads and handles action commands
------------------*/

void dispatch_action (command_holder _com) {
  switch(_com.load[0]){
    case (0x89):{ // power or unpower stepper axes, data ignored, returns success
      break;
    };
    case (0x88):{ // oh boy! switch inside a switch! tool action command, payload starts at index 4, command at 2
      switch(_com.load[2]){
        case (0x03):{ //set target temperature, payload is 16 bit uint of temperature, does nothing for now
    
          uint16_t _target = 0;
      
          for(int i = 0; i < 2;i++){    //read the 16 bit temperature
            uint32_t _tempz = _com.load[i + 4];
            _target = _target + (_tempz << (8 * i));
          };
          
          extruder_temp_target = (int)_target;
          break;
        };
        case (0x0A):{ //turn motor on/off, bottom 2 bits,bit 0 is on or off, bit 1 is direction
          break;
        };
        case (0x1F):{ //Set build platform temperature
          break;
        };
        case (0x04):{ //set PWM speed for motor
          break;
        };
        case (0x0C
        ):{ //toggle fan
          break;
        };
        
      };
      break;
    };
    case (0x8C):{ //set current position to the one specified, 20 byte payload, 4 bytes each axes, 5 axes in steps
      need_halt = false;
      
      uint32_t _xpos = 0;
      uint32_t _ypos = 0;
      uint32_t _zpos = 0;
      uint32_t _apos = 0;
      uint32_t _bpos = 0;
      
      for(int i = 0; i < 4;i++){    //convert from raw bytes to uint32 and cast to int32 later xyz
          uint32_t _tempz = _com.load[i + 1];
          _xpos = _xpos + (_tempz << (8 * i));
      };
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 5];
          _ypos = _ypos + (_tempz << (8 * i));
      };
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 9];
          _zpos = _zpos + (_tempz << (8 * i));
      };
      
      for(int i = 0; i < 4;i++){    //same as above ab
          uint32_t _tempz = _com.load[i + 13];
          _apos = _apos + (_tempz << (8 * i));
      };
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 17];
          _bpos = _bpos + (_tempz << (8 * i));
      };
      
      tool_x = (int32_t)_xpos;
      tool_y = (int32_t)_ypos;
      tool_z = (int32_t)_zpos;
      tool_a = (int32_t)_apos;

      break;
    };
    case(0x86):{ //change tool, only 1 tool so just acknowledge command

      break;
    };
    case(0x87):{ //wait for tool ready, supposed to poll tool,no tool so just acknowledge command when tool ready/hot enough
      while(false){ // supposed to keep checking
        delay(10);
      };
    
      break;
    };
    case(0x85):{ //delay, just sit there with your dick in your hand for that long
      uint32_t _del = 0;
      
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 1];
          _del = _del + (_tempz << (8 * i));
      };
      
      Serial.println(_del,DEC);
           
      delay((_del - (_del % 1000))/1000);
      if ((_del % 1000) > 0){
          delayMicroseconds(_del % 1000);
      };
    
      break;
    };
    case(0x84):{ //find axes Maximums and record to eeprom

      break;
    };
    case(0x8E):{ //queue an absolute point for print head to move to, return success uppon task finish
      uint32_t _xpos = 0;
      uint32_t _ypos = 0;
      uint32_t _zpos = 0;
      uint32_t _apos = 0;
      uint32_t _bpos = 0;
      uint32_t _del = 0;
      uint8_t _motion_flags = 0;
      
      for(int i = 0; i < 4;i++){    //convert from raw bytes to uint32 and cast to int32 later xyz
          uint32_t _tempz = _com.load[i + 1];
          _xpos = _xpos + (_tempz << (8 * i));
      };
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 5];
          _ypos = _ypos + (_tempz << (8 * i));
      };
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 9];
          _zpos = _zpos + (_tempz << (8 * i));
      };
      
      for(int i = 0; i < 4;i++){    //same as above ab
          uint32_t _tempz = _com.load[i + 13];
          _apos = _apos + (_tempz << (8 * i));
      };
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 17];
          _bpos = _bpos + (_tempz << (8 * i));
      };
      
      for(int i = 0; i < 4;i++){    //delay
          uint32_t _tempz = _com.load[i + 21];
          _del = _del + (_tempz << (8 * i));
      };
      
      _motion_flags = _com.load[25];
      
      //proccess relative data
      uint8_t _t_mf = _motion_flags << 7;
      if((_t_mf >> 7) == 1){
        _xpos = (uint32_t)((int32_t)_xpos + tool_x);
      };
      
      _t_mf = _motion_flags << 6;
      if((_t_mf >> 7) == 1){
        _ypos = (uint32_t)((int32_t)_ypos + tool_y);
      };
      
      _t_mf = _motion_flags << 5;
      if((_t_mf >> 7) == 1){
        _zpos = (uint32_t)((int32_t)_zpos + tool_z);
      };
      
      _t_mf = _motion_flags << 4;
      if((_t_mf >> 7) == 1){
        _apos = (uint32_t)((int32_t)_apos + tool_a);
      };
      
      
      //cast and pass data to move tool head
      move_tool_abs((int32_t)_xpos, (int32_t)_ypos, (int32_t)_zpos,(int32_t)_apos, _del);
      
      break;
    };
    case(0x83):{  //Find axis Minimums, decrease axis directions until endstops are hit for the requested axes
      uint8_t _axis_flags = 0; // _ _ _ B A Z Y X
      uint32_t _feed_rate = 0;
      uint16_t _timeout = 0;
      
      _axis_flags = _com.load[1];
      
      for(int i = 0; i < 4;i++){
          uint32_t _tempz = _com.load[i + 2];
          _feed_rate = _feed_rate + (_tempz << (8 * i));
      };
      
      for(int i = 0; i < 2;i++){
          uint32_t _tempz = _com.load[i + 6];
          _timeout = _timeout + (_tempz << (8 * i));
      };
      
      break;
    };
    case(0x90):{  //Recall home position from eeprom, just retruns success, supposed to find coords in eeprom and make the current position that coordinate

      break;
    };
    case(0x8D):{  //wait for build platform ready, just returns success

      break;
    };
    default:{
      uint8_t _resp[] = {0x85};
      send_packet( _resp,1 );
      break;
    };
  };
};

