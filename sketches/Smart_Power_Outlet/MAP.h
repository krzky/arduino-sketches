#include <stdio.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HttpClient.h>
#include "Arduino.h"

// SoftwareSerial pzemSWSerial(8, 7);
// PZEM004T pzem(pzemSWSerial);

#define REG_VOLTAGE     0x0000
#define REG_CURRENT_L   0x0001
#define REG_CURRENT_H   0X0002
#define REG_POWER_L     0x0003
#define REG_POWER_H     0x0004
#define REG_ENERGY_L    0x0005
#define REG_ENERGY_H    0x0006
#define REG_FREQUENCY   0x0007
#define REG_PF          0x0008
#define REG_ALARM       0x0009
#define CMD_RHR         0x03
#define CMD_RIR         0X04
#define CMD_WSR         0x06
#define CMD_CAL         0x41
#define CMD_REST        0x42
#define WREG_ALARM_THR  0x0001
#define WREG_ADDR       0x0002
#define UPDATE_TIME     200
#define RESPONSE_SIZE   32
#define READ_TIMEOUT    100
#define INVALID_ADDRESS 0x00
#ifndef PZEM004T_H
#define PZEM004T_H
#define PZEM_DEFAULT_ADDR   0xF8
#define PZEM_BAUD_RATE      9600

#define NUMFLAKES     10

#define LOGO_WIDTH    128
#define LOGO_HEIGHT   32

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

#define XPOS   0
#define YPOS   1
#define DELTAY 2

#define buzz 4

int OFF = 0, RED = 1, GREEN = 2, BLUE = 3, YELLOW = 4, WHITEe = 10; //, RED = 1, RED = 1,

static const unsigned char PROGMEM logo_bmp[] =
{ B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00011111,B10000000,B00000001,B11111111,B11000001,B11111100,B00000111,B11110000,
  B00011111,B10000000,B00000011,B11111111,B11000001,B11111100,B00000111,B11110000,
  B00011111,B10000000,B00000111,B11111111,B11100001,B11111110,B00001111,B11100000,
  B00011111,B10000000,B00001111,B11111111,B11100000,B11111110,B00001111,B11100000,
  B00011111,B10000000,B00011111,B11111111,B11110000,B11111111,B00011111,B11100000,
  B00011111,B10000000,B00111111,B11000111,B11110000,B01111111,B00011111,B11000000,
  B00011111,B10000000,B01111111,B10010111,B11110000,B01111111,B10111111,B11000000,
  B00011111,B10000001,B11111111,B00111011,B11111000,B00111111,B10111111,B10000000,
  B00011111,B10000011,B11111110,B01111011,B11111000,B00111111,B11111111,B10000000,
  B00011111,B10000111,B11111100,B11111001,B11111100,B00011111,B11111111,B00000000,
  B00011111,B10001111,B11111001,B11111101,B11111100,B00011111,B11111111,B00000000,
  B00011111,B00011111,B11110011,B11111101,B11111110,B00001111,B11111110,B00000000,
  B00011111,B10111111,B11000011,B11111000,B11111110,B00001111,B11111110,B00000000,
  B00011111,B11111111,B10000011,B11111000,B11111110,B00001111,B11111110,B00000000,
  B00011111,B11111111,B00000111,B11110000,B01111111,B00000111,B11111100,B00000000,
  B00011111,B11111111,B00000111,B11110000,B01111111,B00000111,B11111100,B00000000,
  B00011111,B11111111,B10001111,B11100000,B00111111,B10000011,B11111000,B00000000,
  B00011111,B11111111,B11001111,B11100000,B00111111,B10000011,B11111000,B00000000,
  B00011111,B00011111,B11011111,B11111111,B11111111,B11000111,B11110000,B00000000,
  B00011111,B10001111,B11011111,B11111111,B11111111,B11000111,B11110000,B00000000,
  B00011111,B10000111,B10011111,B11111111,B11111111,B11001111,B11100000,B00000000,
  B00011111,B10000011,B10111111,B11111111,B11111111,B11101111,B11100000,B00000000,
  B00011111,B10000001,B10111111,B11111111,B11111111,B11111111,B11100000,B00000000,
  B00011111,B10000000,B01111111,B11111111,B11111111,B11111111,B11000000,B00000000,
  B00011111,B10000000,B01111111,B00000000,B00000111,B11111111,B11000000,B00000000,
  B00011111,B10000000,B11111110,B01100000,B00000011,B11111111,B10000000,B00000000,
  B00011111,B10000000,B11111110,B11111000,B00000011,B11111111,B10000000,B00000000,
  B00011111,B10000000,B11111100,B11111100,B00000001,B11111111,B00000000,B00000000,
  B00011111,B10000001,B11111101,B11111110,B00000001,B11111111,B00000000,B00000000,
  B00011111,B10000001,B11111001,B11111111,B00000000,B11111110,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
};

byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
// Name of the server we want to connect to
const char kHostname[] = "arduino.cc";
// Path to download (this is the bit after the hostname in the URL
// that you want to download
const char kPath[] = "/";
// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

class PZEM004T {
  public:
    PZEM004T(uint8_t receivePin, uint8_t transmitPin, uint8_t addr = PZEM_DEFAULT_ADDR);
    PZEM004T(SoftwareSerial& port, uint8_t addr = PZEM_DEFAULT_ADDR);
    PZEM004T(Stream& port, uint8_t addr = PZEM_DEFAULT_ADDR);
    PZEM004T(HardwareSerial& port, uint8_t addr = PZEM_DEFAULT_ADDR);
    PZEM004T(HardwareSerial* port, uint8_t addr = PZEM_DEFAULT_ADDR) : PZEM004T(*port, addr) {};
    PZEM004T() {};
    ~PZEM004T();
    float voltage();
    float current();
    float power();
    float energy();
    float frequency();
    float pf();
    bool setAddress(uint8_t addr);
    uint8_t getAddress();
    uint8_t readAddress(bool update = false);
    bool setPowerAlarm(uint16_t watts);
    bool getPowerAlarm();
    bool resetEnergy();
    void search();
  private:
    Stream* _serial;
    bool _isSoft;
    SoftwareSerial* localSWserial = nullptr;
    uint8_t _addr;
    bool _isConnected;
    struct {
      float voltage;
      float current;
      float power;
      float energy;
      float frequency;
      float pf;
      uint16_t alarms;
    }  _currentValues;
    uint64_t _lastRead;
    void init(Stream* port, bool isSoft, uint8_t addr);                                                         // Init common to all constructors
    bool updateValues();                                                                                        // Get most up to date values from device registers and cache them
    uint16_t receive(uint8_t *resp, uint16_t len);                                                              // Receive len bytes into a buffer
    bool sendCmd8(uint8_t cmd, uint16_t rAddr, uint16_t val, bool check = false, uint16_t slave_addr = 0xFFFF); // Send 8 byte command
    void setCRC(uint8_t *buf, uint16_t len);                                                                    // Set the CRC for a buffer
    bool checkCRC(const uint8_t *buf, uint16_t len);                                                            // Check CRC of buffer
    uint16_t CRC16(const uint8_t *data, uint16_t len);                                                          // Calculate CRC of buffer
};

#ifdef PZEM004T_DEBUG
#ifndef PZEM004T_DEBUG_SERIAL
#define PZEM004T_DEBUG_SERIAL Serial
#endif
extern HardwareSerial PZEM004T_DEBUG_SERIAL;
void printBuf(uint8_t* buffer, uint16_t len) {
  for (uint16_t i = 0; i < len; i++) {
    char temp[6];
    sprintf(temp, "%.2x ", buffer[i]);
    PZEM004T_DEBUG_SERIAL.print(temp);
  }
  PZEM004T_DEBUG_SERIAL.println();
}
#define DEBUG(...) PZEM004T_DEBUG_SERIAL.print(__VA_ARGS__)
#define DEBUGLN(...) PZEM004T_DEBUG_SERIAL.println(__VA_ARGS__)
#define DEBUGBUF(buf, len) printBuf(buf, len)
#else
#define DEBUG(...)
#define DEBUGLN(...)
#define DEBUGBUF(buf, len)
#endif
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
EthernetClient client;