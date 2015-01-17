/************************************************
Version 0.6
-now has single command buffer, needs testing
-faster digital write

todo:
-homing and endstops
-find real eeprom layout

for version 0.5 and on
-new acceleration, maybe
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

#define BAUD 115200

#include "command_holder.h"
#include "stepper_handle.h"
#include <EEPROM.h>
//#include <MemoryFree.h>
//#include <util/setbaud.h>

/*
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//lcd.println("pre pass move");
*/

uint8_t ha[] = {0x81,0x4e,0x4f}; //hacky testing and debugging load

#define firmware_version 0.06 * 100  // a bunch of version and name data
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
stepper_handle stepper_x(13,12,0);
stepper_handle stepper_y(11,10,0);
stepper_handle stepper_z(9,8,1);
stepper_handle stepper_a(7,6,1);

//statuses
boolean is_busy = false;
boolean need_halt = false;

//acceleration constants
const float accleration_factor = 0.000005;
const float max_step_delay = 1/2000;

//command buffers
command_holder* working = new command_holder();
command_holder* spare = new command_holder();
command_holder* curAction = new command_holder();
command_holder* buffered_action = NULL;

void setup(){
  Serial.begin(BAUD);
 
  //debug
  Serial.print(0xD5);
  Serial.print(0x01);
  Serial.print(0x81);
  Serial.print(0xD2);
  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  
  //lcd
  //lcd.begin(16,2);
  //lcd.print("Begin");
};

void loop(){
  update_state();
  exe_actions();
};
