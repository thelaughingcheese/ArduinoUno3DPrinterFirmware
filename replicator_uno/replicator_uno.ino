/************************************************
Version 0.3
-communicates with replicatorg
-only performs absolute positioning
-no buffer yet
-all query commands are instantly proccessed
-queue extended point now instantly responds with success so that it does not clog up the serial buffer
-if is performing a action, the machine responds with "buffer full"
-now supports stop command
************************************************/

/*-------------------
main loop, setup and global variables
-------------------*/

#include "command_holder.h"
#include "stepper_handle.h"
#include <EEPROM.h>

uint8_t ha[] = {0x81,0x4e,0x4f}; //hacky testing and debugging load

#define firmware_version 0.01 * 100  // a bunch of version and name data
const char firmware_name[] = {'u','n','o',' ','e','m','u','l','a','t','i','o','n','\0'};
#define firmware_name_size 14
const char tool_name[] = {'e','m','u','l','a','t','e','d',' ','t','o','o','l','\0'};
#define tool_name_size 14

//setup tool position
int32_t tool_x = 0;
int32_t tool_y = 0;
int32_t tool_z = 0;

//create handlers for steppers
stepper_handle stepper_x(13,12);
stepper_handle stepper_y(11,10);
stepper_handle stepper_z(9,8);

//statuses
boolean is_busy = false;
boolean need_halt = false;

void setup(){
  //Serial.begin(115200);
  Serial.begin(460800);
  /*uint8_t lol[]={0x85,0x00,0xDB,0x00,0xE7};
  Serial.write(crc8( lol, 0x05));
  pinMode(13,OUTPUT);*/
};

void loop(){
  /*if(Serial.available()){
    send_packet( ha,3 );
    Serial.flush();
  };*/
  
  //check serial buffer for commands, varify them, sort them, append them
  //while(Serial.available()){
    check_s_buffer();
  //};
  //buffer not implimented
  //check query_buffer for commands that need to be handled immidiately
  //printing and what not, main stuff
};
