/*--------------------------
waits for a packet for a max amount of loops before it sends error code 0x80, generic error
--------------------------*/

void wait_packet(){
  for(int i = 0;i < 200;i++){
    if(Serial.available()){
      break;
    };
  };
  
  if(!Serial.available()){
    uint8_t _resp[] = {0x80};
    send_packet( _resp,1 );
  };
};
