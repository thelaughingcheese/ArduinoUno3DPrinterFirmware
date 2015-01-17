/*--------------------------
circular buffer for actions
--------------------------*/

#include <Arduino.h>

class action_buffer{
public:
  action_buffer();
  void push(command_holder);
  command_holder pop();
  boolean is_full();

  command_holder *elements[8];
  uint8_t max_elements;
  uint8_t used_elements;
private:
  uint8_t cur_read_pos;
  void inc_read_pos();
  uint8_t find_next_pos();
};

action_buffer::action_buffer(){
  max_elements = 7;
  used_elements = 0;
  cur_read_pos = 0;
};

void action_buffer::push(command_holder _packet){
  elements[find_next_pos()] = new command_holder(_packet.load, _packet.a_size);
  used_elements++;
};

uint8_t action_buffer::find_next_pos(){ //--------------------------
  uint8_t raw_pos = cur_read_pos + used_elements - 1;
  if(raw_pos > max_elements){
    raw_pos = raw_pos - 8;
  };
  return raw_pos;
};

void action_buffer::inc_read_pos(){
  if(cur_read_pos == max_elements){
    cur_read_pos = 0;
  }
  else{
    cur_read_pos++;
  };
};

command_holder action_buffer::pop(){
  if(used_elements > 0){
    command_holder _temp = *elements[cur_read_pos];
    inc_read_pos();
    return _temp;
  };
};

boolean action_buffer::is_full(){
  return used_elements >= max_elements;
};
