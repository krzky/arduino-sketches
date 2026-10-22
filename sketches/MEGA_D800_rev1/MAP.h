Adafruit_INA219 AmM1;
Adafruit_INA219 AmM2(0x41);
Adafruit_INA219 AmM3(0x44);
Adafruit_INA219 AmM4(0x45);
//Adafruit_INA219 AmM5(0x44);
//Adafruit_INA219 AmM6(0x45);
//Adafruit_INA219 AmM7(0x46);
//Adafruit_INA219 AmM8(0x47);

LiquidCrystal_I2C lcd1(0x27, 20, 4);
//LiquidCrystal_I2C lcd2(0x26, 20, 4);

// OUTPUT
#define solenoid1    14
#define solenoid2    15
#define pcb1         2
#define pcb2         3
#define pcb3         4
#define pcb4         5
//#define pcb5         9
//#define pcb6        10
//#define pcb7        11
//#define pcb8        12

#define led_ok1     22
#define led_ok2     23
#define led_ok3     24
#define led_ok4     25
#define led_ng1     26
#define led_ng2     27
#define led_ng3     28
#define led_ng4     29
//#define led_ng1     30
//#define led_ng2     31
//#define led_ng3     32
//#define led_ng4     33
//#define led_ng5     34
//#define led_ng6     35
//#define led_ng7     36
//#define led_ng8     37

#define NG          12
#define OK          11
#define buzzer      10

#define stamp1      6
#define stamp2      7
#define stamp3      8
#define stamp4      9
//#define stamp5      45
//#define stamp6      46
//#define stamp7      47
//#define stamp8      48

// INPUT
#define sw1         A0
#define sw2         A1
#define sw3         A2
#define sw4         A3
#define up          A4
#define sett        A5
#define dn          A6
//#define in_sen8     A7
#define cover       A12
#define btn_strt    A13
#define btn_rst     A14
#define key         A15

int loops = 1;
int led = 13;
boolean lastSelectState = false, State = false;
unsigned int selpos = 0, milis = 0;
unsigned int runtime = 0, lapsed = 0;

int rstVal;
int lastngState, ngState, notgood = 1;  //======= EEprom ADDRESSES =======

int lastvalOK1, valOK1, dOK1 = 2;
int lastvalOK2, valOK2, dOK2 = 3;
int lastvalOK3, valOK3, dOK3 = 4;
int lastvalOK4, valOK4, dOK4 = 5;
int lastvalOK5, valOK5, dOK5 = 6;
int lastvalOK6, valOK6, dOK6 = 7;
int lastvalOK7, valOK7, dOK7 = 8;
int lastvalOK8, valOK8, dOK8 = 9;

int lastvalNG1, valNG1, dNG1 = 10;
int lastvalNG2, valNG2, dNG2 = 11;
int lastvalNG3, valNG3, dNG3 = 12;
int lastvalNG4, valNG4, dNG4 = 13;
int lastvalNG5, valNG5, dNG5 = 14;
int lastvalNG6, valNG6, dNG6 = 15;
int lastvalNG7, valNG7, dNG7 = 16;
int lastvalNG8, valNG8, dNG8 = 17;

int dNGLamps = 18;
byte lastNGLamps = B00000000, NGLamps = B00000000;

float valAmp1, valAmp2, valAmp3, valAmp4, valAmp5, valAmp6, valAmp7, valAmp8;

int model;
int minA, maxA, minB, maxB;                     // Model measure point
int lastBtn1, lastBtn2, lastBtn3, lastBtn4;     // Model check point

int lastmaxAmp1, maxAmp1, lastmaxAmp1d, maxAmp1d;
int lastmaxAmp2, maxAmp2, lastmaxAmp2d, maxAmp2d;
int lastmaxAmp3, maxAmp3, lastmaxAmp3d, maxAmp3d;
int lastmaxAmp4, maxAmp4, lastmaxAmp4d, maxAmp4d;
int lastmaxAmp5, maxAmp5, lastmaxAmp5d, maxAmp5d;
int lastmaxAmp6, maxAmp6, lastmaxAmp6d, maxAmp6d;
int lastmaxAmp7, maxAmp7, lastmaxAmp7d, maxAmp7d;
int lastmaxAmp8, maxAmp8, lastmaxAmp8d, maxAmp8d;
int lastmaxAmp9, maxAmp9, lastmaxAmp9d, maxAmp9d;
int lastmaxAmp10, maxAmp10, lastmaxAmp10d, maxAmp10d;
int lastmaxAmp11, maxAmp11, lastmaxAmp11d, maxAmp11d;
int lastmaxAmp12, maxAmp12, lastmaxAmp12d, maxAmp12d;
int lastmaxAmp13, maxAmp13, lastmaxAmp13d, maxAmp13d;
int lastmaxAmp14, maxAmp14, lastmaxAmp14d, maxAmp14d;
int lastmaxAmp15, maxAmp15, lastmaxAmp15d, maxAmp15d;
int lastmaxAmp16, maxAmp16, lastmaxAmp16d, maxAmp16d;

int lastminAmp1, minAmp1, lastminAmp1d, minAmp1d;
int lastminAmp2, minAmp2, lastminAmp2d, minAmp2d;
int lastminAmp3, minAmp3, lastminAmp3d, minAmp3d;
int lastminAmp4, minAmp4, lastminAmp4d, minAmp4d;
int lastminAmp5, minAmp5, lastminAmp5d, minAmp5d;
int lastminAmp6, minAmp6, lastminAmp6d, minAmp6d;
int lastminAmp7, minAmp7, lastminAmp7d, minAmp7d;
int lastminAmp8, minAmp8, lastminAmp8d, minAmp8d;
int lastminAmp9, minAmp9, lastminAmp9d, minAmp9d;
int lastminAmp10, minAmp10, lastminAmp10d, minAmp10d;
int lastminAmp11, minAmp11, lastminAmp11d, minAmp11d;
int lastminAmp12, minAmp12, lastminAmp12d, minAmp12d;
int lastminAmp13, minAmp13, lastminAmp13d, minAmp13d;
int lastminAmp14, minAmp14, lastminAmp14d, minAmp14d;
int lastminAmp15, minAmp15, lastminAmp15d, minAmp15d;
int lastminAmp16, minAmp16, lastminAmp16d, minAmp16d;

int dmxAmp1 = 19, dmxAmp1d = 51;
int dmxAmp2 = 20, dmxAmp2d = 52;
int dmxAmp3 = 21, dmxAmp3d = 53;
int dmxAmp4 = 22, dmxAmp4d = 54;
int dmxAmp5 = 23, dmxAmp5d = 55;
int dmxAmp6 = 24, dmxAmp6d = 56;
int dmxAmp7 = 25, dmxAmp7d = 57;
int dmxAmp8 = 26, dmxAmp8d = 58;
int dmxAmp9 = 27, dmxAmp9d = 59;
int dmxAmp10 = 28, dmxAmp10d = 60;
int dmxAmp11 = 29, dmxAmp11d = 61;
int dmxAmp12 = 30, dmxAmp12d = 62;
int dmxAmp13 = 31, dmxAmp13d = 63;
int dmxAmp14 = 32, dmxAmp14d = 64;
int dmxAmp15 = 33, dmxAmp15d = 65;
int dmxAmp16 = 34, dmxAmp16d = 66;

int dmnAmp1 = 35, dmnAmp1d = 67;
int dmnAmp2 = 36, dmnAmp2d = 68;
int dmnAmp3 = 37, dmnAmp3d = 69;
int dmnAmp4 = 38, dmnAmp4d = 70;
int dmnAmp5 = 39, dmnAmp5d = 71;
int dmnAmp6 = 40, dmnAmp6d = 72;
int dmnAmp7 = 41, dmnAmp7d = 73;
int dmnAmp8 = 42, dmnAmp8d = 74;
int dmnAmp9 = 43, dmnAmp9d = 75;
int dmnAmp10 = 44, dmnAmp10d = 76;
int dmnAmp11 = 45, dmnAmp11d = 77;
int dmnAmp12 = 46, dmnAmp12d = 78;
int dmnAmp13 = 47, dmnAmp13d = 79;
int dmnAmp14 = 48, dmnAmp14d = 80;
int dmnAmp15 = 49, dmnAmp15d = 81;
int dmnAmp16 = 50, dmnAmp16d = 82;
