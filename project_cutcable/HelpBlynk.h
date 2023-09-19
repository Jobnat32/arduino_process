#ifndef HelpBlynk //ทำสิ่งที่คุณต้องการเมื่อ HelpBlynk มีการใช้งาน
#define HelpBlynk 
#define RESET_WIFI 35 //ประกาศจองขา io 
#include "HlepLibary.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// การเรียกใช้ผ่าน ไอดี โทรเค็น เท็มเพจ Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6SFA-6M49"
#define BLYNK_TEMPLATE_NAME "cut cable"
#define BLYNK_AUTH_TOKEN "2QpNJdLQJzeWuI3l5vnXJiLFgtf387O4"
// Http การประกาศเรียกใช้
#include <HTTPClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
// เรียกใช้ Timer ของ blynk เพื่อใช้ในการ อัปเดท หน้าจอ   blynk
BlynkTimer timer;
WidgetLCD LCDblynk1(V6); // จอแสดงผลหน้า1
WidgetLCD LCDblynk2(V7); // หน้า2
// String ตัวอักษร
// เรียก ไรบารี wifi connect
//#include <WebServer.h> // Replace with WebServer.h for ESP32
//#include <AutoConnect.h>
//WebServer Server; // Replace with WebServer for ESP32
//AutoConnect Portal(Server);

void rootPage();
void BlynkCheckConnect();
void setup_blynk(); 
void check_setup_blynk();


void blynk_stop(bool status_bk); //stop blynk ขนาดกดปุ่ม ขนาด  running
String httpGet(String pin);// ฟังชันอ่านค่า blank  ขณะ runnnig
BLYNK_WRITE(V2);//  ฟังอ่านค่าขนาด กด V2

void myTimer()
{
   // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  /* แปลงค่าส่ง blynk length โดย มีหลักการคือ เอาค่าใน calcular_compriment ที่มีค่าเป็น mm แล้วค่ามาหาร 1000
    เพื่อให้แสดงหน้า app Blynk หน่วยเป็น m ⤵*/

  //calcular_compriment;
  /*คือการสั่งให้นำข้อมูลไปเขียนที่ใด V4 ตำแหน่งที่เขียน
    Blynk.virtualWrite(ตำแหน่ง, ค่าตัวแแปล);
  */

  Blynk.virtualWrite(V0, !digitalRead(relay_lam));
  Blynk.virtualWrite(V1, !bool(program_end));
}


void lcd_blynk()
{
  String LCDBK1B1;
  String LCDBK1B2;
  String LCDBK2T1;
  String LCDBK2T2;
  if (SelectMode == "SettingBK")
  {
    LCDBK1B1 = SelectMode;
    LCDBK1B2 = String(lenght_blnk,3) + " m.";
    LCDBK2T1 = String(pinValueCut) + "m.";
    LCDBK2T2 = String();
  }
  else
  {
    LCDBK1B1 = SelectMode;
    LCDBK1B2 = String(lenght_blnk,3) + " m.";
    LCDBK2T1 = String(set_cut) + " m.";
    LCDBK2T2 = " ";
  }

  LCDblynk1.clear(); // เครียหน้า LCD หน้า  app Blynk
  LCDblynk1.print(0, 0, "Status:" + LCDBK1B1);
  LCDblynk1.print(0, 1, "Length:" + LCDBK1B2);
  LCDblynk2.clear();
  LCDblynk2.print(0, 0, "cut:" + LCDBK2T1);
  LCDblynk2.print(2, 1, " " + LCDBK2T2);
  httpGet("V9"); // อ่านค่าจากขา Blynk server ผ่าน URL Button stop
}

void check_setup_blynk(){
  if(set_mode_blynk == true){
    Serial.println("Blynk setup" );
    setup_blynk();
  }
  else
  {
    
  }
  
}
void setup_blynk()
{
  
  pinMode(RESET_WIFI , INPUT_PULLUP);

      //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
bool CHECK_BT_RESET_WIFI= digitalRead(RESET_WIFI);
  Serial.println("blynk BT" + String(CHECK_BT_RESET_WIFI)+ String(bool(CHECK_BT_RESET_WIFI ==  true)));
if (CHECK_BT_RESET_WIFI ==  true)
{
      wm.resetSettings();
}
    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    //res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
    Serial.println("Status : " + String(res));
    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
      Serial.println("connected...yeey :)");
        //if you get here you have connected to the WiFi
         // Blynk.begin(auth, ssid, pass);
        //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass,"blynk.cloud",8080);    
        Blynk.config(BLYNK_AUTH_TOKEN,"blynk.cloud",8080); 
       // Blynk.config(BLYNK_AUTH_TOKEN);
        
    }

 

  digitalWrite(LED_BUILTIN, HIGH);               // เมือเชื่อมต่อได้สั่งให้ led ที่บอดติด
  //digitalWrite(BLYNK_LED, HIGH);
  // timer.setInterval(500L, customRand);
  /*ความหมายของพารามิเตอร์ในฟังก์ชัน timer.setInterval() ได้ดังนี้:

    500L : หมายถึงค่าเวลา (interval) ที่ต้องการให้ตัวจับเวลาทำงาน เป็นเวลา 500 มิลลิวินาที
    โดยตัวอักษร L ที่ต่อท้ายเลข 500 คือการระบุว่าเป็น Long integer แทนที่จะใช้ integer
    ธรรมดา เพื่อป้องกันปัญหาเวลาที่ถูกแปลงผิดพลาด myTimer : หมายถึงฟังก์ชันที่ต้องการให้
    timer เรียกใช้ทุกครั้งที่ interval ถึงจะถูกเรียกใช้งาน ในที่นี้คือฟังก์ชัน myTimer()
    ที่ถูกกำหนดไว้ในโค้ดแล้ว ⤵)*/
  bool result = Blynk.connect();
  timer.setInterval(100L, myTimer);    //
  timer.setInterval(250L, lcd_blynk); // เรียกใช้ฟั่งชั่น จอ LCD App  Blynk ทุก 1 วินาที
}

String httpGet(String pin)
{
  HTTPClient http;
  String token = "2QpNJdLQJzeWuI3l5vnXJiLFgtf387O4";
  String url = "https://blynk.cloud/external/api/get?token=" + token + "&" + pin;
  http.begin(url);
  int httpResponseCode = http.GET();
  // Check for a valid response
  if (httpResponseCode == 200)
  {

    response = http.getString();
    Serial.println("HTTP");
    Serial.println(response);
    blynk_stop(bool(response.toInt()));
  }
  // Close the connection
  http.end();
  return "ERROR";
}
void BlynkCheckConnect()
{
  bool result = Blynk.connect();
  if (result != true)
  {
    digitalWrite(LED_BUILTIN, LOW); // เมือเชื่อมต่อได้สั่งให้ led ที่บอดติดdigitalWrite(BLYNK_LED, HIGH);
   // digitalWrite(BLYNK_LED,LOW);

    setup_blynk();
  }
}
/*
void rootPage()
{
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content); // HTTP ส่ง status server
}
*/
void blynk_stop(bool status_bk)
{
  if (status_bk == true)
  {
    SelectMode = "Stop";
    StatusPC = "stop";
    program_end = true;
    step = 999;
    digitalWrite(relay_motor_cut,off_d);
    digitalWrite(relay_motor_lo,off_d);
   

  }
} 

//ฟังก์ชัน BLYNK_WRITE(V1) เป็นฟังก์ชันที่ใช้ในการรับค่าจากแอปพลิเคชัน Blynk ผ่าน Virtual Pin หมายเลข 1 (ในกรณีนี้คือ V1) และประมวลผลค่าที่ได้เพื่อใช้ในโปรแกรม Arduino
BLYNK_WRITE(V1)
{
  int pinValueStatusPg = param.asInt();     // ประกาศศตัวแปรรับค่าตัวเลข จาก  รับค่าจาก V0  .asInt(); เป็นการรับตัวเลข
  Serial.print("V1 Slider value is: "); // แสดงข้อมูลผ่านมอนิเตอร์
  Serial.println(pinValueStatusPg);     // นำข้อมูลที่อ่านค่าได้แสดงผ่านหน้าจอมอนิเตอร์
  /*ถ้า pinValueStatusPg = 1  ปุ่มกดมีค่าเป็น 1 และให้ทำการรันโปรแกรม
    แต่ถ้าไม่เท่า 1 ปุ่มกดมีค่าเป็น 0  และ status_program_eng == true และ หยุดทำงาน⤵
  */

  if (pinValueStatusPg == 1)//แต่ถ้า pinValueStatusPg =  1 ทำภายใน {} 
  {
    if (SelectMode == "Running")//แต่ถ้า SelectMode =  Running ทำภายใน {} 
    {
      Serial.print("V1 Slider value is: "); //แสดงค่า serial
      Blynk.virtualWrite(V1, 1);//ใช้ในการส่งข้อมูล (เขียนค่า) ไปยัง Virtual Pin หมายเลข 1 (V1) ในแอปพลิเคชัน Blynk ที่เชื่อมต่อกับ Arduino 
      Blynk.virtualWrite(V9, 0);//ใช้ในการส่งข้อมูล (เขียนค่า) ไปยัง Virtual Pin หมายเลข 9 (V9) ในแอปพลิเคชัน Blynk ที่เชื่อมต่อกับ Arduino 
      select_menu('#');//เรียกฟังก์ชัน select_menu('#') และส่ง ค่า # ไปในฟังก์ชัน
       Serial.println("ST PC :" + StatusPC);//แสดงค่า serial
    }
    //แต่ถ้าไม่
    else
    {
      Blynk.virtualWrite(V1, 0);//ใช้ในการส่งข้อมูล (เขียนค่า) ไปยัง Virtual Pin หมายเลข 1 (V1) ในแอปพลิเคชัน Blynk ที่เชื่อมต่อกับ Arduino 
      Blynk.virtualWrite(V9, 1);//ใช้ในการส่งข้อมูล (เขียนค่า) ไปยัง Virtual Pin หมายเลข 9 (V9) ในแอปพลิเคชัน Blynk ที่เชื่อมต่อกับ Arduino 
    }
  }
}

//bt on and off cut 
BLYNK_WRITE(V8)
{
  static bool pinValueCutint = param.asInt();// ประกาศศตัวแปรรับค่าตัวเลข จาก  รับค่าจาก V8  .asInt(); เป็นการรับตัวเลข
 //แต่ถ้า SelectMode =  Setting ทำภายใน {} 
  if (SelectMode = "Setting")
  {

// ถ้า pinValueCutint ถ้ามีค่า true และ ค่าที่(relay_motor_cut) เท่ากับ off_d ให้ทำใน{} 
    if (pinValueCutint == true && digitalRead(relay_motor_cut) == off_d)
    {
      digitalWrite(relay_motor_cut, on_d); // สั่งรีเลย์ มอสเตอร์ตัดเปิด
      Blynk.virtualWrite(V8, 1);//ใช้ในการส่งข้อมูล (เขียนค่า) ไปยัง Virtual Pin หมายเลข 8 (V8) ในแอปพลิเคชัน Blynk ที่เชื่อมต่อกับ Arduino 
    }
    // ถ้า pinValueCutint ถ้ามีค่า true และ ค่าที่(relay_motor_cut) เท่ากับ off_d ให้ทำใน{} 
    else if (pinValueCutint == true && digitalRead(relay_motor_cut) == on_d){
      digitalWrite(relay_motor_cut, off_d); // สั่งรีเลย์ มอสเตอร์ตัดเปิด
      Blynk.virtualWrite(V8, 0); //ใช้ในการส่งข้อมูล (เขียนค่า) ไปยัง Virtual Pin หมายเลข 8 (V8) ในแอปพลิเคชัน Blynk ที่เชื่อมต่อกับ Arduino 
    }
  
  }
}
//bt  mode 
BLYNK_WRITE(V5)
{
 bool pinValueMode = param.asInt(); // ประกาศศตัวแปรรับค่าตัวเลข จาก  รับค่าจาก V5  .asInt(); เป็นการรับตัวเลข
// ถ้า pinValueMode ถ้ามีค่า true และ program_end เท่ากับ true ให้ทำใน{} 
  if (pinValueMode == true && program_end == true)
  {
    //แต่ถ้า SelectMode =  Running ทำภายใน {} 
    if (SelectMode == "Running")
    {
      SelectMode = "Running";//ให้ตัวแปร SelectMode มีค่า Running
      pinValueCut = set_cut ;//ให้ตัวแปร pinValueCut มีค่าเท่าตัวแปร set_cut
    }
    select_menu('*');//เรียกฟังก์ชัน select_menu('*') และส่ง ค่า * ไปในฟังก์ชัน
  }
}
BLYNK_WRITE(V4)
{
  bool pinValueUp = param.asInt(); // ประกาศศตัวแปรรับค่าตัวเลข จาก  รับค่าจาก V4  .asInt(); เป็นการรับตัวเลข
// ถ้า pinValueUp ถ้ามีค่า true ให้ทำใน{} 
  if (pinValueUp == true)
  {
  //แต่ถ้า SelectMode =  SettingBK ทำภายใน {} 
    if (SelectMode == "SettingBK")
    {
      Serial.println("up Value cut");//แสดงค่า serial
      pinValueCut++;// เพิ่มค่าตัวแปร pinValueCut +1
    }
   
  }
}
BLYNK_WRITE(V3)
{
  static bool pinValuedow = param.asInt(); // ประกาศศตัวแปรรับค่าตัวเลข จาก  รับค่าจาก V2  .asInt(); เป็นการรับตัวเลข
// ถ้า pinValuedow ถ้ามีค่า true ให้ทำใน{} 
  if (pinValuedow == true)
  {
   // ถ้า SelectMode ถ้ามีค่า SettingBK  ให้ทำใน{} 
     if (SelectMode == "SettingBK" )
    {
      pinValueCut--;// ลดค่าตัวแปร pinValueCut -1
      Serial.println("up Value down");//แสดงค่า serial
  //ถ้า  pinValueCut น้อยกว่า 0 ให้ทำใน{} 
      if (pinValueCut < 0 )
      {
        pinValueCut = 0;//ให้ตัวแปร pinValueCut มีค่า 0
      }
    }
    //แต่ถ้า SelectMode ถ้ามีค่า Setting ให้ทำใน{} 
    else if (SelectMode == "Setting") 
    {
        //encoder_value = 0;
        select_menu('C');//เรียกฟังก์ชัน select_menu('C') และส่ง ค่า C ไปในฟังก์ชัน
    } 
    
  }
}

BLYNK_WRITE(V2)
{
  bool pinValueSet = param.asInt(); // ประกาศศตัวแปรรับค่าตัวเลข จาก  รับค่าจาก v2  .asInt(); เป็นการรับตัวเลข

  /*ถ้า pinValueSet =  1 และ status_program_eng =  true
    ย้าย ค่าที่ทำการตั้งค่า จากหน้าจอยามายังตัว โกโบตัวแปล หรือ ตัวแปลรวม
  */
 // ถ้า pinValueSet  ถ้ามีค่า true และ program_end เท่ากับ true ให้ทำใน{} 
  if (pinValueSet == true && program_end == true)
  {
// ถ้า SelectMode ถ้ามีค่า Setting ให้ทำใน{} 
  if (SelectMode == "Setting"){

    SelectMode = "SettingBK";//ให้ตัวแปร SelectMode มีค่า SettingBK
  } 
  // แต่ถ้า SelectMode ถ้ามีค่า SettingBK ให้ทำใน{} 
  else if ( SelectMode == "SettingBK")
  {
     
    set_cut = pinValueCut;               //  แปลงเป็น เมตร และ เก็บ set_cut
    SetupMinToPWM();               // ย้าย pinValueReload ไปเก็บ set_reload
    SelectMode = "blynk set";                // ให้ข้อมูลในตัวแปล setting_palamitor มีค่าเป็น blynk
         // กองข้อมูล set_cut และนำไปแสดงผล
    encoder_value = 0;
  }
    monitor_main(SelectMode); // เรียกใช้มอนิเตอร์เพื่อนำค่าปัจุบันมมาแสดง
  
  }
}

void blynk_fuction()
{
  // Portal.handleClient();
  Blynk.run(); // เรียกใช้ blynk  ทั้งหมด
  timer.run(); // Initiates BlynkTimer เรียกใช้ฟั่งชั่น Time ตามเวลาที่กำหนด
}

#endif