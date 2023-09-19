#ifndef HelpKeypad
#define HelpKeypad
#include "HlepLibary.h"


#define I2CADDR 0x20  // กำหนด Address ของ I2C
                      // วิธีการหา Address ของ I2C สามารถดูได้จากลิงค์ข้างล่าง 
                      // https://www.myarduino.net/article/98

const byte ROWS = 4;  // กำหนดจำนวนของ Rows
const byte COLS = 4;  // กำหนดจำนวนของ Columns

// กำหนด Key ที่ใช้งาน (4x4)
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// กำหนด Pin ที่ใช้งาน (4x4)
byte rowPins[ROWS] = {0, 1, 2, 3}; // เชื่อมต่อกับ Pin แถวของปุ่มกด
byte colPins[COLS] = {4, 5, 6, 7}; // เชื่อมต่อกับ Pin คอลัมน์ของปุ่มกด

// makeKeymap(keys) : กำหนด Keymap
// rowPins : กำหนด Pin แถวของปุ่มกด
// colPins : กำหนด Pin คอลัมน์ของปุ่มกด
// ROWS : กำหนดจำนวนของ Rows
// COLS : กำหนดจำนวนของ Columns
// I2CADDR : กำหนด Address ขอ i2C
// PCF8574 : กำหนดเบอร์ IC
Keypad_I2C keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574 );

void setup_key(){
  Wire.begin();  // เรียกการเชื่อมต่อ Wire
  keypad.begin( makeKeymap(keys) );  // เรียกกาเชื่อมต่อ


}


char key_pad(){
  char key = keypad.getKey();  // สร้างตัวแปรชื่อ key ชนิด char เพื่อเก็บตัวอักขระที่กด
Serial.println(key);
Serial.println("key pad");

  if (key){  // ถ้าหากตัวแปร key มีอักขระ
   //Serial.print("key.h : ");
   // Serial.println(key);
   value_keypad = key;
   
   } 
   else{
   value_keypad = ' '; 
   }
   //Serial.print(value_keypad);
return value_keypad; //ส่งค่าไปตัวที่เรียกใช่
 
}

#endif