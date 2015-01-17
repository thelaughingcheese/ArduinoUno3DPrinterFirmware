/*--------------------------
performs updates for everything per tick
mainly checks temperatures and new commands
--------------------------*/

void update_state(){
  check_s_buffer();
  update_extruder_temperature();
  //exe_actions();
  
  /*if(check_temp_counter == 200){
    update_extruder_temperature();
    check_temp_counter = 0;
  }
  else{
    check_temp_counter++;
  };*/
};

