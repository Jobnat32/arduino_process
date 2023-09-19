#ifndef HelpCall//ทำสิ่งที่คุณต้องการเมื่อ HelpSelectMode มีการใช้งาน
#define HelpCall//คืออการกำหนดค่า HelpCall ให้เป็นจริง เมื่อไฟล์นี้ถูกนำเข้าครั้งแรก 
#include "HelpCall.h"//#include "HelpCall.h" และ #include "HlepLibary.h" - คำสั่งนี้ใช้ในการนำเข้าไฟล์หัวข้อ (header files) อื่น ๆ 
#include "HlepLibary.h"
void CallFutionTask1();//เป็นการประกาศฟังก์ชันที่ชื่อว่า CallFutionTask1 ในภาษา C++ หรือ C
void CallFutionTask2();//เป็นการประกาศฟังก์ชันที่ชื่อว่า CallFutionTask2 ในภาษา C++ หรือ C
void CallFutionMode();//เป็นการประกาศฟังก์ชันที่ชื่อว่า CallFutionTask3 ในภาษา C++ หรือ C

void CallFutionMode()
{
if (status_blynk == false)//ใช้ if (!status_blynk) แทน if (status_blynk == false) เพื่อเป็นการตรวจสอบว่า status_blynk เป็นเท็จ (false) ในทางด้านของสัมพันธ์.
{
while (true)
{    
char keyb = keypad.getKey();//ใช้ในการอ่านคีย์ที่ถูกกดบนแป้นพิมพ์ (หรือ keypad) และเก็บคีย์ที่ถูกอ่านไว้ในตัวแปร keyb ซึ่งมีประเภทเป็น char หรือตัวอักษรแบบหนึ่งตัว 
char check;// // กำหนด check เป็นค่าว่าง (\0) เพื่อให้เริ่มต้น
Serial.println("M :" + String(keyb));
if(keyb != check)//keyb และ check มีค่าต่างกัน (คีย์ใหม่ไม่เหมือนคีย์เก่า) โค้ดภายในบรรทัดนี้จะถูกดำเนินการ.
{
Serial.println("M : hello selmod" );
return select_onoff_bk(keyb);// ใช้ในการเรียกใช้ฟังก์ชัน select_onoff_bk(keyb) และคืนค่าที่ฟังก์ชัน select_onoff_bk ส่งกลับไปให้กับส่วนที่เรียกใช้งานฟังก์ชัน CallFutionMode ซึ่งอาจจะใช้ค่านี้เพื่อดำเนินการต่อหรือจัดการกับข้อมูลที่ถูกส่งกลับจาก select_onoff_bk
}
else{check = keyb;}//check ให้เป็นค่าของ keyb ซึ่งมีแนวคิดคือการเก็บค่าคีย์ที่ถูกกดล่าสุดเพื่อใช้ในการเปรียบเทียบในรอบถัดไป.

}
}
delay(250); //ใช้ในการหน่วงเวลาหน่วยเป็นมิลลิวินาที โดยในที่นี้กำหนดให้หน่วงเวลา 250 มิลลิวินาที 
}

void CallFutionTask1(){
check_value();// check  value  engcodder  ไม่เท่ากับค่า  ติดลบ ถ้าติดลบจะให้เท่ากับ 0     
char check_key = key_pad();// รับค่าฟังชั่น  key_pad()
//Serial.println("f :" + String(check_key));
if (StatusPC != "Running" && StatusPC != "Setting") //ถ้า StatusPC ไม่ได้อยู่ในสถานะ "Running" หรือ "Setting" โปรแกรมจะเรียกใช้ฟังก์ชัน select_menu(check_key)
{
    select_menu(check_key);// ฟังก์ชัน เลือก mode
}
else if (StatusPC == "Running")//กรณีที่ StatusPC มีค่าเป็น "Running" โปรแกรมจะดำเนินการในบรรทัดนี้
{
    ProcessCut();//เพื่อดำเนินการตามเงื่อนไขที่คุณกำหนดในสถานะ "Running".
}

}

void CallFutionTask2()
{
static String Checkupdatemode; // ประกาศตัวแปรสติงค่าคงที่  
static unsigned long check_encode;// ประกาศตัวแปรสติงค่าคงที่  
static unsigned long TimeupDate = millis();//ประกาศตัวแปรสติงค่าคงที่ และนำค่า ในฟังชั่น millis() เก็บ 
float conlogtofloat = encoder_value;// ค่าที่อ่าน ได้จาก endcoder_value มาเก็บ ใน conlogtofloat ในตัว แปร ทศนิยม
length_cal =  ((conlogtofloat/2400)*100)/1000;//นำค่ามาคำนวณหาความของสายที่วัดได้
//Serial.println("LengthL check:  " +  String(encoder_value));
//Serial.println("Length check:  " +  String(length_cal ,3));
if (millis() - TimeupDate >= 250 )   // millis - TimeupDate มากกล่าวหรือ เท่ากับ 250 ให้งานภายใน
{
  if (check_encode != encoder_value) //check_encode != encoder_value ไม่เท่ากันให้ update LCD or ถ้า  endcoder มีการเปบลียนแปลง 
  {
        
        //Serial.println(length_cal,6);
        update_lengthnow(String(length_cal,3));// อัปเดท  LCD
    }
    
    if (SelectMode != Checkupdatemode)// ถ้า SelectMode ไม่เท่า Checkupdatemode ให้ภายในฟั่งชัน
    {
        if(StatusPC != "Setting")// ถ้า SelectPC ไม่เท่า "Setting" 
        {
            update_length(String(length_cal,3),SelectMode); //ให้เรียกใช้ฟังชั่น  update_length(str,str)

            
        }
        else if (StatusPC == "Setting") //ถ้าเท่ากับ StatusPC == "Setting"  
        {
        monitor_set_cut(corsor_x,corsor_y);////ให้เรียกใช้ฟังชั่น monitor_set_cut(int,int)
        }
        TimeupDate = millis(); //move TimeupDate = millis() or อัปเดทเวลา
    }
//อัปเดทค่าเมื่อทำเสร็จ
Checkupdatemode = SelectMode;
check_encode = encoder_value; 
}

}  
//เช็คสถานะ  Program ทั้งหมด
void callchek(){
    Serial.println("<_____________Check status______________>");
    Serial.println("selcet mode" + SelectMode);
    Serial.println("Status PC" + StatusPC);
    Serial.println("ST Program : " + String(program_end));
    Serial.println("Step" + String(step));
    Serial.println("Check Pwm now >= SP cut: "+ String(encoder_value <=  SpPwmCut));
    
    Serial.println("<_____________END Check status__________>");
}

#endif