#ifndef HelpSelectMode// ทำสิ่งที่คุณต้องการเมื่อ HelpSelectMode มีการใช้งาน
#define HelpSelectMode//กำหนดค่าสัญลักษณ์ 
#include "HlepLibary.h"



int i; // ประกาศตัว  i ให้เก็บตัวแปรประเภท  int 
void select_onoff_bk(char status);// ฟังก์ชัน หนยุดการทำงาน  มอเตอร์ โดยส่งค่าพารามิเตอร์มา
void select_menu(char input);//ฟั่งการเลือกโหมด
void stop_program(char stop_input);
void select_onoff_bk(char status)
{

    /*ฟั่งชั่นรับค่าจากปุ่มกดและแสดงผล*/
    /*ถ้ากด # ให้ Blynk Line หรือทำการให้  Blynk */
    if (status == '#')//แต่ถ้า status =  # ทำภายใน {} 
    {
      status_blynk = true;  //ให้มีค่า status_blynk ให้เก็บ  true
      set_mode_blynk =true;//ให้มีค่า set_mode_blynk ให้เก็บ  true
      ST_LCD_B = "Blynk Online";//ให้มีค่า ST_LCD_B ให้เก็บ  Blynk Online
      setup();// ให้เรียกใช้ฟังชั่น setup()
    }
    else if (status == '*')//แต่ถ้า status =  * ทำภายใน {} 
    {
      status_blynk = true; //ให้มีค่า status_blynk ให้เก็บ  true
      set_mode_blynk = false; //ให้มีค่า status_mode_blynk ให้เก็บ  false
      ST_LCD_B = "Blynk Offline";//ให้มีค่า ST_LCD_B ให้เก็บ  Blynk Online
     setup();// ให้เรียกใช้ฟังชั่น setup()
    }
    
}


//ฟังชั่นเลือกโหมดการทำงาน  โดยมีค่าพารามิเตอร์มาด้วย
void select_menu(char input)
{
  // Serial.println("manul Fibfob LED" + input);
if(input == '*') //ถ้าค่าที่ส่ง = * ทำงานภายใน {} (ในกรนี้ที่อยู่ในการเริ่มต้นโปรแกรม)
{

    if (SelectMode == "Setting") // ถ้า SelectMode =  Setting ให้ทำภายใน {} 
    {
      SelectMode = "Running";// ให้ค่าใน SelectMode = Running
    //Serial.println("Strat_motorP: "+ String(Strat_motorP));
   // Serial.println("program_end" + String(program_end));
  

    } 
   else if (SelectMode == "Running")//  แต่ถ้า SelectMode = Running จะให้ทำภายใน{}
   {
      SelectMode = "Setting";// ให้ค่าใน SelectMode = Running
  }      
    else//แต่ไม่ตรงเงื่อนไขไหน ให้ภายใน else  
    {
      SelectMode = "Setting";// ให้ค่าใน SelectMode = Setting
      set_bk = 2; // ให้ค่าภายในตัวแปร set_bk=  2
  }      
 // Serial.println("Status C: " + SelectMode );
   
}

  if (input == '#')//ถ้าค่าที่ได้รับ มาเป็น # ให้ทำภายใน {}  
  {

    if (SelectMode  == "Running")//ถ้า SelectMode = Running 
    {
        if ((float(encoder_value)/2) <=  SpPwmCut)//ถ้า 
        {
       // Serial.println("manul Fibfob LED"); 
        StatusPC = "Running"; //ให้ัวแปร StatusPC =  Running 
        program_end = false; //ให้ัวแปร program_end  =  false
        Strat_motorP = true; // ให้ตัวแปร Strat_motorP =  true 
        step =  10; //ให้ตัวแปร step  = 10   
        set_bk = 5;//ให้ตัวแปร set_bk  = 5  
        }

    //ProcessCut();    
    }
    else if (SelectMode == "Setting") // แต่ถ้า SelectMode  = Setting  ให้ทำงานภาย {}
    {
      StatusPC = "Setting"; //ให้ตัวแปร  StatusPC =  Setting
       setting_cut(); //เรียกฟังชั่น  setting_cut()
    }
    
  }
   if(input == 'C')  //ถ้า input = 'C' 
   {
    encoder_value = 0;  //ให้ตัวแปร encoder_value  = 0
    check_timeFR = 0; //่ให้ตัวแปร  check_timeFR  = 0
    check_timeRC = 0;//่ให้ตัวแปร  check_timeRC  = 0
    counter = 0;//่ให้ตัวแปร  counter  = 0
    step =0;//่ให้ตัวแปร  step  = 0
    digitalWrite(relay_lam , off_d);//ให้ขาดิจิตอล ตัวแปร  relay_lam  หยุดทำงาน
     }

    if (input == 'D') //ถ้า input = D ให้ทำงานภายใน  {}
    {
        if (SelectMode == "Setting") // ถ้า SelectMode ถ้ามีค่า Setting 
        {
       bool status_cut = !digitalRead(relay_motor_cut); //ประกาศ staut_cut เก็บตัวแปล  boolen และ อ่านจาก relay_motor_cut มาเก็บในตัวแปร
        String text_status = "" ;//ประกาศ status_cu เก็บตัวแปล   สติง
        digitalWrite(relay_motor_cut,status_cut);// ให้สั่งให้ขา relay_motor_cut มีสถานะตาม  status_cut 
        if(status_cut == 0 )//ถ้า status_cut  = 0  ให้ทำภายใน {}
        {
            text_status = "ON"; // ให้ text_status มีค่าเป็น ON 
        }
        else//ถ้า ไม่ 
        {
            text_status = "OFF";//ให้ test_status มีค่าเป็น  OFF
        }
        
        //update_status_out("Relat Cut" + text_status);// check text_status to  monitoring
        }
    }
    if (input == 'B') //  ถ้า  input  มีค่าเป็น  B  ให้ทำภายใน{}
    {
        if (SelectMode == "Setting")// ถ้า SelectMode มีค่าเป็น  Setting ให้ทำภายใน  {}
        {
       bool status_rl = !digitalRead(relay_motor_lo);//ประกาศ status_rl เก็บตัวแปล  boolen และ อ่านจาก relay_motor_lo มาเก็บในตัวแปร
        String text_status = "" ;//ประกาศ status_rl เก็บตัวแปลสติง
        digitalWrite(relay_motor_lo,status_rl);// ให้สั่งให้ขา relay_motor_lo มีสถานะตาม  status_rl 
        if(status_rl == 0 )//ถ้า status_rl  = 0  ให้ทำภายใน {}
        {
            text_status = "ON";// ให้ text_status มีค่าเป็น ON 
        }
        else//ถ้าไม่ 
        {
            text_status = "OFF";//ให้ test_status มีค่าเป็น  OFF
        }
        }
        if (input  == '*'  && StatusPC == "Runnig") //ถ้า input มีค่าเท่ากับ * และ Status มีค่าเท่ากับ Running ภายใน {}
        {
        program_end = true;// ให้ตัวแปร  program_end มีเป็น  True 
        digitalWrite(relay_motor_cut,off_d); //สั่งให้ขาดิจิตอล relay_motor_cut เป็น off หรือ สั่ง off มอเตอร์ relay_motor_cut 
        digitalWrite(relay_motor_lo,off_d);//สั่งให้ขาดิจิตอล relay_motor_lo เป็น off หรือ สั่ง off มอเตอร์ relay_motor_lo
        SelectMode = "Stop";//ให้ตัวแปร SelectMode มีค่าเป็น Stop
        StatusPC = "Ready";//ให้ตัวแปร SelectPC มีค่าเป็น ready
        set_bk = 1;//ให้ตัวแปร set_bk มีค่าเป็น 1
        }
        
        //update_status_out("Relat Cut" + text_status);
        
    }
   // resor ='0';
return;//รีเทินค่าค่าว่าง
}

//ฟังก์ชัน หยุดการทำงานทั้งหมด
void stop_program(char stop_input){
if (stop_input == '*')//ถ้า stop_input มีค่าเท่ากับ  * ให้ทำงานภายใน{}
{
  stoped_program = true; //ให้ตัวแปร stoped_program มีค่าเป็น true 
}
}

#endif