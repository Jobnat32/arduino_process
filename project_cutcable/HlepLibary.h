#ifndef HelpLibary//ทำสิ่งที่คุณต้องการเมื่อ HelpLibary มีการใช้งาน
#define HelpLibary
// แหล่งการเรียก Libary ที่ใช่งานใน Program  และ file
// original arduino
#include <Arduino.h>
#include <typeinfo>
#include <stdio.h>

//file libary variable
#include "HelpGoble.h"

//keypad i2c
#include <Keypad_I2C.h>
#include <Keypad.h>

// LCD
#include <Wire.h>// key pad and LCD
#include <LiquidCrystal_I2C.h>

// file .h ที่สร้างขึ้น  keypad
#include "HelpKeypad.h"
#include "HelpEndcodder.h"
#include "HelpParamiter.h"
//file libary  
#include "HelpLCD.h"

#include "HelpProcessCut.h"
#include "HelpSelectMode.h"

//blynk 
#include "HelpBlynk.h"


#include "HelpCall.h"


#endif