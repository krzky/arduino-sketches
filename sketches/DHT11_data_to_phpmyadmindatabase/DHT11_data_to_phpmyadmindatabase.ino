
#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0x00, 0x50, 0x56, 0x91, 0x49, 0x42};

#define DHTPIN A0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


float hum;
float temp;


char server[] = "192.168.100.50";
IPAddress ip(192, 168, 100, 10);
IPAddress dnServer(192, 168, 100, 225);
IPAddress gateway(192, 168, 100, 200);
IPAddress subnet(255, 255, 255, 0);
EthernetClient client;

/* Setup for Ethernet and RFID */

void setup() {
  //Serial.begin(9600);
  //while(!//Serial);
  dht.begin();
  if (Ethernet.begin(mac) == 0) {
    //Serial.println("Failed to configure Ethernet using");
    Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  }
  //Serial.println("ETH OK");
  delay(1000);
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //Serial.print("Humidity : ");
  //Serial.print(hum);
  //Serial.println("%");
  //Serial.print("Temp.    : ");
  //Serial.print(temp);
  //Serial.println("°C");
  //delay(2000);
  Sending_To_phpmyadmindatabase();
  delay(30000);
  //delay(3000);
}


void Sending_To_phpmyadmindatabase() {
  if (client.connect(server, 80)) {
    //Serial.println("connected");
    //Serial.print("GET /sensor/sensor.php?Humidity=");
    client.print("GET /sensor/sensor.php?Humidity=");
    //Serial.print(hum);
    client.print(hum);
    client.print("&Temperature=");
    //Serial.print("&Temperature=");
    client.print(temp);
    //Serial.print(temp);
    client.print(" ");
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.100.50");
    client.println("Connection: close");
    client.println();
    //Serial.println();
    //Serial.println();
  }

  else {
    // if you didn't get a connection to the server:
    //Serial.println("connection failed");
  }
}
