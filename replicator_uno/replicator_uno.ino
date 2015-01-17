/************************************************
Version 0.2
-communicates with replicatorg
-only performs absolute positioning
-linear, must finish one instruction at a time, query commands are NOT prioritized
-no stop command implemented
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
  while(Serial.available()){
    if(Serial.read() == 0xD5){
      while(!Serial.available()){ //wait for next byte to send
      }
      
      uint8_t _size = Serial.read(); //find packet size in packet
      uint8_t _payload[_size];
      
      for(int i = 0; i < _size; i++){ //read payload according to size
        while(!Serial.available()){
        }
        _payload[i] = Serial.read();
      };
      
      while(!Serial.available()){ //wait for next set of information
      }
      
      if(crc8(_payload, _size) == Serial.read()){ //compare checksum to the current packet
        if(_payload[0] < 128){ //handles query commands
          //send_packet( ha,3 );
          command_holder _temp(_payload,_size);
          dispatch_query(_temp);
        }
        else{ //handles everything else: action commands
          command_holder _temp(_payload,_size);
          dispatch_action(_temp);
        };
      }
      else{ //tell the computer it don't goofed
        uint8_t _resp[] = {0x83};
        send_packet( _resp,1 );
      };
      
      //send_packet( ha,3 );
    };
  };
  //buffer not implimented
  //check query_buffer for commands that need to be handled immidiately
  //printing and what not, main stuff
};
