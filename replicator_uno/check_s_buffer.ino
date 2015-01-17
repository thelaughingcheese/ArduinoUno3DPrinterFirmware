/*--------------------------
check the serial buffer for info
--------------------------*/

void check_s_buffer(){
  boolean is_errornous = false;
  
  if(Serial.available()){
    if(Serial.read() == 0xD5){
      wait_packet(is_errornous);//wait for next byte to send
      
      if(!is_errornous){
        uint8_t _size = Serial.read(); //find packet size in packet
        uint8_t _payload[_size];

        for(int i = 0; i < _size; i++){ //read payload according to size
          wait_packet(is_errornous);
          if(is_errornous){
            break;
          };
          _payload[i] = Serial.read();
        };
        if(!is_errornous){
          wait_packet(is_errornous);//wait for next set of information
          if(!is_errornous){
            if(crc8(_payload, _size) == Serial.read()){ //compare checksum to the current packet
            
              //--------------------------------------
            
              if(_payload[0] < 128){ //handles query commands
                //send_packet( ha,3 );
                command_holder _temp(_payload,_size);
                dispatch_query(_temp);
              }
              else{ //handles everything else: action commands
                ///*
                if(!is_busy){  //if isn't performing action then perform action
                  is_busy = true;
                  command_holder _temp(_payload,_size);
                  dispatch_action(_temp);
                  is_busy = false;
                }
                else{  //if busy tell replicatorg that the buffer is full (cuz there is no buffer)
                  uint8_t _resp[] = {
                    0x82        };
                  send_packet( _resp,1 );
                };
                //*/
                
                /*
                if(!a_buff.is_full()){
                  command_holder _temp(_payload,_size);
                  a_buff.push(_temp);
                }
                else{
                  uint8_t _resp[] = {0x82};
                  send_packet( _resp,1 );
                };
                */
                
              };
              
              //-------------------------------------
              
            }
            else{ //tell the computer it don't goofed
              uint8_t _resp[] = {0x83};
              send_packet( _resp,1 );
            };
          };
        };
      };

      //send_packet( ha,3 );
      
      //clear everything in the serial buffer incase there was an error
      while(Serial.available()){ //BAH! serial.flush was reppurposed in arduino 1.0 =[
        Serial.read();
      };
      
      if(is_errornous){
        uint8_t _resp[] = {0x80};
        send_packet( _resp,1 );
      };
    }
    else{
      while(Serial.available()){ //BAH! serial.flush was reppurposed in arduino 1.0 =[
        delayMicroseconds(500);
        Serial.read();
      };
      
      uint8_t _resp[] = {0x80};
      send_packet( _resp,1 );
    };
  };
};



