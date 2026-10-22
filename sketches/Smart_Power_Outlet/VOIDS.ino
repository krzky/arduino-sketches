void initial() {
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  pinMode(buzz, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.setTimeout(5);
  Serial.begin(115200);

  Serial.println("draw display init");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  BuzzON();
  delay(75);
  BuzzOFF();
  delay(100);
  BuzzON();
  delay(75);
  BuzzOFF();

  LED(WHITEe);
  delay(2000);

  testdrawbitmap();
  display.display();
  delay(2000);

  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  // while (Ethernet.begin(mac) == 0) {
  //   Serial.println("Failed to configure Ethernet using DHCP");
  //   Serial.println("Retrying . . ."); Ethernet.begin(mac);
  // }
  printIPAddress();
}

void printIPAddress() {
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}
void httpinit(){
  int err =0;
  EthernetClient c;
  HttpClient http(c);
  if (err == 0){
    Serial.println("startedRequest ok");

    err = http.responseStatusCode();
    if (err >= 0){
      Serial.print("Got status code: ");
      Serial.println(err);

      err = http.skipResponseHeaders();
      if (err >= 0){
        int bodyLen = http.contentLength();
        Serial.print("Content length is: ");
        Serial.println(bodyLen);
        Serial.println();
        Serial.println("Body returned follows:");
      
        // Now we've got to the body, so we can print it out
        unsigned long timeoutStart = millis();
        char c;
        // Whilst we haven't timed out & haven't reached the end of the body
        while ( (http.connected() || http.available()) &&
               ((millis() - timeoutStart) < kNetworkTimeout) ){
            if (http.available()){
                c = http.read();
                // Print out this character
                Serial.print(c);
               
                bodyLen--;
                // We read something, reset the timeout counter
                timeoutStart = millis();
            }
            else{
                // We haven't got any data, so let's pause to allow some to
                // arrive
                delay(kNetworkDelay);
            }
        }
      }
      else{
        Serial.print("Failed to skip response headers: ");
        Serial.println(err);
      }
    }
    else{    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();
}
void testdrawbitmap(void) {
  display.clearDisplay();
  display.drawBitmap( 32, 0, logo_bmp, 63, 32, 1);
  display.display();
  delay(1000);
}
void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  for (f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for (;;) {
    display.clearDisplay();
    
    for (f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display();
    delay(200);

    for (f = 0; f < NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      if (icons[f][YPOS] >= display.height()) {
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}
void ethMaintain() {
  switch (Ethernet.maintain())
  {
    case 1:
      Serial.println("Error: renewed fail");
      break;

    case 2:
      Serial.println("Renewed success");

      printIPAddress();
      break;

    case 3:
      Serial.println("Error: rebind fail");
      break;

    case 4:
      Serial.println("Rebind success");

      printIPAddress();
      break;

    default:
      break;

  }
}

void LED(int val){
  Serial.print("LED = "); Serial.println(val);
  digitalWrite(2, HIGH);
  if (!val){                   //OFF
    digitalWrite(2, LOW);
    digitalWrite(3,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
  }
  else if (val == 1){          //RED
    digitalWrite(3,220);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
  }
  else if (val == 2){          //GREEN
    digitalWrite(3,HIGH);
    digitalWrite(5,230);
    digitalWrite(6,HIGH);
  }
  else if (val == 3){          //BLUE
    digitalWrite(3,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,220);
  }
  else if (val == 4){          //YELLOW
    digitalWrite(3,220);
    digitalWrite(5,230);
    digitalWrite(6,HIGH);
  }
  else if (val == 10){          //WHITE
    analogWrite(3,220);
    analogWrite(5,230);
    analogWrite(6,220);
  }
}

void BuzzON() {
  digitalWrite(buzz, LOW);
}
void BuzzOFF() {
  digitalWrite(buzz, HIGH);
}

void serialCall(int val) {
  if (val == 1) {
    Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    if (isnan(voltage)) {
      Serial.println("Error reading voltage");
    } else if (isnan(current)) {
      Serial.println("Error reading current");
    } else if (isnan(power)) {
      Serial.println("Error reading power");
    } else if (isnan(energy)) {
      Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
      Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
      Serial.println("Error reading power factor");
    } else {

      Serial.print("Voltage: ");
      Serial.print(voltage);
      Serial.println("V");
      Serial.print("Current: ");
      Serial.print(current);
      Serial.println("A");
      Serial.print("Power: ");
      Serial.print(power);
      Serial.println("W");
      Serial.print("Energy: ");
      Serial.print(energy, 3);
      Serial.println("kWh");
      Serial.print("Frequency: ");
      Serial.print(frequency, 1);
      Serial.println("Hz");
      Serial.print("PF: ");
      Serial.println(pf);
    }

    Serial.println();
    delay(2000);
  }
}

PZEM004T::PZEM004T(uint8_t receivePin, uint8_t transmitPin, uint8_t addr) {
  localSWserial = new SoftwareSerial(receivePin, transmitPin); // We will need to clean up in destructor
  localSWserial->begin(PZEM_BAUD_RATE);
  init((Stream *)localSWserial, true, addr);
}
PZEM004T::PZEM004T(SoftwareSerial& port, uint8_t addr) {
  port.begin(PZEM_BAUD_RATE);
  init((Stream *)&port, true, addr);
}
PZEM004T::PZEM004T(Stream& port, uint8_t addr) {
  init(&port, true, addr);
}
PZEM004T::PZEM004T(HardwareSerial& port, uint8_t addr) {
  port.begin(PZEM_BAUD_RATE);
  init((Stream *)&port, false, addr);
}
PZEM004T::~PZEM004T() {
  if (this->localSWserial != nullptr) {
    delete this->localSWserial;
  }
}
float PZEM004T::voltage() {
  if (!updateValues()) // Update vales if necessary
    return NAN;
  return _currentValues.voltage;
}
float PZEM004T::current() {
  if (!updateValues()) // Update vales if necessary
    return NAN;
  return _currentValues.current;
}
float PZEM004T::power() {
  if (!updateValues()) // Update vales if necessary
    return NAN;
  return _currentValues.power;
}
float PZEM004T::energy() {
  if (!updateValues()) // Update vales if necessary
    return NAN;
  return _currentValues.energy;
}
float PZEM004T::frequency(){
  if (!updateValues()) // Update vales if necessary
    return NAN;
  return _currentValues.frequency;
}
float PZEM004T::pf() {
  if (!updateValues()) // Update vales if necessary
    return NAN;
  return _currentValues.pf;
}
bool PZEM004T::sendCmd8(uint8_t cmd, uint16_t rAddr, uint16_t val, bool check, uint16_t slave_addr) {
  uint8_t sendBuffer[8]; // Send buffer
  uint8_t respBuffer[8];
  if ((slave_addr == 0xFFFF) ||
      (slave_addr < 0x01) ||
      (slave_addr > 0xF7)) {
    slave_addr = _addr;
  }
  sendBuffer[0] = slave_addr;                   // Set slave address
  sendBuffer[1] = cmd;
  sendBuffer[2] = (rAddr >> 8) & 0xFF;     // Set high byte of register address
  sendBuffer[3] = (rAddr) & 0xFF;
  sendBuffer[4] = (val >> 8) & 0xFF;       // Set high byte of register value
  sendBuffer[5] = (val) & 0xFF;
  setCRC(sendBuffer, 8);
  _serial->write(sendBuffer, 8);
  if (check) {
    if (!receive(respBuffer, 8)) { // if check enabled, read the response
      return false;
    }
    for (uint8_t i = 0; i < 8; i++) {
      if (sendBuffer[i] != respBuffer[i])
        return false;
    }
  }
  return true;
}
bool PZEM004T::setAddress(uint8_t addr) {
  if (addr < 0x01 || addr > 0xF7) // sanity check
    return false;
  if (!sendCmd8(CMD_WSR, WREG_ADDR, addr, true))
    return false;
  _addr = addr;
  return true;
}
uint8_t PZEM004T::readAddress(bool update) {
  static uint8_t response[7];
  uint8_t addr = 0;
  if (!sendCmd8(CMD_RHR, WREG_ADDR, 0x01, false))
    return INVALID_ADDRESS;
  if (receive(response, 7) != 7) { // Something went wrong
    return INVALID_ADDRESS;
  }
  addr = ((uint32_t)response[3] << 8 | (uint32_t)response[4]);
  if (update) {
    _addr = addr;
  }
  return addr;
}
uint8_t PZEM004T::getAddress() {
  return _addr;
}
bool PZEM004T::setPowerAlarm(uint16_t watts) {
  if (watts > 25000) { // Sanitych check
    watts = 25000;
  }
  if (!sendCmd8(CMD_WSR, WREG_ALARM_THR, watts, true))
    return false;

  return true;
}
bool PZEM004T::getPowerAlarm() {
  if (!updateValues()) // Update vales if necessary
    return NAN; // Update did not work, return NAN
  return _currentValues.alarms != 0x0000;
}
void PZEM004T::init(Stream* port, bool isSoft, uint8_t addr) {
  if (addr < 0x01 || addr > 0xF8) // Sanity check of address
    addr = PZEM_DEFAULT_ADDR;
  _addr = addr;
  this->_serial = port;
  this->_isSoft = isSoft;
  _lastRead = 0;
  _lastRead -= UPDATE_TIME;
  _isConnected = false; // We have not received anything yet...
}
bool PZEM004T::updateValues() {
  static uint8_t response[25];
  if (_lastRead + UPDATE_TIME > millis()) {
    return true;
  }
  DEBUGLN("Updating Values");
  sendCmd8(CMD_RIR, 0x00, 0x0A, false);
  if (receive(response, 25) != 25) { // Something went wrong
    return false;
  }
  _currentValues.voltage = ((uint32_t)response[3] << 8 | (uint32_t)response[4]) / 10.0;
  _currentValues.current = ((uint32_t)response[5] << 8 | (uint32_t)response[6] | (uint32_t)response[7] << 24 | (uint32_t)response[8] << 16) / 1000.0;
  _currentValues.power =   ((uint32_t)response[9] << 8 | (uint32_t)response[10] | (uint32_t)response[11] << 24 | (uint32_t)response[12] << 16) / 10.0;
  _currentValues.energy =  ((uint32_t)response[13] << 8 | (uint32_t)response[14] | (uint32_t)response[15] << 24 | (uint32_t)response[16] << 16) / 1000.0;
  _currentValues.frequency  = ((uint32_t)response[17] << 8 | (uint32_t)response[18]) / 10.0;
  _currentValues.pf         = ((uint32_t)response[19] << 8 | (uint32_t)response[20]) / 100.0;
  _currentValues.alarms     = ((uint32_t)response[21] << 8 | (uint32_t)response[22]);
  _lastRead = millis();
  return true;
}

bool PZEM004T::resetEnergy() {
  uint8_t buffer[] = {0x00, CMD_REST, 0x00, 0x00};
  uint8_t reply[5];
  buffer[0] = _addr;
  setCRC(buffer, 4);
  _serial->write(buffer, 4);
  uint16_t length = receive(reply, 5);
  if (length == 0 || length == 5) { return false;}
  return true;
}

uint16_t PZEM004T::receive(uint8_t *resp, uint16_t len) {
  if (_isSoft)
    ((SoftwareSerial *)_serial)->listen();
  unsigned long startTime = millis(); // Start time for Timeout
  uint8_t index = 0; // Bytes we have read
  while ((index < len) && (millis() - startTime < READ_TIMEOUT))
  {
    if (_serial->available() > 0){
      uint8_t c = (uint8_t)_serial->read();
      resp[index++] = c;
    }
    yield();  // do background netw tasks while blocked for IO (prevents ESP watchdog trigger)
  }

  if (!checkCRC(resp, index)) {
    _isConnected = false; // We are no longer connected
    return 0;
  }
  _isConnected = true; // We received a reply
  return index;
}
bool PZEM004T::checkCRC(const uint8_t *buf, uint16_t len) {
  if (len <= 2) // Sanity check
    return false;
  uint16_t crc = CRC16(buf, len - 2); // Compute CRC of data
  return ((uint16_t)buf[len - 2]  | (uint16_t)buf[len - 1] << 8) == crc;
}
void PZEM004T::setCRC(uint8_t *buf, uint16_t len) {
  if (len <= 2) // Sanity check
    return;
  uint16_t crc = CRC16(buf, len - 2);
  buf[len - 2] = crc & 0xFF; // Low byte first
  buf[len - 1] = (crc >> 8) & 0xFF; // High byte second
}

static const uint16_t crcTable[] PROGMEM = {
  0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
  0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
  0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
  0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
  0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
  0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
  0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
  0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
  0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
  0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
  0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
  0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
  0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
  0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
  0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
  0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
  0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
  0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
  0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
  0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
  0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
  0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
  0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
  0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
  0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
  0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
  0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
  0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
  0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
  0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
  0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
  0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
};
uint16_t PZEM004T::CRC16(const uint8_t *data, uint16_t len) {
  uint8_t nTemp; // CRC table index
  uint16_t crc = 0xFFFF;
  while (len--) {
    nTemp = *data++ ^ crc;
    crc >>= 8;
    crc ^= (uint16_t)pgm_read_word(&crcTable[nTemp]);
  }
  return crc;
}
void PZEM004T::search() {
#if ( not defined(PZEM004T_DISABLE_SEARCH))
  static uint8_t response[7];
  for (uint16_t addr = 0x01; addr <= 0xF8; addr++) {
    sendCmd8(CMD_RIR, 0x00, 0x01, false, addr);
    if (receive(response, 7) != 7) { continue;} 
    else {
      Serial.print("Device on addr: ");
      Serial.println(addr);
    }
  }
#endif
}
