/*--------------------------
performs updates for everything per tick
--------------------------*/

void update_state(){
  check_s_buffer();
  update_extruder_temperature();
};
