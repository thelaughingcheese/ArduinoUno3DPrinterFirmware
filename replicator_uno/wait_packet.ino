/*--------------------------
waits for a packet for a max amount of loops before it sends error code 0x80, generic error
--------------------------*/

void wait_packet(boolean& _error){
  for(int i = 0;i < 10000;i++){
    if(Serial.available()){
      break;
    };
  };
  
  if(!Serial.available()){
    uint8_t _resp[] = {0x80};
    send_packet( _resp,1 );
    _error = true;
  };
};

