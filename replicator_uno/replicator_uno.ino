/************************************************
Version 0.5
-int32_t's in move_tool_abs now uses integer math to avoid long floating point calculations and to increase acurracy
-step_delay doesnt uses acceleration unless more than 10 steps, other wise rounding errors cause no delay and the motor skips steps
-host software requires modifications to fix com bugs
-checks thermistor temperatures less frequently

todo:
-homing and endstops
-buffer
-find real eeprom layout

for version 0.5 and on
-new acceleration
-PID heat controller - may not be nessesary
-maybe lcd and i2c support for multi-core control
-microsecond stepper delay compensation

EEPROM format:
0-127 makerbot based config data
  0-15
    0  character x, unknown purpose
    1  character y, unknown purpose
    2-15  unknown purpose
  16-31
    16-23 8 byte/character ascii name
    24-31 unknown purpose
  32-47 unknown purpose
  48-63 unknown purpose
  64-79 unknown purpose
  80-95 unknown purpose
  96-111 unknown purpose
  112-128 unknown purpose
128-1023 blank data 0xFF

pins:
digital
0 - serial
1 - serial
2 - 
3 - 
4 - 
5 - extruder heater control
6 - a
7 - a
8 - z
9 - z
10 - y
11 - y
12 - x
13 - x

analog
0 - thermister
1 - 
2 - 
3 - 
4 - i2c
5 - i2c
************************************************/

/*-------------------
main loop, setup and global variables
-------------------*/

#define BAUD 57600

#include "command_holder.h"
#include "stepper_handle.h"
#include "action_buffer.h"
#include <EEPROM.h>
#include <MemoryFree.h>
//#include <util/setbaud.h>

uint8_t ha[] = {0x81,0x4e,0x4f}; //hacky testing and debugging load

#define firmware_version 0.01 * 100  // a bunch of version and name data
const char firmware_name[] = {'u','n','o',' ','e','m','u','l','a','t','i','o','n','\0'};
#define firmware_name_size 14
const char tool_name[] = {'e','m','u','l','a','t','e','d',' ','t','o','o','l','\0'};
#define tool_name_size 14

//setup tool data
int32_t tool_x = 0;
int32_t tool_y = 0;
int32_t tool_z = 0;
int32_t tool_a = 0;

int extruder_temp = 0;
int extruder_temp_target = 0;
int check_temp_counter = 0;

//create handlers for steppers
stepper_handle stepper_x(13,12);
stepper_handle stepper_y(11,10);
stepper_handle stepper_z(9,8);
stepper_handle stepper_a(7,6);

//statuses
boolean is_busy = false;
boolean need_halt = false;

//acceleration constants
const float accleration_factor = 0.000005;
const float max_step_delay = 1/2000;

//action buffer
//action_buffer a_buff;

void setup(){
  Serial.begin(BAUD);
  
  /*UBRR0H = UBRRH_VALUE;  //search lightweight and fast gcode printing
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
  UCSR0A |= _BV(U2X0);
  #else
  UCSR0A &= ~_BV(U2X0);
  #endif*/
  
  //Serial.begin(921600);
  /*uint8_t lol[]={0x85,0x00,0xDB,0x00,0xE7};
  Serial.write(crc8( lol, 0x05));
  pinMode(13,OUTPUT);*/
  
  Serial.print(0xD5);
  Serial.print(0x01);
  Serial.print(0x81);
  Serial.print(0xD2);
  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
};

void loop(){
  /*if(Serial.available()){
    send_packet( ha,3 );
    Serial.flush();
  };*/
  
  //check serial buffer for commands, varify them, sort them, append them
  //while(Serial.available()){
    update_state();
  //};
  //buffer not implimented
  //check query_buffer for commands that need to be handled immidiately
  //printing and what not, main stuff
  //Serial.println(freeMemory());
};
