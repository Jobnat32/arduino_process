#ifndef HelpLCD//ทำสิ่งที่คุณต้องการเมื่อ HelpLCD มีการใช้งาน
#define HelpLCD
#include "HlepLibary.h"

// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x3F, 20, 4);
LiquidCrystal_I2C lcd(0x27, 20, 4);

String sum_input_kb;
String status_set,select_set,text_monitor,sum_input_cut;

///ประกาศใช่ฟั่งทั้งเพื่อป้องกันการเรียกหาฟั่ง error
int corsor_x, corsor_y; //ประกาศตัวแปลแบบ int หรือ ตัวเลข 
void select_mode_blynk(); // ฟังชั่นเลือกการใช่งาน blynk
void update_length(String length,String SelectMode); // ฟังชั่นอัปเดทค่าความยาวบน LCD และ สถานะโหมด
void monitor_main(String text);//ฟังชั่นอัปเดทขนาดมีการเปลื่ยน หรือ ขณะเปลี่ยนโหมด
void update_status_out(String STATUS);//อัปเดทสถานะ
void monitor_set_cut(int cs_x, int cs_y);  // ฟังชั่งแสดงผลขนาด ตั้งค่า setcut 
void setting_cut(); // ฟังชั่นตำแหน่ง ลูกศรการทำงานนั้น
//

//ฟังชั่นอัปเดทขนาดมีการเปลื่ยน หรือ ขณะเปลี่ยนโหมด
void monitor_main( String text)
{

  String legth_input= String(encoder_value);// แปลงค่าตัวอัษร และ เก็บในตัวแปล
    unsigned int CL_lenght = legth_input.length(); //หาความ STR
  
  if (CL_lenght >= 8)// ถ้าความยาวเกินให้ค่าเท่า "∞" 
  {
    legth_input = "∞";
  }

  Serial.println("hello");//  print text status serial monitor
  Serial.println(text);//  print text status serial monitor
  lcd.clear(); // ล้างหน้าจอlcd.clear(); // ล้างหน้าจอ
  lcd.init();//ประกาศการใช้งาน LCD
  lcd.backlight();//ปรับความสว่างหน้าจอ LCD
  lcd.setCursor(0, 0);//บันทัดที่ 1 
  // แสดงเลือก โมดในการทำงาน
  lcd.print("  Status: "  + text);//นำค่าที่ส่งผ่านฟังชั่นส่งมาแสดงผล 
  lcd.print("length : "+ legth_input + " m.");//นำค่าอ่านมาแสดง
  lcd.setCursor(1,2);//set ตำแหน่งต้องการแสดง
  lcd.print("SP Cut : " + String(set_cut) + " m.");// นำค่า set_cut มาแสดงผล

  text_monitor = text; //การแทนค่าให้  text_monitor = text 
}
void update_status_out(String STATUS)
{  lcd.init();
  lcd.clear(); // ล้างหน้าจอlcd.clear(); // ล้างหน้าจอ
  lcd.setCursor(0,3);
  lcd.print( "ST : "+ STATUS); 
}
void update_lengthnow(String length){
  String lentext =("length : "+ length + " m.");
 int lenn = lentext.length();
Serial.println("<______update_____>");
Serial.println("lentext");
Serial.println(lentext);
Serial.println("<______END update_____>");

    lcd.setCursor(0,1);//บันทัดที่ 2
  lcd.print(lentext);
}

void update_length(String length,String SelectMode)
{
  unsigned int CL_lenght = length.length();
  if (CL_lenght >= 8){
    length = "∞";
  }
lcd.clear(); // ล้างหน้าจอ 
lcd.init(); 
lcd.backlight();//ปรับความสว่างหน้าจอ LCD

  lcd.setCursor(0, 0);//บันทัดที่ 1 
  // แสดงเลือก โมดในการทำงาน
  lcd.print("  Status: "  + SelectMode);// แสดงสถานะโปรแกรม ขณะนั้นๆ บันทัดที่ 1 
  lcd.setCursor(0,1);//บันทัดที่ 2
  lcd.print("length : "+ length + " m."); //แสดงค่าความยาวที่วัดได้
  lcd.setCursor(1,2);//บันทัดที่ 3
  lcd.print("SPCut : " + String(set_cut) + " m.");// แสดงค่าระยะที่ต้องการตัด

}
//setup value set_cut
void monitor_set_cut(int cs_x, int cs_y)
{
  lcd.clear(); // ล้างหน้าจอ
  lcd.backlight();//ปรับความสว่างหน้าจอ LCD
  lcd.setCursor(0, 0);//บันทัดที่ 1  
  // แสดงเลือก โมดในการทำงาน
  lcd.print("   Setup : Cut");
  //  ระบุตำแหน่งในการแสดงใน  lcd  บรรทัด 2  และ ก็เริ่มต้นตัวอักษรที่ 1
  lcd.setCursor(3, 1);//บันทัดที่ 2
  lcd.print(" cut(m): " + String(sum_input_cut)); //แสดงบนหน้าจอ LCD
 lcd.setCursor(5, 3);//บันทัดที่ 4
  lcd.print("Cancel   Ok ");//แสดงบนหน้าจอ LCD
  lcd.setCursor(cs_x, cs_y);//รับค่าจากฟั่งชั่น เพื่อแสดงลูกศรตามที่กำหนด
  lcd.print("->");//แสดงบนหน้าจอ LCD

  
}

void setting_cut()
{//corsor_x , corsor_y ประกาศค่าเริ่มต้นของตำแหน่งลูกศร เป็นตัวแปรแบบใช่ร่วม
corsor_x = 1;//move หรือ กำหนดค่าให้เท่ากับ  1 
corsor_y = 1;//move หรือ กำหนดค่าให้เท่ากับ  1 
sum_input_cut =  set_cut; //move หรือให้ ค่า sum_input_cut =  set_cut มีค่าเท่ากัน
  monitor_set_cut(corsor_x,corsor_y);
    while (true)
  {
      /*ฟั่งชั่นรับค่าจากปุ่มกดและแสดงผล*/
     // Serial.print(key_pad());   
      char key = key_pad(); // สร้างตัวแปรชื่อ key ชนิด char เพื่อเก็บตัวอักขระที่กด

    if (key!=' ')
      {                      // ถ้าหากตัวแปร key มีอักขระ
        Serial.println(key); // แสดงผลระหว่างกด
        if (key == 'A') // ถ้าค่าเท่ากับ  A  ให้ทำภาย
        {
          corsor_x = 3;//move หรือ กำหนดค่าให้เท่ากับ  3
          corsor_y = 3;//move หรือ กำหนดค่าให้เท่ากับ  3
          status_set = "cancel"; //move หรือ กำหนดค่าให้เท่ากับ  "cancel"
        
        }
        else if (key == 'B')// แต่ถ้าค่าเท่ากับ B  ให้ทำภาย
        {
          corsor_x = 12;//move หรือ กำหนดค่าให้เท่ากับ  12
          corsor_y = 3; //move หรือ กำหนดค่าให้เท่ากับ  3 
          status_set = "ok";//move หรือ กำหนดค่าให้เท่ากับ  ok 

        }
        else if (key == 'C')// แต่ถ้าค่าเท่ากับ c  ให้ทำภาย
        {
          sum_input_cut = "";  //  sum_input_cut ให้เท่ากับ

        }
        else if (key == '#')// แต่ถ้าค่าเท่ากับ #  ให้ทำภาย
        {
          if(status_set == "ok")  // และถ้า status_set == "ok" 
          { 
            set_cut = sum_input_cut.toInt(); //ให้แปลงค่า sum_input_cut STR to int หรือ  สติง เป็น เลข
            SetupMinToPWM(); // ฟังชั่นที่ แปลงค่า ที่ต้องการตัน PWM 
            break;// ออก วายลูป
          }
          else if(status_set == "cancel") //แต่ถ้าเท่ากับ cancel 
          {
            set_cut = set_cut; //ให้ตัว set_cut = set_ccut  หรือ ค่าเท่าก่อนหน้้า 
            break;// ออก วายลูป 
          }

        }
        else if (key ==  '*')// แต่ถ้าค่าเท่ากับ *ให้ทำภาย
        {
          corsor_x = 1;//move หรือ กำหนดค่าให้เท่ากับ  1
          corsor_y = 1; //move หรือ กำหนดค่าให้เท่ากับ  1
        }
        else if (key != 'A' || 'B'||'D'|| '#'|| 'C'|| '*') // แต่ถ้าค่าเท่ากับไม่เท่า 'A' || 'B'||'D'|| '#'|| 'C'|| '*' ให้ทำภาย
          {
            if(corsor_x == 1 && corsor_y == 1) //ถ้าค่าเท่ากับ corsor_x และ corsor_y เท่ากับ 1
            {
            sum_input_cut = sum_input_cut + String(key); // ให้นำค่ากดมาบวกกัน
            
          }
          }
      monitor_set_cut(corsor_x,corsor_y);//เรียก ฟังชั่นและนำค่าไปแสดงผล
      }
      
  }
  StatusPC = " ";//ถ้าค่าเท่ากับ StatusPC ค่าว่าง
  //SetupMinToPWM();
  return (monitor_main("Setup ok")); // เรียกหน้าจอ LCD หน้าหลัก และ แสดงผล  Setup ok
}

  
  





void update_monitor(){
static unsigned long previousTimeM = 0; // Variable to store the previous time value
  unsigned long currentTimeM = millis(); // Get the current time value
  Serial.println("cuut s");
  // Check if 1000 milliseconds (1 second) have passed

  if (currentTimeM - previousTimeM >= 2000) {
  monitor_main(text_monitor);
  previousTimeM = currentTimeM;
  }
}

void select_mode_blynk(){
  lcd.clear(); // ล้างหน้าจอlcd.clear(); // ล้างหน้าจอ
  lcd.init();
  lcd.backlight();//ปรับความสว่างหน้าจอ LCD
  lcd.setCursor(3, 0);//กำหนดตำแหน่ง การแสดงผล
  // แสดงเลือก โมดในการทำงาน
  lcd.print("Select Mode"); 
  lcd.setCursor(4,1);//กำหนดตำแหน่ง การแสดงผล
  lcd.print("* : Not Blynk ");
  lcd.setCursor(4,2);//กำหนดตำแหน่ง การแสดงผล
  lcd.print("# : Blynk");
  lcd.setCursor(3,3);//กำหนดตำแหน่ง การแสดงผล
  lcd.print(ST_LCD_B);
}


#endif 