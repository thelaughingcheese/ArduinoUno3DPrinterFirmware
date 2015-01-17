/*------------------
reads and handles query commands
------------------*/

void dispatch_query (command_holder _com) {
  switch(_com.load[0]){
    case (0x00):{
      uint8_t _resp[3];
      _resp[2] = byte((word)firmware_version >> 8);
      _resp[1] = byte(firmware_version);
      _resp[0] = 0x81;
      send_packet( _resp,3 );
      break;
    };
    case (0x01):{ //INIT HERE THIS IS TEMP, set head pos to 0, clear command buff, set eeprom val
      uint8_t _resp[] = {0x81};
      send_packet( _resp,1 );
      break;
    };
    case (0x07):{ // stop print
      need_halt = true;
      
      uint8_t _resp[] = {0x81};
      send_packet( _resp,1 );
      break;
    };
    case (0x08):{  //pause/unpause
      uint8_t _resp[] = {0x81};
      send_packet( _resp,1 );
      break;
    };
    case (0x0A):{ // tool query
      switch(_com.load[2]){
        case (0x00):{
          uint8_t _resp[3];
          _resp[2] = byte((word)firmware_version >> 8);
          _resp[1] = byte(firmware_version);
          _resp[0] = 0x81;
          send_packet( _resp,3 );
          break;
        };
        case (0x22):{
          uint8_t _resp[1+tool_name_size];
          _resp[0] = 0x81;
      
          for(int i = 0; i < tool_name_size; i++){
            _resp[i+1] = tool_name[i];
          }
      
          send_packet( _resp,1+firmware_name_size );
          break;
        };
        case (0x02):{ //Return tool temperature
          uint8_t _resp[3];
          
          _resp[0] = 0x81;
          _resp[1] = byte(extruder_temp);
          _resp[2] = byte(extruder_temp >> 8);
      
          send_packet( _resp,3 );
          break;
        };
        case (0x03):{ //Set Tool temperature
          uint8_t _resp[] = {0x81};
          uint16_t _target = 0;
      
          for(int i = 0; i < 2;i++){    //read the 16 bit tenperature
            uint32_t _tempz = _com.load[i + 3];
            _target = _target + (_tempz << (8 * i));
          };
          
          extruder_temp_target = (int)_target;
      
          send_packet( _resp,1);
          break;
        };
        case (0x1E):{ //Return build platform temperature, we lie here too until we have a tool
          uint8_t _resp[3];
          
          _resp[0] = 0x81;
          _resp[1] = 0xc8;
          _resp[2] = 0x00;
      
          send_packet( _resp,3 );
          break;
        };
        default:{
          uint8_t _resp[] = {0x85};
          send_packet( _resp,1 );
          break;
        };
      };
      break;
    };
    case (0x0B):{ // ask if the machine is working, 0 for working, 1 for doing nothing, we lie and respond 1
      uint8_t _resp[2];
      
      _resp[0] = 0x81;
      
      if(is_busy){
        _resp[1] = 0x00;
      }
      else{
        _resp[1] = 0x01;
      };
      
      send_packet( _resp,2 );
      break;
    };
    case (0x0C):{ //reading from eeprom!
      uint8_t _resp[1+_com.load[3]];
      uint16_t _offset = 0;
      
      for(int i = 0; i < 2;i++){    //read the 16 bit offset
          uint32_t _tempz = _com.load[i + 1];
          _offset = _offset + (_tempz << (8 * i));
      };
      
      _resp[0] = 0x81;
      for(uint8_t i = 0; i < _com.load[3];i++){
        _resp[i+1] = (uint8_t)EEPROM.read(_offset + (int)i);
      };
      
      send_packet( _resp,1+_com.load[3] );
      break;
    };
    case (0x0D):{ //write to eeprom uint16 of off set, uint8 of length of data, N bytes of the data, this is TEMPERARY, it lies to replicator-g for now
      uint16_t _offset = 0;  //init and read packet and response
      uint8_t _length = _com.load[3];
      //uint8_t _data[_length];
      
      for(int i = 0; i < 2;i++){    //read the 16 bit offset
         uint32_t _tempz = _com.load[i + 1];
         _offset = _offset + (_tempz << (8 * i));
      };
       
      uint8_t _resp[2];

      _resp[0] = 0x81;
      _resp[1] = _length;
      
      //actually write data
      for(int i = 0; i < _length; i++){
        EEPROM.write((int)_offset + i,byte(_com.load[4 + i]));
      };

      send_packet( _resp,2 );
      break;
    };
    case (0x14):{  //get firmware build name
      uint8_t _resp[1+firmware_name_size];
      _resp[0] = 0x81;
      
      for(int i = 0; i < firmware_name_size; i++){
        _resp[i+1] = firmware_name[i];
      }
      
      send_packet( _resp,1+firmware_name_size );
      break;
    };
    case (0x15):{ // get extended position of all axes
      uint8_t _resp[23];
      
      _resp[0] = 0x81;
      for(int i = 0; i < 4; i++){
        _resp[i+1] = byte((uint32_t)tool_x >> (8*i));
      }
      for(int i = 0; i < 4; i++){
        _resp[i+5] = byte((uint32_t)tool_y >> (8*i));
      }
      for(int i = 0; i < 4; i++){
        _resp[i+9] = byte((uint32_t)tool_z >> (8*i));
      }
      
      for(int i = 0; i < 8; i++){//axis a and b, lies
        _resp[i+13] = 0x00;
      }
      
      for(int i = 0; i < 2; i++){
        _resp[i+21] = 0x00;
      }
      
      send_packet( _resp,22 );
      break;
    };
    case (0x19):{ //build end notification
      uint8_t _resp[] = {0x81};
      send_packet( _resp,1 );
      break;
    };
    default:{
      uint8_t _resp[] = {0x85};
      send_packet( _resp,1 );
      break;
    };
  };
};

