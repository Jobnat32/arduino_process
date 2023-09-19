#ifndef HelpGoble
#define HelpGoble

#define relay_motor_lo 25
#define relay_motor_cut 26
#define relay_lam 27
#define reset_board 15
#define on_d 0
#define off_d 1
#define SPTimeCut 5000 //5วินาที
#define SPTimeRunFeed 7000 //7วินาที
#define SPTimeCounter  10000 //11วินาที

char value_keypad;
int step = 10;//step ซึ่งเป็นตัวแปรประเภทจำนวนเต็ม (integer) และมีค่าเริ่มต้นเท่ากับ 10.
bool status_blynk = false; //คือการประกาศตัวแปร status_blynk ที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น false คือเป็นค่าทางตรรกะ (boolean) ที่บ่งชี้ว่า Blynk (เซอร์วิสหรือแพลตฟอร์มการเชื่อมต่ออุปกรณ์ออนไลน์) อยู่ในสถานะเชื่อมต่อหรือไม่ โดย false บ่งชี้ว่าไม่เชื่อมต่อในสถานะเริ่มต้น.

//SM.h
String SelectMode = "Setting";//ประกาศตัวแปรซึ่งเป็นตัวแปรประเภทสตริง (String) และกำหนดค่าเริ่มต้นให้เป็นสตริง "Setting" 
String StatusPC = "?";//ประกาศตัวแปร StatusPC ซึ่งเป็นตัวแปรประเภทสตริง (String) และกำหนดค่าเริ่มต้นให้เป็นสตริง "?" 
//PC use
// 
bool  brake_read = true;//คือการประกาศตัวแปรที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น true
bool program_end = true;////คือการประกาศตัวแปรที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น true
bool back_process_rolad = false;////คือการประกาศตัวแปรที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น false
bool CutCable = false;//คือการประกาศตัวแปรที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น false
bool runfeedcable = false;//คือการประกาศตัวแปรที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น false
bool Strat_motorP = false;//คือการประกาศตัวแปรที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น false
bool stoped_program = false;//คือการประกาศตัวแปรที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น false

bool set_mode_blynk = false;//คือการประกาศตัวแปร  ที่มีประเภทข้อมูลเป็น bool ซึ่งมีค่าเริ่มต้นเป็น false

int check_time = 0;//เป็นตัวแปรประเภทจำนวนเต็ม (integer) และมีค่าเริ่มต้นเท่ากับ 0.
int check_timeRC = 0;//เป็นตัวแปรประเภทจำนวนเต็ม (integer) และมีค่าเริ่มต้นเท่ากับ 0.
int check_timeFR = 0;//เป็นตัวแปรประเภทจำนวนเต็ม (integer) และมีค่าเริ่มต้นเท่ากับ 0.
int set_bk = 1;//เป็นตัวแปรประเภทจำนวนเต็ม (integer) และมีค่าเริ่มต้นเท่ากับ 1.
//status string blynk 
String status_Blynk;//ประกาศตัวแปรซึ่งเป็นตัวแปรประเภทสตริง (String) และกำหนดค่าเริ่มต้นให้เป็นสตริง " " 
String response; //ประกาศตัวแปรซึ่งเป็นตัวแปรประเภทสตริง (String) และกำหนดค่าเริ่มต้นให้เป็นสตริง " " 
String ST_LCD_B = "BLynk On or Off?";//ประกาศตัวแปรซึ่งเป็นตัวแปรประเภทสตริง (String) และกำหนดค่าเริ่มต้นให้เป็นสตริง "BLynk On or Off?" 
//boolen blynk 
float lenght_blnk;//การประกาศตัวแปรซึ่งเป็นตัวแปรประเภท float ซึ่งใช้ในการเก็บค่าทศนิยม 


//float blynk
float pinValueReload;//การประกาศตัวแปรซึ่งเป็นตัวแปรประเภท float ซึ่งใช้ในการเก็บค่าทศนิยม 
float pinValueCut;//การประกาศตัวแปรซึ่งเป็นตัวแปรประเภท float ซึ่งใช้ในการเก็บค่าทศนิยม 
#endif