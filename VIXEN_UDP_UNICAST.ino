/* UNICAST VIXE preko WIFI, ko ni unicasta, bere iz SD kartice 25ms
NODEMCU plosca:
SD:
- GND, 3.3V kar na plošo
- CS na D4
- MOSI na D7
- SCK na D5
- MISO na D6

LED WS2801: 
- DATA na D1
- SCK na D2
- GND
- posebej 5V inGND

LED WS2811:
- DATA na RX
- GND
- posebej 5V in GND

*/


#include <SPI.h>
#include <ESP8266WiFi.h>
#include <E131.h>
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include <WiFiUdp.h>

#include <SD.h>
#define CS_PIN  D4

#ifndef STASSID
//#define STASSID "JOZE_WIFI"
//#define STAPSK  "englazvinamidej"
#define STASSID "kranjc_wifi"
#define STAPSK  "StefanaInBertolin"
#endif

const int NUM_LEDS = 25;
CRGB leds[NUM_LEDS];

const int NUM_LEDS100 = 100;
CRGB leds100[NUM_LEDS100];

float cas, tempo;

unsigned int localPort = 5568;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged\r\n";       // a string to send back

WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  
    FastLED.addLeds<WS2801, 4, 5, RGB, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
    FastLED.addLeds<WS2812, 3, RGB>(leds100, NUM_LEDS100);

    // FastLED.setBrightness(100);

    for (int i=0;i<NUM_LEDS;i++) {
          leds[i].r = 0;
          leds[i].g = 0;
          leds[i].b = random(0,255);
          delay(50);
          FastLED.show();
    }
    
    delay(1000);
        for (int i=0;i<NUM_LEDS;i++) {
          leds[i].r = 0;
          leds[i].g = random(0,255);
          leds[i].b = 0;
          delay(50);
          FastLED.show();
    }
    
    for (int i=0;i<NUM_LEDS100;i++) {
          leds100[i].r = 0;
          leds100[i].g = 255;
          leds100[i].b = 0;
          delay(50);
          FastLED.show();
    }
    delay(1000);

    // preverjanje kartice
    if (!SD.begin(CS_PIN)) {
      Serial.println("Kartice ne prepoznam!!!");
      return;
    } else {
      Serial.println("SD kartica OK!");
    }

    
    Udp.begin(localPort);

    cas = millis();


    
}

void delajsam() {
  File dataFile = SD.open("output.bin");

  if (dataFile) {
    Serial.println("start");
    
    while (dataFile.available()) {
      tempo = millis();

      int packetSize = Udp.parsePacket();
        if (packetSize) {
            dataFile.close();
            cas = millis();
            return;
        }

      
      for (int i=0;i<NUM_LEDS;i++) {
        leds[i].r = dataFile.read();
        leds[i].g = dataFile.read();
        leds[i].b = dataFile.read();
      }
      for (int i=0;i<NUM_LEDS100;i++) {
        leds100[i].r = dataFile.read();
        leds100[i].g = dataFile.read();
        leds100[i].b = dataFile.read();
      }
      while (millis() < (tempo + 25)) {
         delay(1);
      }
      FastLED.show();
       
    }
    Serial.println("konec");
    dataFile.close();
  } else {
    Serial.println("Ne more odpreti output.bin");
    return;
  }
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    // FastLED.addLeds<WS2801, 4, 5, RGB, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
    for (int i=0;i<NUM_LEDS;i++) {
      leds[i].r = packetBuffer[126 + i*3];
      leds[i].g = packetBuffer[126 + i*3 + 1];
      leds[i].b = packetBuffer[126 + i*3 + 2];
    }
    // FastLED.show();
    // FastLED.addLeds<WS2811, 3, RGB>(leds100, NUM_LEDS100);
    for (int i=0;i<NUM_LEDS100;i++) {
      leds100[i].r = packetBuffer[126 + NUM_LEDS*3 + i*3];
      leds100[i].g = packetBuffer[126 + NUM_LEDS*3 + i*3 + 1];
      leds100[i].b = packetBuffer[126 + NUM_LEDS*3 + i*3 + 2];
    }
    FastLED.show();
    cas = millis();
  } else {
    if (millis() >= (cas + 5000)) {
        delajsam();
    }    
  }
}
