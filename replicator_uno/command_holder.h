/*--------------------------
retains pointer to array of N bytes of packet data
retains uint8 of number of N bytes
--------------------------*/

#include <Arduino.h>

class command_holder{
public:
  command_holder(uint8_t[],uint8_t);

  uint8_t *load;
  uint8_t a_size;
};

command_holder::command_holder( uint8_t _arg[], uint8_t _size ){
  load = _arg;
  a_size = _size;
};



