/*--------------------------
checks extruder temperature and controls the heater
basic bang-bang control
--------------------------*/

void update_extruder_temperature(){
  extruder_temp = thermister_convert(analogRead(0));
  
  if(extruder_temp < extruder_temp_target){
    analogWrite(5,255);
  }
  else{
    analogWrite(5,150);
  };
};
