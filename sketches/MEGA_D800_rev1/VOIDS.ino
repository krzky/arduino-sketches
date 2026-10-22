void initial(){

//  Serial.setTimeout(5);
//  Serial.begin(115200);

  lcbegin(); AmBegin();
  delay(1);
  output(); input(); pinBegin();
  delay(1);
  eepromBegin();
  delay(1);

  if (ngState){ LedNG(); lcd_update(); NG1();}

//  modelSel();

  lcinit();
  int strt = 1;
  while (strt) {strt = digitalRead(btn_strt); lcwaitserial();}

  LedNGoff();
  lcClear();
  
//  int btn1 = digitalRead(sw1), btn2 = digitalRead(sw2), btn3 = digitalRead(sw3), btn4 = digitalRead(sw4);
  lastBtn1 = 1, lastBtn2 = 1, lastBtn3 = 1, lastBtn4 = 1;
  
  buzz();
  
  int str = digitalRead(btn_strt), rst = digitalRead(btn_rst), ky = digitalRead(key);
  if(!str && !rst && !ky){
    AmM1.setCalibration_16V_400mA();
    digitalWrite(pcb1, LOW);lcClear();
    float val = AmM1.getCurrent_mA();
    while(!ky){
      ky = digitalRead(key);
      lcd1.setCursor(7, 0); lcd1.print(val);
      delay(1000);
      val = AmM1.getCurrent_mA();
    }
    beep();
  }
}
void output(){
  pinMode(buzzer,OUTPUT);
  pinMode(stamp1,OUTPUT);
  pinMode(stamp2,OUTPUT);
  pinMode(stamp3,OUTPUT);
  pinMode(stamp4,OUTPUT);
  pinMode(solenoid1,OUTPUT);
  pinMode(solenoid2,OUTPUT);
  pinMode(pcb1,OUTPUT);
  pinMode(pcb2,OUTPUT);
  pinMode(pcb3,OUTPUT);
  pinMode(pcb4,OUTPUT);
  pinMode(led_ok1,OUTPUT);
  pinMode(led_ok2,OUTPUT);
  pinMode(led_ok3,OUTPUT);
  pinMode(led_ok4,OUTPUT);
  pinMode(led_ng1,OUTPUT);
  pinMode(led_ng2,OUTPUT);
  pinMode(led_ng3,OUTPUT);
  pinMode(led_ng4,OUTPUT);
  pinMode(NG,OUTPUT);
  pinMode(OK,OUTPUT);
}
void input(){
  pinMode(btn_strt,INPUT_PULLUP);
  pinMode(btn_rst,INPUT_PULLUP);
  pinMode(cover,INPUT_PULLUP);
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  pinMode(sw3,INPUT_PULLUP);
  pinMode(sw4,INPUT_PULLUP);
  pinMode(up,INPUT_PULLUP);
  pinMode(sett,INPUT_PULLUP);
  pinMode(dn,INPUT_PULLUP);
}
void pinBegin(){
  digitalWrite(pcb1,HIGH);
  digitalWrite(pcb2,HIGH);
  digitalWrite(pcb3,HIGH);
  digitalWrite(pcb4,HIGH);
  digitalWrite(buzzer,HIGH);
  digitalWrite(stamp1,HIGH);
  digitalWrite(stamp2,HIGH);
  digitalWrite(stamp3,HIGH);
  digitalWrite(stamp4,HIGH);
  digitalWrite(solenoid1,HIGH);
  digitalWrite(solenoid2,HIGH);
  digitalWrite(OK,HIGH);
  digitalWrite(NG,HIGH);
  digitalWrite(led_ok1,LOW);
  digitalWrite(led_ok2,LOW);
  digitalWrite(led_ok3,LOW);
  digitalWrite(led_ok4,LOW);
  digitalWrite(led_ng1,LOW);
  digitalWrite(led_ng2,LOW);
  digitalWrite(led_ng3,LOW);
  digitalWrite(led_ng4,LOW);
}
void AmBegin(){
  AmM1.begin(); AmM2.begin(); AmM3.begin(); AmM4.begin();
  AmM1.setCalibration_16V_400mA(); AmM2.setCalibration_16V_400mA(); AmM3.setCalibration_16V_400mA(); AmM4.setCalibration_16V_400mA();
}

void buzz(){                    // buzz sound
  digitalWrite(buzzer,LOW);
  digitalWrite(OK,LOW);
  digitalWrite(NG,LOW);
  digitalWrite(led_ok1,HIGH);
  digitalWrite(led_ok2,HIGH);
  digitalWrite(led_ok3,HIGH);
  digitalWrite(led_ok4,HIGH);
  digitalWrite(led_ng1,HIGH);
  digitalWrite(led_ng2,HIGH);
  digitalWrite(led_ng3,HIGH);
  digitalWrite(led_ng4,HIGH);
  delay(750);
  digitalWrite(buzzer,HIGH);
  digitalWrite(OK,HIGH);
  digitalWrite(NG,HIGH);
  digitalWrite(led_ok1,LOW);
  digitalWrite(led_ok2,LOW);
  digitalWrite(led_ok3,LOW);
  digitalWrite(led_ok4,LOW);
  digitalWrite(led_ng1,LOW);
  digitalWrite(led_ng2,LOW);
  digitalWrite(led_ng3,LOW);
  digitalWrite(led_ng4,LOW);
  lcd_update();
}
void beep(){                    // peep sound
  digitalWrite(buzzer,LOW);
  delay(50);
  digitalWrite(buzzer,HIGH);
  lets_reset();
}
void beepbeep(){                // peep 3x sound
  digitalWrite(buzzer,LOW);
  delay(75);
  digitalWrite(buzzer,HIGH);
  delay(50);
  digitalWrite(buzzer,LOW);
  delay(75);
  digitalWrite(buzzer,HIGH);
  delay(50);
  digitalWrite(buzzer,LOW);
  delay(75);
  digitalWrite(buzzer,HIGH);
}

void alloff(){
  digitalWrite(pcb1,HIGH);
  digitalWrite(pcb2,HIGH);
  digitalWrite(pcb3,HIGH);
  digitalWrite(pcb4,HIGH);
  digitalWrite(buzzer,HIGH);
  digitalWrite(led_ok1,LOW);
  digitalWrite(led_ok2,LOW);
  digitalWrite(led_ok3,LOW);
  digitalWrite(led_ok4,LOW);
  //unlock();  
}

void stamp(String val){
  if (val[0]=='1')digitalWrite(stamp1,LOW); else{}
  if (val[1]=='1')digitalWrite(stamp2,LOW); else{}
  if (val[2]=='1')digitalWrite(stamp3,LOW); else{}
  if (val[3]=='1')digitalWrite(stamp4,LOW); else{}
  delay(1000);
  digitalWrite(stamp1,HIGH); digitalWrite(stamp2,HIGH); digitalWrite(stamp3,HIGH); digitalWrite(stamp4,HIGH);
}
void lock(){                          // lock on
  digitalWrite(solenoid1,LOW); 
  digitalWrite(solenoid2,HIGH); 
  delay(300);
  digitalWrite(solenoid1,HIGH);
  delay(50);
}
void unlock(){                        // lock off
  digitalWrite(solenoid1,HIGH); 
  digitalWrite(solenoid2,LOW);
  delay(300);
  digitalWrite(solenoid2,HIGH);
  delay(50);
}

void start(){
  valAmp1 = valAmp2 = valAmp3 = valAmp4 = valAmp5 = valAmp6 = valAmp7 = valAmp8 = 0;
  digitalWrite(pcb1,LOW);
  digitalWrite(pcb2,LOW);
  digitalWrite(pcb3,LOW);
  digitalWrite(pcb4,LOW);
  digitalWrite(led_ok1,LOW);
  digitalWrite(led_ok2,LOW);
  digitalWrite(led_ok3,LOW);
  digitalWrite(led_ok4,LOW);
  digitalWrite(led_ng1,LOW);
  digitalWrite(led_ng2,LOW);
  digitalWrite(led_ng3,LOW);
  digitalWrite(led_ng4,LOW);
  digitalWrite(OK,HIGH);
  digitalWrite(NG,HIGH);
  delay(1000);
}
void start_end(){
  digitalWrite(pcb1,HIGH);
  digitalWrite(pcb2,HIGH);
  digitalWrite(pcb3,HIGH);
  digitalWrite(pcb4,HIGH);
}

void OK1(){
  int strt = digitalRead(btn_strt), cov = 0;
  digitalWrite(OK,LOW);
  updateEEPROM();
  unlock();
    while(!cov){
      cov = digitalRead(cover);
      strt = digitalRead(btn_strt);
      if (!strt){break;}
    }
    delay(10);
    if(cov){alloff();}
}
void NG1(){
    int strt = digitalRead(btn_strt), cov = 0, rst = 1, rest = 1;
    digitalWrite(NG,LOW);
    digitalWrite(buzzer,LOW);
    while(rest){
      rest = digitalRead(key);
    }
    Zero();
    while(!cov){
      cov = digitalRead(cover);
      strt = digitalRead(btn_strt);
      if (!strt){break;}
    }
    delay(10);
    if(cov){alloff();}
    delay(500);
}
void Zero(){
  int rst = 1, rest = 0;
  ngState = 0;
  digitalWrite(buzzer,HIGH);
  delay(100);
  while(!rest){
    delay(5);
    rest = digitalRead(key);
    rst = digitalRead(btn_rst);
    if (!rst){ rstVal=1;}
  }
  digitalWrite(NG,HIGH);
  if (rstVal){ valReset(); rstVal=0;}
  unlock();
  updateEEPROM();
}

void LedOK(String val){
  if (val[0]=='1'){digitalWrite(led_ok1,HIGH);} else{}
  if (val[1]=='1'){digitalWrite(led_ok2,HIGH);} else{}
  if (val[2]=='1'){digitalWrite(led_ok3,HIGH);} else{}
  if (val[3]=='1'){digitalWrite(led_ok4,HIGH);} else{}
//  if (val[4]=='1'){digitalWrite(led_ok5,HIGH);} else{}
//  if (val[5]=='1'){digitalWrite(led_ok6,HIGH);} else{}
//  if (val[6]=='1'){digitalWrite(led_ok7,HIGH);} else{}
//  if (val[7]=='1'){digitalWrite(led_ok8,HIGH);} else{}
}
void LedNG(){
  //int pin = 38;
  for(int bits = 7, pins = 34; bits > -1; bits--){
    pins--;
    if(NGLamps & (1 << bits)){digitalWrite(pins,HIGH);}
  }
}
void LedNGoff(){
  digitalWrite(led_ng1,LOW);
  digitalWrite(led_ng2,LOW);
  digitalWrite(led_ng3,LOW);
  digitalWrite(led_ng4,LOW);
}

void valReset(){
  valOK1 = 0;
  valOK2 = 0;
  valOK3 = 0;
  valOK4 = 0;
  valNG1 = 0;
  valNG2 = 0;
  valNG3 = 0;
  valNG4 = 0;
  NGLamps = 0;
}

void Adjustment() {
  modelAdjustment();
  updateEEPROM();
}
void modelAdjustment(){
  loops = 1;
  int val = 0, pos = 1;
  int a = 0, b = 0, c = 0, d = 0;
  int selectState = digitalRead(sett);
  int incrementState;
  int decrementState;

  if      (model ==  1){ a = minA = minAmp1; b = minB = minAmp1d; c = maxA = maxAmp1, d = maxB = maxAmp1d;}
  else if (model ==  2){ a = minA = minAmp2; b = minB = minAmp2d; c = maxA = maxAmp2, d = maxB = maxAmp2d;}
  else if (model ==  3){ a = minA = minAmp3; b = minB = minAmp3d; c = maxA = maxAmp3, d = maxB = maxAmp3d;}
  else if (model ==  4){ a = minA = minAmp4; b = minB = minAmp4d; c = maxA = maxAmp4, d = maxB = maxAmp4d;}
  else if (model ==  5){ a = minA = minAmp5; b = minB = minAmp5d; c = maxA = maxAmp5, d = maxB = maxAmp5d;}
  else if (model ==  6){ a = minA = minAmp6; b = minB = minAmp6d; c = maxA = maxAmp6, d = maxB = maxAmp6d;}
  else if (model ==  7){ a = minA = minAmp7; b = minB = minAmp7d; c = maxA = maxAmp7, d = maxB = maxAmp7d;}
  else if (model ==  8){ a = minA = minAmp8; b = minB = minAmp8d; c = maxA = maxAmp8, d = maxB = maxAmp8d;}
  else if (model ==  9){ a = minA = minAmp9; b = minB = minAmp9d; c = maxA = maxAmp9, d = maxB = maxAmp9d;}
  else if (model ==  10){ a = minA = minAmp10; b = minB = minAmp10d; c = maxA = maxAmp10, d = maxB = maxAmp10d;}

  lcd1.setCursor(0, 1); lcd1.print("                    ");
  lcd1.setCursor(3, 1); lcd1.print("Min");
  lcd1.setCursor(13, 1); lcd1.print("Max");
  lcValUpdate(a, b, c, d);
  delay(1);
  lastSelectState = selectState;
  while (lastSelectState == selectState) {
    selectState = digitalRead(sett);
  }
  lastSelectState = selectState;

  while (loops) {
    selectState = digitalRead(sett);
    incrementState = digitalRead(up);
    decrementState = digitalRead(dn);
    
    if (selectState == LOW) {
      lcValUpdate(a, b, c, d);
      pos = posAdjustment(pos);
      while (selectState == LOW) {
        selectState = digitalRead(sett);
        val++;
        if (val >= 2000) {
          break;
        }
        delay(1);
      }
      if (val >= 2000) {
        loops = 0;
      } else { val = 0;}
    }

    if (incrementState == LOW) {
      if (pos == 1) { a++; if (a > 400) { a = 0;}}
      if (pos == 2) { b++; if (b > 9)   { b = 0;}}
      if (pos == 3) { c++; if (c > 400) { c = 0;}}
      if (pos == 4) { d++; if (d > 9)   { d = 0;}}
      modelApply(a, b, c, d); lcValUpdate(minA, minB, maxA, maxB);
      while (incrementState == LOW) { incrementState = digitalRead(up);}
      runtime = 0;
    }
    if (decrementState == LOW) {
      if (pos == 1) { a--; if (a < 0) { a = 400;}}
      if (pos == 2) { b--; if (b < 0) { b = 9;  }}
      if (pos == 3) { c--; if (c < 0) { c = 400;}}
      if (pos == 4) { d--; if (d < 0) { d = 9;  }}
      modelApply(a, b, c, d); lcValUpdate(minA, minB, maxA, maxB);
      while (decrementState == LOW) { decrementState = digitalRead(dn);}
      runtime = 0;
    }
    blinks(pos);
    delay(1);
  }

  modelApply(a, b, c, d);
  updateEEPROM();
}
void lcValUpdate(int a, int b, int c, int d) {
  if (a < 100) { lcd1.setCursor(1, 2); lcd1.print(" ");} else { lcd1.setCursor(1, 2);}
  lcd1.print(a); lcd1.print(","); lcd1.print(b); lcd1.print("0mA");

  if (c < 100) { lcd1.setCursor(11, 2); lcd1.print(" ");} else { lcd1.setCursor(11, 2);}
  lcd1.print(c); lcd1.print(","); lcd1.print(d); lcd1.print("0mA");
}
int posAdjustment(int pos) {
  int selectState = digitalRead(sett);
  if (selectState == LOW) { pos ++; if (pos > 4) { pos = 1;}}

  return pos;
}
void blinks(int pos) {
  runtime++;
  if (runtime - milis >= 440) {
    milis = runtime;
    if (pos == 1) { lcd1.setCursor(1, 2); lcd1.print("   ");}
    else if (pos == 2) { lcd1.setCursor(5, 2); lcd1.print(" ");}
    else if (pos == 3) { lcd1.setCursor(11, 2); lcd1.print("   ");}
    else if (pos == 4) { lcd1.setCursor(15, 2); lcd1.print(" ");}
  }
  else if (runtime - milis >= 415) { lcValUpdate(minA, minB, maxA, maxB);}
}
void modelSel() {
  int btn1 = digitalRead(sw1), btn2 = digitalRead(sw2), btn3 = digitalRead(sw3), btn4 = digitalRead(sw4);
  delay(10);
  btn1 = digitalRead(sw1), btn2 = digitalRead(sw2), btn3 = digitalRead(sw3), btn4 = digitalRead(sw4);
  delay(10);
  btn1 = digitalRead(sw1), btn2 = digitalRead(sw2), btn3 = digitalRead(sw3), btn4 = digitalRead(sw4);
  if      (!btn1 && !btn2 && !btn3 && !btn4){ model =  1;}  //1
  else if ( btn1 && !btn2 && !btn3 && !btn4){ model =  2;}  //2
  else if (!btn1 &&  btn2 && !btn3 && !btn4){ model =  3;}  //3
  else if ( btn1 &&  btn2 && !btn3 && !btn4){ model =  4;}  //4
  else if (!btn1 && !btn2 &&  btn3 && !btn4){ model =  5;}  //5
  else if ( btn1 && !btn2 &&  btn3 && !btn4){ model =  6;}  //6
  else if (!btn1 &&  btn2 &&  btn3 && !btn4){ model =  7;}  //7
  else if ( btn1 &&  btn2 &&  btn3 && !btn4){ model =  8;}  //8
  else if (!btn1 && !btn2 && !btn3 &&  btn4){ model =  9;}  //9
  else if ( btn1 && !btn2 && !btn3 &&  btn4){ model = 10;}  //10
  else if ( btn1 &&  btn2 &&  btn3 &&  btn4){ model =  0; err04();} // for(;;);  }  //ERR04 BCD sw error

  if      (model ==  1){ minA = minAmp1; minB = minAmp1d; maxA = maxAmp1, maxB = maxAmp1d;}
  else if (model ==  2){ minA = minAmp2; minB = minAmp2d; maxA = maxAmp2, maxB = maxAmp2d;}
  else if (model ==  3){ minA = minAmp3; minB = minAmp3d; maxA = maxAmp3, maxB = maxAmp3d;}
  else if (model ==  4){ minA = minAmp4; minB = minAmp4d; maxA = maxAmp4, maxB = maxAmp4d;}
  else if (model ==  5){ minA = minAmp5; minB = minAmp5d; maxA = maxAmp5, maxB = maxAmp5d;}
  else if (model ==  6){ minA = minAmp6; minB = minAmp6d; maxA = maxAmp6, maxB = maxAmp6d;}
  else if (model ==  7){ minA = minAmp7; minB = minAmp7d; maxA = maxAmp7, maxB = maxAmp7d;}
  else if (model ==  8){ minA = minAmp8; minB = minAmp8d; maxA = maxAmp8, maxB = maxAmp8d;}
  else if (model ==  9){ minA = minAmp9; minB = minAmp9d; maxA = maxAmp9, maxB = maxAmp9d;}
  else if (model == 10){ minA = minAmp10; minB = minAmp10d; maxA = maxAmp10, maxB = maxAmp10d;}
  
  lcClear();
  lcd1.setCursor(2,1); lcd1.print("Model Changed!");
  lcd1.setCursor(5,2); lcd1.print("Model "); lcd1.print(model - 1);
  
  if ( btn1 &&  btn2 &&  btn3 &&  btn4){ model =  0; err04();} // for(;;);  }  //ERR04 BCD sw error
  delay(1000);

  //  lcd_update();
  if ( btn1 &&  btn2 &&  btn3 &&  btn4){ model =  0; err04();} // for(;;);  }  //ERR04 BCD sw error

  lastBtn1 = btn1, lastBtn2 = btn2, lastBtn3 = btn3, lastBtn4 = btn4;

//  else if (btn1 && btn2 && btn3 && btn4){}
//  else if (btn1 && btn2 && btn3 && btn4){}
//  else if (btn1 && btn2 && btn3 && btn4){}
//  else if (btn1 && btn2 && btn3 && btn4){}
//  else if (btn1 && btn2 && btn3 && btn4){}

}
void modelApply(int a, int b, int c, int d) {
  if      (model ==  1){ minA = minAmp1 = a; minB = minAmp1d = b; maxA = maxAmp1 = c, maxB = maxAmp1d = d;}
  else if (model ==  2){ minA = minAmp2 = a; minB = minAmp2d = b; maxA = maxAmp2 = c, maxB = maxAmp2d = d;}
  else if (model ==  3){ minA = minAmp3 = a; minB = minAmp3d = b; maxA = maxAmp3 = c, maxB = maxAmp3d = d;}
  else if (model ==  4){ minA = minAmp4 = a; minB = minAmp4d = b; maxA = maxAmp4 = c, maxB = maxAmp4d = d;}
  else if (model ==  5){ minA = minAmp5 = a; minB = minAmp5d = b; maxA = maxAmp5 = c, maxB = maxAmp5d = d;}
  else if (model ==  6){ minA = minAmp6 = a; minB = minAmp6d = b; maxA = maxAmp6 = c, maxB = maxAmp6d = d;}
  else if (model ==  7){ minA = minAmp7 = a; minB = minAmp7d = b; maxA = maxAmp7 = c, maxB = maxAmp7d = d;}
  else if (model ==  8){ minA = minAmp8 = a; minB = minAmp8d = b; maxA = maxAmp8 = c, maxB = maxAmp8d = d;}
  else if (model ==  9){ minA = minAmp9 = a; minB = minAmp9d = b; maxA = maxAmp9 = c, maxB = maxAmp9d = d;}
  else if (model == 10){ minA = minAmp10 = a; minB = minAmp10d = b; maxA = maxAmp10 = c, maxB = maxAmp10d = d;}
}

// LCD voids //
void lcbegin(){
  lcd1.init();
  lcd1.backlight();
  lcd1.setCursor(2,0); lcd1.print("WWW.GEMAPRO.COM");
  lcd1.setCursor(4,2); lcd1.print(" FCT  D800 ");
  delay(100);
  lcd1.setCursor(0,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(2,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(4,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(6,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(8,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(10,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(12,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(14,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(16,3); lcd1.print("__");
  delay(100);
  lcd1.setCursor(18,3); lcd1.print("__");
  delay(200);
}
void lcinit(){
  lcClear();
  delay(5);
  lcd1.setCursor(2,0); lcd1.print("WWW.GEMAPRO.COM");
  lcd1.setCursor(0,0); lcd1.print("|");
  lcd1.setCursor(0,1); lcd1.print("|");
  lcd1.setCursor(0,2); lcd1.print("|");
  lcd1.setCursor(0,3); lcd1.print("|");
  lcd1.setCursor(5,1); lcd1.print("FCT  D800");
  lcd1.setCursor(5,2); lcd1.print("R E A D Y");
  lcd1.setCursor(19,0); lcd1.print("|");
  lcd1.setCursor(19,1); lcd1.print("|");
  lcd1.setCursor(19,2); lcd1.print("|");
  lcd1.setCursor(19,3); lcd1.print("|");
}
void lcwaitserial(){
  lcd1.setCursor(1,3); lcd1.print("                  ");
  lcd1.setCursor(3,3); lcd1.print("__");
  lcd1.setCursor(7,3); lcd1.print("__");
  lcd1.setCursor(11,3); lcd1.print("__");
  lcd1.setCursor(15,3); lcd1.print("__");
  delay(300);
  lcd1.setCursor(1,3); lcd1.print("                  ");
  lcd1.setCursor(1,3); lcd1.print("__");
  lcd1.setCursor(5,3); lcd1.print("__");
  lcd1.setCursor(9,3); lcd1.print("__");
  lcd1.setCursor(13,3); lcd1.print("__");
  lcd1.setCursor(17,3); lcd1.print("__");
  delay(300);
}
void lcready(){
  lcClear();
  lcd1.setCursor(1,1); lcd1.print("                  ");
  
  lcd1.setCursor(0,0); lcd1.print("|");
  lcd1.setCursor(0,1); lcd1.print("|");
  lcd1.setCursor(0,2); lcd1.print("|");
  lcd1.setCursor(0,3); lcd1.print("|");

  lcd1.setCursor(6,1); lcd1.print("FCT  D800");
  lcd1.setCursor(6,1);
  
  lcd1.setCursor(19,0); lcd1.print("|");
  lcd1.setCursor(19,1); lcd1.print("|");
  lcd1.setCursor(19,2); lcd1.print("|");
  lcd1.setCursor(19,3); lcd1.print("|");
  
  delay(300);
  lcd1.setCursor(9,3); lcd1.print("__");
  delay(300);
  lcd1.setCursor(7,3);  lcd1.print("__");
  lcd1.setCursor(11,3); lcd1.print("__");
  delay(300);
  lcd1.setCursor(5,3);  lcd1.print("__");
  lcd1.setCursor(13,3); lcd1.print("__");
  delay(300);
  lcd1.setCursor(3,3);  lcd1.print("__");
  lcd1.setCursor(15,3); lcd1.print("__");
  delay(300);
  lcd1.setCursor(1,3);  lcd1.print("__");
  lcd1.setCursor(17,3); lcd1.print("__");
  delay(300);
  lcd1.setCursor(1,3); lcd1.print("                  ");
}
void lcCover(){
  lcClear();
  lcd1.setCursor(4, 1); lcd1.print("|| ERR02 ||");
  lcd1.setCursor(4, 2); lcd1.print("|| COVER ||");
  delay(300);
}
void err03(){
  lcClear();
  lcd1.setCursor(4, 1); lcd1.print("|| ERR 03 ||");
  lcd1.setCursor(4, 2); lcd1.print("|| AMPMTR ||");
  delay(300);
}
void err04(){
  lcClear();
  lcd1.setCursor(4, 1); lcd1.print("|| ERR04 ||");
  lcd1.setCursor(4, 2); lcd1.print("|| BCDSW ||");
  delay(300);
}
void lcd_update(){
  lcClear();
  lcd1.setCursor(0, 0); lcd1.print("1="); lcd1.print(valAmp1);
  lcd1.setCursor(9, 0); lcd1.print("OK"); lcd1.print(valOK1);
  lcd1.setCursor(15, 0); lcd1.print("NG"); lcd1.print(valNG1);

  lcd1.setCursor(0, 1); lcd1.print("2="); lcd1.print(valAmp2);
  lcd1.setCursor(9, 1); lcd1.print("OK"); lcd1.print(valOK2);
  lcd1.setCursor(15, 1); lcd1.print("NG"); lcd1.print(valNG2);

  lcd1.setCursor(0, 2); lcd1.print("3="); lcd1.print(valAmp3);
  lcd1.setCursor(9, 2); lcd1.print("OK"); lcd1.print(valOK3);
  lcd1.setCursor(15, 2); lcd1.print("NG"); lcd1.print(valNG3);

  lcd1.setCursor(0, 3); lcd1.print("4="); lcd1.print(valAmp4);
  lcd1.setCursor(9, 3); lcd1.print("OK"); lcd1.print(valOK4);
  lcd1.setCursor(15, 3); lcd1.print("NG"); lcd1.print(valNG4);

  //  lcd1.setCursor(6, 0); lcd1.print("FCT D800");
}
void lcClear(){
  lcd1.clear(); //lcd2.clear();
}

//EEPROM FUNCTIONS=========================================================
void updateEEPROM(){
  if (ngState != lastngState){ EEPROM_write(notgood, ngState); lastngState = ngState;}
  if (NGLamps != lastNGLamps){ EEPROM_write(dNGLamps, NGLamps); lastNGLamps = NGLamps;}
  if (valOK1 != lastvalOK1){ EEPROM_write(dOK1, valOK1); lastvalOK1 = valOK1;}
  if (valOK2 != lastvalOK2){ EEPROM_write(dOK2, valOK2); lastvalOK2 = valOK2;}
  if (valOK3 != lastvalOK3){ EEPROM_write(dOK3, valOK3); lastvalOK3 = valOK3;}
  if (valOK4 != lastvalOK4){ EEPROM_write(dOK4, valOK4); lastvalOK4 = valOK4;}
  if (valNG1 != lastvalNG1){ EEPROM_write(dNG1, valNG1); lastvalNG1 = valNG1;}
  if (valNG2 != lastvalNG2){ EEPROM_write(dNG2, valNG2); lastvalNG2 = valNG2;}
  if (valNG3 != lastvalNG3){ EEPROM_write(dNG3, valNG3); lastvalNG3 = valNG3;}
  if (valNG4 != lastvalNG4){ EEPROM_write(dNG4, valNG4); lastvalNG4 = valNG4;}
  if (maxAmp1 != lastmaxAmp1){ EEPROM_write(dmxAmp1, maxAmp1); lastmaxAmp1 = maxAmp1;}
  if (maxAmp2 != lastmaxAmp2){ EEPROM_write(dmxAmp2, maxAmp2); lastmaxAmp2 = maxAmp2;}
  if (maxAmp3 != lastmaxAmp3){ EEPROM_write(dmxAmp3, maxAmp3); lastmaxAmp3 = maxAmp3;}
  if (maxAmp4 != lastmaxAmp4){ EEPROM_write(dmxAmp4, maxAmp4); lastmaxAmp4 = maxAmp4;}
  if (maxAmp5 != lastmaxAmp5){ EEPROM_write(dmxAmp5, maxAmp5); lastmaxAmp5 = maxAmp5;}
  if (maxAmp6 != lastmaxAmp6){ EEPROM_write(dmxAmp6, maxAmp6); lastmaxAmp6 = maxAmp6;}
  if (maxAmp7 != lastmaxAmp7){ EEPROM_write(dmxAmp7, maxAmp7); lastmaxAmp7 = maxAmp7;}
  if (maxAmp8 != lastmaxAmp8){ EEPROM_write(dmxAmp8, maxAmp8); lastmaxAmp8 = maxAmp8;}
  if (maxAmp9 != lastmaxAmp9){ EEPROM_write(dmxAmp9, maxAmp9); lastmaxAmp9 = maxAmp9;}
  if (maxAmp10 != lastmaxAmp10){ EEPROM_write(dmxAmp10, maxAmp10); lastmaxAmp10 = maxAmp10;}
  
  if (maxAmp1d != lastmaxAmp1d){ EEPROM_write(dmxAmp1d, maxAmp1d); lastmaxAmp1d = maxAmp1d;}
  if (maxAmp2d != lastmaxAmp2d){ EEPROM_write(dmxAmp2d, maxAmp2d); lastmaxAmp2d = maxAmp2d;}
  if (maxAmp3d != lastmaxAmp3d){ EEPROM_write(dmxAmp3d, maxAmp3d); lastmaxAmp3d = maxAmp3d;}
  if (maxAmp4d != lastmaxAmp4d){ EEPROM_write(dmxAmp4d, maxAmp4d); lastmaxAmp4d = maxAmp4d;}
  if (maxAmp5d != lastmaxAmp5d){ EEPROM_write(dmxAmp5d, maxAmp5d); lastmaxAmp5d = maxAmp5d;}
  if (maxAmp6d != lastmaxAmp6d){ EEPROM_write(dmxAmp6d, maxAmp6d); lastmaxAmp6d = maxAmp6d;}
  if (maxAmp7d != lastmaxAmp7d){ EEPROM_write(dmxAmp7d, maxAmp7d); lastmaxAmp7d = maxAmp7d;}
  if (maxAmp8d != lastmaxAmp8d){ EEPROM_write(dmxAmp8d, maxAmp8d); lastmaxAmp8d = maxAmp8d;}
  if (maxAmp9d != lastmaxAmp9d){ EEPROM_write(dmxAmp9d, maxAmp9d); lastmaxAmp9d = maxAmp9d;}
  if (maxAmp10d != lastmaxAmp10d){ EEPROM_write(dmxAmp10d, maxAmp10d); lastmaxAmp10d = maxAmp10d;}
  
  if (minAmp1 != lastminAmp1){ EEPROM_write(dmnAmp1, minAmp1); lastminAmp1 = minAmp1;}
  if (minAmp2 != lastminAmp2){ EEPROM_write(dmnAmp2, minAmp2); lastminAmp1 = minAmp2;}
  if (minAmp3 != lastminAmp3){ EEPROM_write(dmnAmp3, minAmp3); lastminAmp1 = minAmp3;}
  if (minAmp4 != lastminAmp4){ EEPROM_write(dmnAmp4, minAmp4); lastminAmp1 = minAmp4;}
  if (minAmp5 != lastminAmp5){ EEPROM_write(dmnAmp5, minAmp5); lastminAmp1 = minAmp5;}
  if (minAmp6 != lastminAmp6){ EEPROM_write(dmnAmp6, minAmp6); lastminAmp1 = minAmp6;}
  if (minAmp7 != lastminAmp7){ EEPROM_write(dmnAmp7, minAmp7); lastminAmp1 = minAmp7;}
  if (minAmp8 != lastminAmp8){ EEPROM_write(dmnAmp8, minAmp8); lastminAmp1 = minAmp8;}
  if (minAmp9 != lastminAmp9){ EEPROM_write(dmnAmp9, minAmp9); lastminAmp1 = minAmp9;}
  if (minAmp10 != lastminAmp10){ EEPROM_write(dmnAmp10, minAmp10); lastminAmp10 = minAmp10;}
  
  if (minAmp1d != lastminAmp1d){ EEPROM_write(dmnAmp1d, minAmp1d); lastminAmp1d = minAmp1d;}
  if (minAmp2d != lastminAmp2d){ EEPROM_write(dmnAmp2d, minAmp2d); lastminAmp2d = minAmp2d;}
  if (minAmp3d != lastminAmp3d){ EEPROM_write(dmnAmp3d, minAmp3d); lastminAmp3d = minAmp3d;}
  if (minAmp4d != lastminAmp4d){ EEPROM_write(dmnAmp4d, minAmp4d); lastminAmp4d = minAmp4d;}
  if (minAmp5d != lastminAmp5d){ EEPROM_write(dmnAmp5d, minAmp5d); lastminAmp5d = minAmp5d;}
  if (minAmp6d != lastminAmp6d){ EEPROM_write(dmnAmp6d, minAmp6d); lastminAmp6d = minAmp6d;}
  if (minAmp7d != lastminAmp7d){ EEPROM_write(dmnAmp7d, minAmp7d); lastminAmp7d = minAmp7d;}
  if (minAmp8d != lastminAmp8d){ EEPROM_write(dmnAmp8d, minAmp8d); lastminAmp8d = minAmp8d;}
  if (minAmp9d != lastminAmp9d){ EEPROM_write(dmnAmp9d, minAmp9d); lastminAmp9d = minAmp9d;}
  if (minAmp10d != lastminAmp10d){ EEPROM_write(dmnAmp10d, minAmp10d); lastminAmp10d = minAmp10d;}
}
void eepromBegin(){
  byte error, ep_Address = 0x50;
  int rest = digitalRead(key), nodetect = 0;
  lcd1.setCursor(0,1); lcd1.print("EEPROM INITIALIZING");
  delay(100);

  lcd1.setCursor(0,3); lcd1.print("==|>");

  Wire.beginTransmission(ep_Address);
  error = Wire.endTransmission();

  lcd1.setCursor(2,3); lcd1.print("==|>");

  if (error == 0){ nodetect++;}
  if (error == 4){ }
  if (!nodetect){
    lcd1.setCursor(0,1); lcd1.print("                   ");
    lcd1.setCursor(4, 1); lcd1.print("|| ERR01 ||");
    lcd1.setCursor(4, 2); lcd1.print("EEPROM ERROR");
    lcd1.setCursor(2, 3); lcd1.print("KEY FOR RELOAD!");
    while (!nodetect){
      rest = digitalRead(key);
      delay(100);
      if (!rest){
        while (!rest){
          rest = digitalRead(key);
          if (rest){ beep();}
        }
      }
    }
  }

  ngState = EEPROM_read(notgood);
  lastngState = ngState;
  NGLamps = EEPROM_read(dNGLamps);
  lastNGLamps = NGLamps;

  lcd1.setCursor(4,3); lcd1.print("==|>");

  valOK1 = EEPROM_read(dOK1);  lastvalOK1 = valOK1;
  valOK2 = EEPROM_read(dOK2);  lastvalOK2 = valOK2;
  valOK3 = EEPROM_read(dOK3);  lastvalOK3 = valOK3;
  valOK4 = EEPROM_read(dOK4);  lastvalOK4 = valOK4;

  lcd1.setCursor(6,3); lcd1.print("==|>");

  valNG1 = EEPROM_read(dNG1);  lastvalNG1 = valNG1;
  valNG2 = EEPROM_read(dNG2);  lastvalNG2 = valNG2;
  valNG3 = EEPROM_read(dNG3);  lastvalNG3 = valNG3;
  valNG4 = EEPROM_read(dNG4);  lastvalNG4 = valNG4;

  lcd1.setCursor(8,3); lcd1.print("==|>");

  maxAmp1 = lastmaxAmp1 = EEPROM_read(dmxAmp1);
  maxAmp2 = lastmaxAmp2 = EEPROM_read(dmxAmp2);
  maxAmp3 = lastmaxAmp3 = EEPROM_read(dmxAmp3);
  maxAmp4 = lastmaxAmp4 = EEPROM_read(dmxAmp4);
  maxAmp5 = lastmaxAmp5 = EEPROM_read(dmxAmp5);
  maxAmp6 = lastmaxAmp6 = EEPROM_read(dmxAmp6);
  maxAmp7 = lastmaxAmp7 = EEPROM_read(dmxAmp7);
  maxAmp8 = lastmaxAmp8 = EEPROM_read(dmxAmp8);
  maxAmp9 = lastmaxAmp9 = EEPROM_read(dmxAmp9);
  maxAmp10 = lastmaxAmp10 = EEPROM_read(dmxAmp10);

  lcd1.setCursor(10,3); lcd1.print("==|>");

  maxAmp1d = lastmaxAmp1d = EEPROM_read(dmxAmp1d);
  maxAmp2d = lastmaxAmp2d = EEPROM_read(dmxAmp2d);
  maxAmp3d = lastmaxAmp3d = EEPROM_read(dmxAmp3d);
  maxAmp4d = lastmaxAmp4d = EEPROM_read(dmxAmp4d);
  maxAmp5d = lastmaxAmp5d = EEPROM_read(dmxAmp5d);
  maxAmp6d = lastmaxAmp6d = EEPROM_read(dmxAmp6d);
  maxAmp7d = lastmaxAmp7d = EEPROM_read(dmxAmp7d);
  maxAmp8d = lastmaxAmp8d = EEPROM_read(dmxAmp8d);
  maxAmp9d = lastmaxAmp9d = EEPROM_read(dmxAmp9d);
  maxAmp10d = lastmaxAmp10d = EEPROM_read(dmxAmp10d);

  lcd1.setCursor(12,3); lcd1.print("==|>");

  minAmp1 = lastminAmp1 = EEPROM_read(dmnAmp1);
  minAmp2 = lastminAmp2 = EEPROM_read(dmnAmp2);
  minAmp3 = lastminAmp3 = EEPROM_read(dmnAmp3);
  minAmp4 = lastminAmp4 = EEPROM_read(dmnAmp4);
  minAmp5 = lastminAmp5 = EEPROM_read(dmnAmp5);
  minAmp6 = lastminAmp6 = EEPROM_read(dmnAmp6);
  minAmp7 = lastminAmp7 = EEPROM_read(dmnAmp7);
  minAmp8 = lastminAmp8 = EEPROM_read(dmnAmp8);
  minAmp9 = lastminAmp9 = EEPROM_read(dmnAmp9);
  minAmp10 = lastminAmp10 = EEPROM_read(dmnAmp10);

  lcd1.setCursor(14,3); lcd1.print("==|>");

  minAmp1d = lastminAmp1d = EEPROM_read(dmnAmp1d);
  minAmp2d = lastminAmp2d = EEPROM_read(dmnAmp2d);
  minAmp3d = lastminAmp3d = EEPROM_read(dmnAmp3d);
  minAmp4d = lastminAmp4d = EEPROM_read(dmnAmp4d);
  minAmp5d = lastminAmp5d = EEPROM_read(dmnAmp5d);
  minAmp6d = lastminAmp6d = EEPROM_read(dmnAmp6d);
  minAmp7d = lastminAmp7d = EEPROM_read(dmnAmp7d);
  minAmp8d = lastminAmp8d = EEPROM_read(dmnAmp8d);
  minAmp9d = lastminAmp9d = EEPROM_read(dmnAmp9d);
  minAmp10d = lastminAmp10d = EEPROM_read(dmnAmp10d);
  
  lcd1.setCursor(16,3); lcd1.print("==|>");

  if (!valOK1 && !valOK2 && !valOK3 && !valOK4 && !valNG1 && !valNG2 && !valNG3 && !valNG4){// && !valOK5 && !valOK6 && !valOK7 && !valOK8// && !valNG5 && !valNG6 && !valNG7 && !valNG8){
    //lcClear();
    lcd1.setCursor(0,1); lcd1.print("                    ");
    lcd1.setCursor(1,1); lcd1.print("All data reseted!");
    delay(1000);
  } else {}

  lcd1.setCursor(18,3); lcd1.print("==");
  delay(300);
  updateEEPROM();
  lcd1.setCursor(0,1); lcd1.print("                    ");
  lcd1.setCursor(1,1); lcd1.print("EEPROM INITIALIZED");
  delay(1000);
}

//write to EEPROM==========================================================
void EEPROM_write(int eaddress, byte val){
  int i2c_address = 0x50;
  Wire.beginTransmission(i2c_address);
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.write(val);
  Wire.endTransmission(); delay(5);
}
//read from EEPROM=========================================================
byte EEPROM_read(int eaddress){
  int i2c_address = 0x50;
  byte rcvData = 0xFF;
  Wire.beginTransmission(i2c_address);
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(i2c_address, 1);
  rcvData = Wire.read();
  return rcvData;
}
