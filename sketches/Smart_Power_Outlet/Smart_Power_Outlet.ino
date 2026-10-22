#include "MAP.h"
SoftwareSerial pzemSWSerial(8, 7);
PZEM004T pzem(pzemSWSerial);

void setup() {
  initial();
}

void loop() {
  serialCall(1);
}
