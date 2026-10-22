# Arduino sketches

A collection of Arduino / ESP32 sketches from coursework, the thesis, and
bench experiments. Each folder is a self-contained sketch (`.ino` + helper
headers).

| Sketch | Board / stack | What it does |
|---|---|---|
| `Smart_Power_Outlet` | ESP32 + PZEM-004T | Thesis prototype: measures voltage, current and power of a socket, then reports it. |
| `Final_Arduino_Code` | ESP32 + WiFiClient | Posts sensor readings to a PHP endpoint on a local XAMPP server. |
| `DHT11_data_to_phpmyadmindatabase` | ESP8266 + DHT11 | Reads temperature/humidity and writes it to MySQL through PHP. |
| `trial_project` | Arduino + Ethernet2 + TFT | Bench test of the Ethernet shield, display and RTC together. |
| `trial_comm` | Arduino + ModbusMaster | Modbus RTU communication experiment over SoftwareSerial. |
| `trial_led` | Arduino | Blink/serial bring-up. |
| `sketch_dec11a` | ATtiny/AVR TCB | Bare-register timer compare interrupt experiment. |

Library zips and IDE caches were removed; install the libraries listed in each
sketch's `#include` lines through the Arduino Library Manager.

Not included: sketches written for employer products (test jigs and module
testers), which are not mine to publish.

MIT licensed — see [LICENSE](LICENSE).
