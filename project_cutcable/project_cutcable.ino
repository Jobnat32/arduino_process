float length_cal = 0;//การประกาศตัวแปร มีชนิดข้อมูลเป็นทศนิยม (float) ค่าเริ่มต้นเป็น  0
#include "HlepLibary.h"//เรียกไฟล์ ชื่อ HlepLibary.h 
#include "HelpKeypad.h"//เรียกไฟล์ ชื่อ HelpKeypad.h 


void setup()//กำหนดการตั้งค่าเบื้องต้นสำหรับบอร์ด Arduino รวมถึงการกำหนดขา (pin) และเตรียมอุปกรณ์ต่างๆ ที่จำเป็นสำหรับโปรแกรมของคุณ.
{
  Serial.begin(115200);//เปิดการสื่อสาร Serial และเริ่มต้นการสื่อสารที่ความเร็ว 115,200 bps รายละเอียดของการสื่อสารจะถูกส่งออกไปผ่านพอร์ต Serial และคุณสามารถใช้คำสั่ง Serial.print() หรือ Serial.println() เพื่อส่งข้อมูลไปยัง Serial Monitor ของ Arduino IDE เพื่อตรวจสอบผลลัพธ์หรือรับข้อมูลจากโปรแกรม Arduino ไปยังคอมพิวเตอร์ของคุณ.
   pinMode(LED_BUILTIN, OUTPUT); // ประกาศขาเอาพุต สำหรับเรียกใช้
 //pinMode(BLYNK_LED, OUTPUT);
  config_hardware(); 
  pinMode(ENCODER_A, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(ENCODER_B, INPUT_PULLUP); // internal pullup input pin 3
 // pinMode(reset_board, INPUT_PULLUP); // internal pullup input pin 3
  setup_interrupt();// เรียกใช้ฟังก์ชัน setup_interrupt()
  SetupMinToPWM();// เรียกใช้ฟังก์ชัน SetupMinToPWM();
  select_mode_blynk();// เรียกใช้ฟังก์ชัน select_mode_blynk()
setup_key();// เรียกใช้ฟังก์ชัน setup_key()
check_setup_blynk();// เรียกใช้ฟังก์ชัน check_setup_blynk()
//setup_blynk();
  

}
/*
ฟังก์ชัน millis() เป็นฟังก์ชันใน Arduino IDE ที่ใช้ในการคืนค่าเวลาที่ผ่านไป (เวลาในมิลลิวินาที) ตั้งแต่ขณะที่โปรแกรม
 Arduino เริ่มทำงานหรือรีเซ็ตครั้งล่าสุด ใน Arduino, millis() มักถูกใช้ในการจับเวลาและกำหนดการทำงานหรือระยะเวลา
 ของกิจกรรมต่างๆ โดยสิ่งสำคัญที่ต้องรู้ คือ millis() จะคืนค่าเป็น unsigned long ซึ่งเป็นจำนวนเต็มไม่ลบที่สามารถเก็บค่าเวลา
 ได้มากถึงประมาณ 50 วัน โดยหลังจากนั้นจะมีการลูปกลับไปเริ่มนับใหม่.
*/
void loop()
{
  Serial.println("ST PIN RESET:  "+ String(digitalRead(reset_board)));// แสดงค่าสัญญาณ pin reset_board  ผ่าน serial monitor
CallFutionMode();//เรียกใช้ฟังก์ชัน CallFutionMode() 
CallFutionTask1();//เรียกใช้ฟังก์ชัน CallFutionTask1()
CallFutionTask2();//เรียกใช้ฟังก์ชัน CallFutionTask2()

Serial.println("Time :  " + String(millis())); // แสดงค่า millis()  ผ่าน serial monitor
static int cunter_blynk = 25; // คือการประกาศตัวแปร cunter_blynk ที่มีชนิดข้อมูลเป็นจำนวนเต็ม (integer) และกำหนดค่าเริ่มต้นให้เป็น 25 โดยใช้คำสั่ง static.
if(set_mode_blynk == true)//แต่ถ้า set_mode_blynk = true ทำภายใน {} 
{
  lenght_blnk =  length_cal,3; //ให้ค่า lenght_blynk มีค่าเป็น  lenth_cal และ ให้ใส่ 3 ทศนิยม
  Serial.println("Check cunter :  " + String(cunter_blynk)); // แสดงค่า cunter_blynk  ผ่าน serial monitor
if(StatusPC == "Running")//แต่ถ้า StatusPC = Running ทำภายใน {} 
{
httpGet("V9");//เรียกใช้ฟังก์ชัน httpGet("V9") โดยให้อ่านค่าภาย http V9
}
if(cunter_blynk >= set_bk)////แต่ถ้า cunter_blynk มากกว่าหรือเท่ากับ set_bk ทำภายใน {} 
{
Serial.println("update blynk");// แสดงค่า update blynk  ผ่าน serial monitor
blynk_fuction();//เรียกใช้ฟังก์ชัน blynk_fuction() 
cunter_blynk = 0;// ให้ค่าภายใน cunter_blynk มีค่าเป็น  0
} 
else//แต่ถ้าไม่
{
cunter_blynk++; //ให้ค่าเพิ่มทีระ 1
}
}
}



/*ฟังก์ชันต้้งค่า interrupt
digitalPinToInterrupt(ENCODER_A): การใช้ digitalPinToInterrupt()
 จะแปลงหมายเลขขาดิจิตอลที่คุณระบุ (ENCODER_A) เป็นหมายเลขอินเทอรัพต์ที่
 สามารถใช้ได้ในการเชื่อมต่อกับฟังก์ชัน attachInterrupt().
 encoder_a: นี่คือชื่อของฟังก์ชันที่คุณต้องการให้ Arduino เรียกเมื่อเกิดการเปลี่ยนแปลงบนขา 
 ENCODER_A. คังก์ชันนี้เพื่อทำงานในสิ่งที่ต้องการเมื่อเกิดการเปลี่ยนแปลง 
*/
void setup_interrupt(){
attachInterrupt(digitalPinToInterrupt(ENCODER_A) ,encoder_a, CHANGE);
attachInterrupt(digitalPinToInterrupt(ENCODER_B) ,encoder_b, CHANGE);
 
attachInterrupt(digitalPinToInterrupt(stoped_program),stop_program_now ,HIGH);
//attachInterrupt(reset_board, BackMotorLo, FALLING);//LOW เพื่อกระตุ้นการขัดจังหวะเมื่อใดก็ตามที่พิน

}
//่ฟังก์ชันหยุดการทำงาน
void stop_program_now()
{

 // ปิดรีเลย์ที่เชื่อมกับขา relay_lam
  digitalWrite(relay_lam, off_d);
  
  // ปิดรีเลย์ที่เชื่อมกับขา relay_motor_cut
  digitalWrite(relay_motor_cut, off_d);
  
  // ตั้งค่าสถานะ StatusPC เป็น "Stopping"
  StatusPC = "Stopping";
  
  // ตั้งค่า SelectMode เป็น "Stopping"
  SelectMode = "Stopping";
  
  // ตั้งค่า program_end เป็น true เพื่อบอกว่าโปรแกรมจบลง
  program_end = true;
  
  // ตั้งค่า step เป็น 999
  step = 999;
} 
