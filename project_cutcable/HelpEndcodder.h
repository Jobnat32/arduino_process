#ifndef HelpEndcodder//ทำสิ่งที่คุณต้องการเมื่อ HelpEndcodder มีการใช้งาน
#define HelpEndcodder
#include <stdio.h>
#include "HlepLibary.h"


// library Rotary encoder
#define LPD3806 1200 // รุ่น 600BM Rotary 3.2 cm.
#define ENCODER_A 14 // Pin for Encoder A
#define ENCODER_B 13 // Pin for Encoder B
long int encoder_value;  // ชนิดข้อมูลใน Arduino เป็นจำนวนเต็ม 32 บิตแบบมีเครื่องหมาย โดยมีช่วงตั้งแต่ -2,147,483,648 ถึง 2,147,483,647 ขนาดของ int32_t คือ 4 ไบต์ (32 บิต)

void encoder_a();
void encoder_b();
void check_value(); // check  value  engcodder  ไม่เท่ากับค่า  ติดลบ ถ้าติดลบจะให้เท่ากับ 0 
// ฟังก์ชัน interrupt เมื่อมีการเปลี่ยนแปลงจะที่ไม่สนใจ ⤵
void encoder_a()//ฟังก์ชัน encoder_a 
{
  int A = digitalRead(ENCODER_A); //อ่านค่าจาก ขา  GIPO ที่เก็บในตัวแปร ENCODER_A และ น ำ มาเก็บ A 
  int B = digitalRead(ENCODER_B);//อ่านค่าจาก ขา  GIPO ที่เก็บในตัวแปร ENCODER_B และ น ำ มาเก็บ B 

  if (B != A) /// ถ้า B ไม่เท่ากับ  A ให้ทำตามเงื่อนไข 
  {
    encoder_value++; // บวกค่าเพิ่ม 1
    
  }
  else  //ไม่ใช่
  {
    encoder_value--; // ลบค่า 1
  }
 
}
// ฟังก์ชัน interrupt เมื่อมีการเปลี่ยนแปลงจะที่ไม่สนใจ ⤵
void encoder_b()//ฟังก์ชัน encoder_b
{
  int A = digitalRead(ENCODER_A); //อ่านค่าจาก ขา  GIPO ที่เก็บในตัวแปร ENCODER_A และ น ำ มาเก็บ A 
  int B = digitalRead(ENCODER_B);//อ่านค่าจาก ขา  GIPO ที่เก็บในตัวแปร ENCODER_B และ น ำ มาเก็บ B 
  if (A == B)/// ถ้า B เท่ากับ  A ให้ทำตามเงื่อนไข
  {
    encoder_value++; // เพิ่มค่า 1
  }
  else //แต่ถ้าไม่  
  {
    encoder_value--;//ลดค่าลงที่ 1
  }

}
void check_value()// check  value  engcodder  ไม่เท่ากับค่า  ติดลบ ถ้าติดลบจะให้เท่ากับ 0 
{
  if ( encoder_value <= -1) //  ในกรณีที่  ค่า  encoder_value  เป็น ลบจะให้ค่า เท่ากับ  0
  {
     encoder_value = 0;//เป็น ลบจะให้ค่า เท่ากับ  0
  } 

}
#endif