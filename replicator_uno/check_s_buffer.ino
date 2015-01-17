/*--------------------------
check the serial buffer for info
--------------------------*/

void check_s_buffer(){
  boolean is_errornous = false;

  if(Serial.available()){
    if(Serial.read() == 0xD5){
      wait_packet(is_errornous);//wait for next byte to send
      
      if(!is_errornous){
        working->a_size = Serial.read(); //find packet size in packet
        
        for(int i = 0; i < working->a_size; i++){ //read payload according to size
          wait_packet(is_errornous);
          if(is_errornous){
            break;
          };
          working->load[i] = Serial.read();
        };

        if(!is_errornous){
          wait_packet(is_errornous);//wait for next set of information
          if(!is_errornous){
            if(crc8(working->load, working->a_size) == Serial.read()){ //compare checksum to the current packet
           
              //--------------------------------------
              if(working->load[0] < 128){ //handles query commands
                dispatch_query(*working);
              }
              else{ //handles everything else: action commands
                if(buffered_action == NULL){  //buffer action if there isn't one already buffered
                  buffered_action = working;
                  working = spare;
                  
                  uint8_t _resp[] = {0x81};
                  send_packet(_resp,1);
                  return;
                }
                else{  //if there is aleady a command buffered then tell that to the host
                  uint8_t _resp[] = {0x82};
                  send_packet(_resp,1);
                  
                  return;
                };
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

      //clear 1 byte
      Serial.read();
      
      if(is_errornous){
        uint8_t _resp[] = {0x80};
        send_packet( _resp,1 );
      };
    }
    else{
      //used to clear entire buffer, instead just clear the one mismatched byte
      Serial.read();
      
      uint8_t _resp[] = {0x80};
      send_packet( _resp,1 );
    };
  };
};



