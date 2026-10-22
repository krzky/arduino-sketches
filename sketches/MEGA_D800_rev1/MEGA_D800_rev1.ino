#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_INA219.h>
#include "MAP.H"

String inval;

void(*lets_reset) (void) = 0;

void setup() {
  initial();
}

void loop() { /*------------------------------------- Main Loop ----------------------------------------*/
  int strt = digitalRead(btn_strt), rst = digitalRead(btn_rst), rest = digitalRead(key), cov = digitalRead(cover), bset = digitalRead(sett), selectState = digitalRead(sett), i = model, rstVal;
  int btn1 = digitalRead(sw1), btn2 = digitalRead(sw2), btn3 = digitalRead(sw3), btn4 = digitalRead(sw4);

  if (ngState)        { updateEEPROM(); NG1();} else{if (strt && !cov && rest && rst)   { LedNGoff();}}
  if (!selectState)   { int val = 0; lcd1.clear(); lcd1.setCursor(0, 1); lcd1.print("Hold for 2 secs");
                        while ((selectState == LOW) && (val < 2000)) { selectState = digitalRead(sett); val++; delay(1);}
                        if (val >= 2000) { Adjustment();} lcd_update();}
  if (lastBtn1 != btn1 || lastBtn2 != btn2 || lastBtn3 != btn3 || lastBtn4 != btn4){ delay(10); modelSel(); lcd_update();}

  if (!strt && rest)  { if (!cov){ measure();} else if(i < 1 && i > 10) { err04();} else{ lcCover();}}
  if (!strt && !rest) { }
  if (!rst && rest)   { rstVal = 1;}
  if (!rst && !rest)  { beep();}
  if (rst && !rest)   { Zero();}
} /*-------------------------------------------End of Loop---------------------------------------------*/

//========================================================================================================== MAIN VOIDS =============================================================================================
void measure() {
  char outval[5] = "0000\x00";
  float ampA1, ampA2, ampA3, ampB1, ampB2, ampB3, ampC1, ampC2, ampC3, ampD1, ampD2, ampD3;
  float ampA4, ampA5, ampA6, ampB4, ampB5, ampB6, ampC4, ampC5, ampC6, ampD4, ampD5, ampD6;
  float ampA7, ampA8, ampA9, ampB7, ampB8, ampB9, ampC7, ampC8, ampC9, ampD7, ampD8, ampD9;

  lcClear();
  lcd1.setCursor(4, 1); lcd1.print("= FCT D800 =");
  lcd1.setCursor(5, 2); lcd1.print("MEASURING");
  lock();

  start();
  lcd1.setCursor(0, 3); lcd1.print("==");
  ampA1 = AmM1.getCurrent_mA(); ampB1 = AmM2.getCurrent_mA();                 // 1ST measuring
  ampC1 = AmM3.getCurrent_mA(); ampD1 = AmM4.getCurrent_mA();
  ampA2 = AmM1.getCurrent_mA(); ampB2 = AmM2.getCurrent_mA();
  ampC2 = AmM3.getCurrent_mA(); ampD2 = AmM4.getCurrent_mA();
  ampA3 = AmM1.getCurrent_mA(); ampB3 = AmM2.getCurrent_mA();
  ampC3 = AmM3.getCurrent_mA(); ampD3 = AmM4.getCurrent_mA();
  delay(50);
  lcd1.setCursor(2, 3);
  lcd1.print("==");
  delay(50);
  lcd1.setCursor(4, 3);
  lcd1.print("==");
  delay(50);

  lcd1.setCursor(6, 3);
  lcd1.print("==");
  ampA4 = AmM1.getCurrent_mA(); ampB4 = AmM2.getCurrent_mA();                 // 1ST measuring
  ampC4 = AmM3.getCurrent_mA(); ampD4 = AmM4.getCurrent_mA();
  ampA5 = AmM1.getCurrent_mA(); ampB5 = AmM2.getCurrent_mA();
  ampC5 = AmM3.getCurrent_mA(); ampD5 = AmM4.getCurrent_mA();
  ampA6 = AmM1.getCurrent_mA(); ampB6 = AmM2.getCurrent_mA();
  ampC6 = AmM3.getCurrent_mA(); ampD6 = AmM4.getCurrent_mA();
  delay(50);
  lcd1.setCursor(8, 3);
  lcd1.print("==");
  delay(50);
  lcd1.setCursor(10, 3);
  lcd1.print("==");
  delay(50);

  lcd1.setCursor(12, 3);
  lcd1.print("==");
  ampA7 = AmM1.getCurrent_mA(); ampB7 = AmM2.getCurrent_mA();                 // 1ST measuring
  ampC7 = AmM3.getCurrent_mA(); ampD7 = AmM4.getCurrent_mA();
  ampA8 = AmM1.getCurrent_mA(); ampB8 = AmM2.getCurrent_mA();
  ampC8 = AmM3.getCurrent_mA(); ampD8 = AmM4.getCurrent_mA();
  ampA9 = AmM1.getCurrent_mA(); ampB9 = AmM2.getCurrent_mA();
  ampC9 = AmM3.getCurrent_mA(); ampD9 = AmM4.getCurrent_mA();
  delay(50);
  lcd1.setCursor(14, 3);
  lcd1.print("==");
  delay(50);
  lcd1.setCursor(16, 3);
  lcd1.print("==");

  valAmp1 = (ampA1 + ampA2 + ampA3 + ampA4 + ampA5 + ampA6 + ampA7 + ampA8 + ampA9) / 9;                                      // Calculate measurement
  valAmp2 = (ampB1 + ampB2 + ampB3 + ampB4 + ampB5 + ampB6 + ampB7 + ampB8 + ampB9) / 9;
  valAmp3 = (ampC1 + ampC2 + ampC3 + ampC4 + ampC5 + ampC6 + ampC7 + ampC8 + ampC9) / 9;
  valAmp4 = (ampD1 + ampD2 + ampD3 + ampD4 + ampD5 + ampD6 + ampD7 + ampD8 + ampD9) / 9;  delay(5);

  //  lcd1.setCursor(0, 0); lcd1.print(sen1); minA, maxA, minB, maxB;
  //  lcd1.setCursor(0, 1); lcd1.print(sen2);
  
  if((valAmp1 >= (minA+(minB/10))) && (valAmp1 <= (maxA+(maxB/10))))         {outval[0]='1';} else{}                  // state + sensor1
  if((valAmp2 >= (minA+(minB/10))) && (valAmp2 <= (maxA+(maxB/10))))         {outval[1]='1';} else{}                  // state + sensor2
  if((valAmp3 >= (minA+(minB/10))) && (valAmp3 <= (maxA+(maxB/10))))         {outval[2]='1';} else{}                  // state + sensor3
  if((valAmp4 >= (minA+(minB/10))) && (valAmp4 <= (maxA+(maxB/10))))         {outval[3]='1';} else{}                  // state + sensor4
  
  lcd1.setCursor(18, 3);
  lcd1.print("==");
  delay(100);
  
  start_end();                                                                // Turn off VCC
  result(outval);                                                             // Export result
}
void result(String val){
  int res = 0;

  if (val[0]=='1'){res++; valOK1++; bitClear(NGLamps,0);} else{ valNG1++; bitSet(NGLamps,0);}
  if (val[1]=='1'){res++; valOK2++; bitClear(NGLamps,1);} else{ valNG2++; bitSet(NGLamps,1);}
  if (val[2]=='1'){res++; valOK3++; bitClear(NGLamps,2);} else{ valNG3++; bitSet(NGLamps,2);}
  if (val[3]=='1'){res++; valOK4++; bitClear(NGLamps,3);} else{ valNG4++; bitSet(NGLamps,3);}

  LedOK(val); LedNG();
  stamp(val);
  lcd_update();
  if (res == 4){OK1();} else{ ngState = 1;}
}
