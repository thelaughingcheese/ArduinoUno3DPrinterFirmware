/*------------------
properly calculates and makes a delay between each step to ensure proper acceleration

finish moving variables
------------------*/

void step_delay(int32_t _travel_dist,int32_t _cur_pos,float _target_dt, float& speed_ratio, int _delay_mult){
  /*
  
  float actual_ratio = 0;

  if(_cur_pos < _travel_dist/2){
    speed_ratio += accleration_factor;
  }
  else if(_cur_pos > _travel_dist/2 && _cur_pos > _travel_dist-(speed_ratio/accleration_factor)){
    speed_ratio -= accleration_factor;
  };
  
  actual_ratio = 1/constrain(speed_ratio,max_step_delay,1/_target_dt);
  
  */
  
  //step_delay_micro(0);

  /*
  if(_travel_dist < 6){
    step_delay_micro(_target_dt);
  }
  else{
    //step_delay_micro((unsigned long)actual_ratio * _delay_mult);
  };
  */
  
  step_delay_micro(_target_dt);
};
