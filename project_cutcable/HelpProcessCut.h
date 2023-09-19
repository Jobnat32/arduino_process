#ifndef HelpProcessCut //ทำสิ่งที่คุณต้องการเมื่อ HelpProcessCut มีการใช้งาน
#define HelpProcessCut
#include "HlepLibary.h"


float Pwmnow;
int counter =  0; 


void ProcessCut();//ฟั่งชั่นลำการทำงาน
void ChekCablenow();//ฟั่งชั่นเช็คสาย  
void BackMotorLo();///ฟั่งชั่นหยุด โล่
void RunningCut(bool StatusCut);// ฟังชั่นการตัดสาย
void FeedSpool(bool StatusFeedlo);////ฟั่งชั่นเช็คสาย  
void ProcessEnd();// คำสั่งคืนค่าทั้งหมด
void config_hardware();//ตั้งค่าขา output ที่ใช้

void config_hardware(){
  pinMode(relay_lam, OUTPUT);
  pinMode(relay_motor_lo, OUTPUT);
  pinMode(relay_motor_cut, OUTPUT);
  // SETUP START PROGRAM OFF RELAY ALL 
  digitalWrite(relay_motor_lo,off_d);
  digitalWrite(relay_motor_cut,off_d);
  digitalWrite(relay_lam,off_d);

}

// คำสั่งคืนค่าทั้งหมด
void ProcessEnd(){
 digitalWrite(relay_motor_lo,off_d);// กำหนด relay_motor_lo off
 digitalWrite(relay_motor_cut,off_d);// กำหนด relay_motor_cut off 
 program_end = true;//การกำหนดค่าให้กับตัวแปร program_end โดยกำหนดให้มีค่าเป็น true
 runfeedcable = false; //กำหนดค่าให้กับตัวแปร runfeedcable โดยกำหนดให้มีค่าเป็น false
 StatusPC = "Endprocess";//กำหนดค่าให้กับตัวแปร StatusPC โดยกำหนดให้มีค่าเป็นสตริง (string) "Endprocess"
 CutCable = false;//กำหนดค่าให้กับตัวแปร CutCable โดยกำหนดให้มีค่าเป็น false
 set_bk = 1;//กำหนดค่าให้กับตัวแปร set_bk โดยกำหนดให้มีค่าเป็น 1.
}
//ฟังชั่น หมุน โล่สายไฟ 
void FeedSpool(bool StatusFeedlo)
{ 
 
  if (StatusFeedlo == true)//(ค่าของ StatusFeedlo เป็น true) โค้ดภายในบล็อก {} 
  { 
  static unsigned long TimeN_rf = millis(); // Variable to store the previous time value
  
  if(check_timeFR == 0)//(ค่าของ check_timeFR เป็น 0) โค้ดภายในบล็อก {}
  {
   // Serial.println("process Feedlo on");
    digitalWrite(relay_motor_cut,off_d);//กำลังตั้งค่าขาเอาท์พุต relay_motor_cut ให้เป็นสถานะ off_d 
    //Serial.println("lo on");   
   digitalWrite(relay_motor_lo,on_d);  //กำลังตั้งค่าขาเอาท์พุต relay_motor_lo ให้เป็นสถานะ on

   TimeN_rf = millis(); //กำลังกำหนดค่าที่ได้จาก millis() นั้น โดยในกรณีนี้ TimeN_rf จะเก็บค่าเวลาปัจจุบันในมิลลิวินาที.
   check_timeFR = 1;//กำหนดค่าให้กับตัวแปร check_timeFR โดยกำหนดให้มีค่าเป็น 1.
  }
  if(millis() - TimeN_rf > SPTimeRunFeed)//เป็นการตรวจสอบว่าผ่านไปเวลาเท่ากับหรือมากกว่าค่าที่เก็บไว้ใน SPTimeRunFeed โดยใช้ millis() เพื่อเข้าถึงเวลาปัจจุบันและ TimeN_rf เก็บเวลาที่ถูกบันทึกไว้ก่อนหน้านี้ หากเงื่อนไขเป็นจริง (ค่าที่ผ่านไปมากกว่า SPTimeRunFeed) โค้ดที่อยู่ในบล็อก {}
  {
  digitalWrite(relay_motor_lo,off_d);//กำลังตั้งค่าขาเอาท์พุต relay_motor_lo ให้เป็นสถานะ off_d
  ProcessEnd();//เรียกฟังชั่น ProcessEnd()  
  TimeN_rf = millis();//updata time ที่ผ่านมา 
  }

  }

}

void RunningCut(bool StatusCut)
{ 
 static unsigned long previousTimeC =  millis(); // Variable to store the previous time value

  if(check_timeRC == 0)//ตรวจสอบค่าใน check_timeRC เ่ท่ากับ 0  ให้ทำใน {}
  {
  //Serial.println("step3");
  //Serial.println("process Cut on"); 
   previousTimeC = millis();//เก็บค่าเวลาที่ผ่าน 
   
   
   if (StatusCut == true)// เมื่อ StatusCut เป็น true
   {

    digitalWrite(relay_motor_lo,off_d);
    digitalWrite(relay_motor_cut,on_d); 
    //Serial.println("cuut s...");
  
   } // Check if 1000 milliseconds (1 second) have passed
  check_timeRC = 1; //กำหนดค่าใน check_timeRC = 1 
  }

int C = 0;//ตัวแปร C ใช้เพื่อเก็บค่าจำนวนเต็ม โดยค่าเริ่มต้นของ C ในที่นี้ถูกกำหนดให้เป็น 0
  if(StatusCut == true)   // เมื่อ StatusCut เป็น true
{
  //Serial.println(C);

 
  unsigned long currentTimeC = millis(); // รับค่าเวลาปัจจุบัน// Get the current time value
  //Serial.println("Check Time cut : " + String(currentTimeC) + ":" + String(previousTimeC) + ":" + String(currentTimeC - previousTimeC) + ": 6000"); // Check timer program
  if (currentTimeC - previousTimeC >= 6000) // ถ้า currentTimeC - previousTimeC มาดกล่าว ุ6000 
  {
   //Serial.println("cuut");
    digitalWrite(relay_motor_cut,off_d);   //สั่งปิด  relay  motor 
    CutCable = false;//กำหนดค่า CutCable เป็น false
    runfeedcable = true;//การกำหนดค่า runfeedcable เป็น true
    previousTimeC = currentTimeC;// รับปัจุบันมาเก็บ 
    step =  40; // การกำหนดตัวแปร step  เท่า 4
  }
  C++; //ให้บวกค่า 1+
}

}




//สั่ง มอเติร์หยุดทำงาน
void BrakeMotorLo()
{
digitalWrite(relay_motor_lo,off_d);//สั่งหยุด delay  หรือ ปืด
brake_read = true;//  และให้ brake_read มีค่าเท่ากับ true
CutCable = true;//ให้ CutCable มีค่าเท่ากับ true
}

//ฟั่งชั่นเช็คสาย  
void ChekCablenow()
{
  //Serial.println("k");
   
 // Serial.println(bool(float(encoder_value/2) != float(Pwmnow))); // check cable 
 if( float(encoder_value/2) == Pwmnow && CutCable == false) // ถ้า ค่า endoder_value/2 == Pwmnow และ CutCable == false จะให้ทำภายใน {}
 {  static unsigned long timeN_ct = millis(); // Variable to store the previous time value // ตัวแปรเพื่อจัดเก็บค่าเวลาก่อนหน้า
    unsigned long timeNR_ct = millis(); //ตัวแปรเพื่อจัดเก็บค่าเวลาค่าที่ผ่านมานะตอน ้้น
   //Serial.println("Check Time : " + String(timeNR_ct) + ":" + String(timeN_ct) + ":" + String(timeNR_ct - timeN_ct)); 
 if (timeNR_ct - timeN_ct > 1000)//เปรียบเทียบค่าที่มาและเวลาเริ่มต้น หาเวลาที่ run มากล่าว 1000 หรือไม่ถ้าให้ทำถาย{}
 {
  counter++; // บวกค่าเพิ่มทีละ 1
  
  timeN_ct = timeNR_ct; //และทำการ อัปเดท time
   } 
   //Serial.println("counter : " +String(counter));
 }
 else if(float(encoder_value/2) != float(Pwmnow)) //  แต่ถ้า encoder_value/2 != Pwmnow 
 {
  counter = 0;//ให้เครีย counter เท่ากับ 0
 }
 if (counter >= 15)//ถ้า counter > 15 ให้ภายใน  {} 
 {
  digitalWrite(relay_lam,on_d); // ให้้สั่ง  relay_lam   on   
  StatusPC = "Time Out";// ให้ตัวแปร statusPC =  Time Out
  //Serial.println("Alarm Cable");
  ProcessEnd(); //ฟังชั่นคืนค่าเริ่มต้น  
 }

 Pwmnow = encoder_value/2 ;///  อัปเดทที่รับก่อนหน้า 
}

void ProcessCut(){
//Serial.println("program_end :" + String(bool(program_end)));
//Serial.println("step : " +  String(step) );
  //if (program_end == false)
  //{
   
Serial.println("ENCODER :" + String(encoder_value/2)+ ":" + String(SpPwmCut)); //เช็คระยะสาย
 if(program_end == false )//ถ้า  program_end  =  flase ให้ภายใน {}   
 {
  //Serial.println("hello p cut");
  if (Strat_motorP == true && step == 10)// ถ้า  Strat_motorP = true && step = 10 ให้ภายใน  {}
  {
  //Serial.println("Motor On");
  digitalWrite(relay_motor_lo,on_d);// ให้ดีเลย์ มอสเตอร์ โล on
  CutCable = false;// กำหนดตัวแปร  CutCable =   false 
  runfeedcable = false; // กำหนดตัวแปร  runfeedcable = false 
  Strat_motorP = false; //กำหนด Strat_motorP = false
  //Serial.println("step1");
  step = 20; //กำหนดตัวแปร  step  =  20
 }
 // Serial.println("step2 check : "+ String(bool((float(encoder_value/2) >= SpPwmCut && step == 20 ))));   
 if (float(encoder_value/2) >= SpPwmCut && step == 20 )// ถ้า encoder_value/2 มากกว่า SpPemCut && step = 20 ให้ทำภายใน {}
 {
  //Serial.println("step2 : "+ String(bool(encoder_value >= SpPwmCut)));  
  ///if (float(encoder_value/2) >= SpcheckPwm){
  digitalWrite(relay_motor_lo,off_d);   // สั่งให้ output off  
  CutCable = true;//  กำหนดให้มีค่า  CutCable = true
  step = 30;//กำหนดตัวแปร  step  =  30
 
  //}
 }
 if (CutCable == true && step  == 30)// ถ้า  CutCable = true และ step  = 30  ให้ทำภายให้{}
 {
 //Serial.println("step3");
  RunningCut(CutCable); //  เรียกฟังชั่น   RunningCut(CutCable) และส่ง ค่าไปยัง ฟังชั่น
  
 }
 if (runfeedcable == true &&  step == 40)//ถ้า  runfeedcable = true และ step  = 40  ให้ทำภายให้{}
 {
  //Serial.println("step4");
  FeedSpool(runfeedcable);//เรียกฟังชั่น   FeedSpool(runfeedcable) และส่ง ค่าไปยัง ฟังชั่น
   
    }
 ChekCablenow();////ฟั่งชั่นเช็คสาย  
 }
  
  }
//}

#endif
