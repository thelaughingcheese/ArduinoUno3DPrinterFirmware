/*------------------
0xD5 - start byte
0xNN - length of info in bytes
0xNN - payload
0xNN - CRC of the payload

payload formats:
  host commands:
    0xNN - command
    0xNN - Data
  responses:
    0xNN - response code
    0xNN - response data
------------------*/

void send_packet(uint8_t _payload[], uint8_t _size){
  uint8_t _data[3 + _size];
  
  _data[0] = 0xD5;
  _data[1] = _size;
  
  for(int i; i < _size; i++){
    _data[2 + i] = _payload[i];
  };
  
  _data[2 + _size] = crc8(_payload,_size);
  
  Serial.write(_data, 3 + _size);
  Serial.flush();
};

