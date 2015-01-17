/*--------------------------
retains pointer to array of N bytes of packet data
retains uint8 of number of N bytes
--------------------------*/

#include <Arduino.h>

class command_holder{
public:
  command_holder();

  uint8_t load[32];
  uint8_t a_size;
};

command_holder::command_holder(){
  a_size = 0;
};
