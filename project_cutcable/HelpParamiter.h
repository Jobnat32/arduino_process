#ifndef HelpParamiter//ทำสิ่งที่คุณต้องการเมื่อ HelpParamiter มีการใช้งาน
#define HelpParamiter
#include "HlepLibary.h"

float set_cut = 0.3;
int spool = 225; // ระสายม้วนสายไฟก่อน
float SpPwmCut,calcular_compriment,SpPwmCutErr,SpcheckPwm;
//int myError[] = {0, 1.90  , 1.00 ,0.13, -1.20 ,-1.43 , -3.45, -3.77 , -5.57 , -5.67 , -5.90};

//11.88 PWM  =  1mm.
void SetupMinToPWM(){
    SpPwmCut = (11.88 * ((set_cut * 1000)-spool)) + (11.88*2) ;  // คำนวนค่า PWM to  1 mm.
    //SpcheckPwm = (11.88 * (spool - 5)) + (11.88 + (set_cut  - 0.001)); // คำนวนค่า PWM setcut 
    SpPwmCutErr = 0;

}

//float calcular(float endcodder) <- ไม่ได้เรียกใช่งานแล้ว
//float calcular(float endcodder)
//{      /* สูตร C = 2πr π = 3.142  End_code = 31.7 mm r =  End_code / 2
//  float       
//                                            */
//  Serial.println(endcodder);
//  float turn =  (endcodder/2)/LPD3806; //หาจำนวนรอของ endcodder
//  float calcular_rotary = (100);//(2 * 3.142 * 31.5 / 2);//(101); // คำนวนความยาวที่  end code หมุน 1 รอบ
//  calcular_compriment = (calcular_rotary * turn)/10;   // คำนวณความยามที่ได้จากจำนวณรอบ
// return calcular_compriment;
//
//}

#endif