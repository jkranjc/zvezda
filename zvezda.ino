// Uncomment this line if you have any interrupts that are changing pins - this causes the library to be a little bit more cautious
// #define FAST_SPI_INTERRUPTS_WRITE_PINS 1

// Uncomment this line to force always using software, instead of hardware, SPI (why?)
// #define FORCE_SOFTWARE_SPI 1

// Uncomment this line if you want to talk to DMX controllers
// #define FASTSPI_USE_DMX_SIMPLE 1

#include "FastLED.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// test code
//
//////////////////////////////////////////////////

#define NUM_LEDS 150

CRGB leds[NUM_LEDS];

int xr, xg, xb, xrand, xrand1, x,y,z,j;
int rele_min = 4;
int rele_max = 8;

void setup() {


  
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);

   	// For safety (to prevent too high of a power draw), the test case defaults to
   	// setting brightness to 25% brightness
   	LEDS.setBrightness(254);

   	// LEDS.addLeds<WS2811, 13>(leds, NUM_LEDS);
   	// LEDS.addLeds<TM1809, 13>(leds, NUM_LEDS);
   	// LEDS.addLeds<UCS1903, 13>(leds, NUM_LEDS);
   	// LEDS.addLeds<TM1803, 13>(leds, NUM_LEDS);

   	// LEDS.addLeds<P9813>(leds, NUM_LEDS);
   	//CLEDController *pLed = new ClocklessController_Trinket<4, NS(400), NS(400), NS(450), GRB>();
   	//LEDS.addLeds(pLed, leds, NUM_LEDS);
   	// LEDS.addLeds<LPD8806>(leds, NUM_LEDS);
    //LEDS.addLeds<WS2801>(leds, NUM_LEDS);
   	// LEDS.addLeds<SM16716>(leds, NUM_LEDS);

   	// LEDS.addLeds<WS2811, 11>(leds, NUM_LEDS);

	// Put ws2801 strip on the hardware SPI pins with a BGR ordering of rgb and limited to a 1Mhz data rate
LEDS.addLeds<WS2801, 3, 2, BGR, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);

   	// LEDS.addLeds<LPD8806, 10, 11>(leds, NUM_LEDS);
//LEDS.addLeds<WS2811, 2, BRG>(leds, NUM_LEDS);
   	// LEDS.addLeds<LPD8806, BGR>(leds, NUM_LEDS);

      randomSeed(analogRead(0));
      for (int i = rele_min; i <= rele_max; i++) {
          pinMode(i, OUTPUT);
          digitalWrite(i, HIGH);
      }

Serial.begin(9600);
Serial.println("Joza, pozen!");

}

void loop() { 
  
  xr = 50 * random(5);
  xg = 50 * random(5);
  xb = 50 * random(5);
  xrand = int(random(12)) + 1;
  xrand1 = int(random(5)) + 1;
  memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
 
//xrand = 12;
//xrand1 = 5;

//  Serial.print("XRAND: ");
  Serial.println(xrand);

  switch(xrand) {
    
  case 1:
        // vse skupaj naenkrat
        LEDS.showColor(CRGB(xr, xg, xb), 250);
        delay(1000);
        break;  
  case 2:
        // letijo v krogu po ena v levo
        x = 10;
        for(int i = 0; i < 9; i++) {
	  for(int iLed = 0; iLed < NUM_LEDS; iLed++) {
    	    memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
	    leds[iLed] = CRGB(xr, xg, xb); 
	    LEDS.show();
	    delay(x);
	  }
          x = x - 1;
        }
        memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
        break;
   case 3:
        // letijo v krogu po ena v desno
        x = 10;
        for(int i = 0; i < 9; i++) {
	  for(int iLed = NUM_LEDS - 1; iLed > -1; iLed--) {
    	    memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
	    leds[iLed] = CRGB(xr, xg, xb); 
	    LEDS.show();
	    delay(x);
	  }
          x = x -1;
        }
        memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
        break;
  case 4:
	// fade up, down
	for(int scale = 0; scale < 250; scale++) { 
	  LEDS.showColor(CRGB(xr, xg, xb), scale);
	  delay(5);
	}
	for(int scale = 250; scale > 0; scale--) { 
	  LEDS.showColor(CRGB(xr,xg,xb), scale);
	delay(5);
	}
        break;
  case 5:
        // zapolnijo krog v levo
        for(int iLed = 0; iLed < NUM_LEDS; iLed++) {
 	    leds[iLed] = CRGB(xr, xg, xb); 
	    LEDS.show();
	    delay(100);
        }
        break;
   case 6:
        // zapolnijo krog v desno
        for(int iLed = NUM_LEDS - 1; iLed > -1; iLed--) {
 	    leds[iLed] = CRGB(xr, xg, xb); 
	    LEDS.show();
	    delay(100);
        }
        break;
   case 7:
        // zapolnijo krog naključno
        for(int iLed = 0; iLed < NUM_LEDS; iLed++) {
 	    leds[iLed] = CRGB(50 * random(5), 50 * random(5), 50 * random(5)); 
        }
  	LEDS.show();
        delay(1000);
        break;
   case 8:
        // od špice proti notranjosti
        for(int iLed = 3; iLed < NUM_LEDS; iLed = iLed + 5) {
 	    leds[iLed] = CRGB(xr, xg, xb); 
        }
        LEDS.show();
        delay(300);
        xr = 50 * random(5);
        xg = 50 * random(5);
        xb = 50 * random(5);
        for(int iLed = 3; iLed < NUM_LEDS; iLed = iLed + 5) {
 	    leds[iLed + 1] = CRGB(xr, xg, xb); 
 	    leds[iLed - 1] = CRGB(xr, xg, xb); 
        }
        LEDS.show();
        delay(300);
        xr = 50 * random(5);
        xg = 50 * random(5);
        xb = 50 * random(5);

        for(int iLed = 3; iLed < NUM_LEDS; iLed = iLed + 5) {
            if (iLed == (NUM_LEDS - 2)) {
 	      leds[0] = CRGB(xr, xg, xb); 
             } else {
  	      leds[iLed + 2] = CRGB(xr, xg, xb); 
            }
 	    leds[iLed - 2] = CRGB(xr, xg, xb); 
        }
        LEDS.show();
        delay(1000);
        break;
   case 9:
        // kaca
        for(int iLed = 0; iLed < NUM_LEDS; iLed++) {
            x = xr;
            y = xg;
            z = xb;
            leds[iLed] = CRGB(x, y, z); 
            if (iLed > 0) {
              x = x - 50;
              if (x < 0) { x = 0; }
              y = y - 50;
              if (y < 0) { y = 0; }
              z = z - 50;
              if (z < 0) { z = 0; }
       	      leds[iLed - 1] = CRGB(x, y, z); 
            }
            if (iLed > 1) {
              x = x - 50;
               y = y - 50;
              if (y < 0) { y = 0; }
              z = z - 50;
              if (z < 0) { z = 0; }
              if (x < 0) { x = 0; }
     	      leds[iLed - 2] = CRGB(x, y, z); 
            }
           if (iLed > 2) {
              x = x - 50;
              if (x < 0) { x = 0; }
              y = y - 50;
              if (y < 0) { y = 0; }
              z = z - 50;
              if (z < 0) { z = 0; }
     	      leds[iLed - 3] = CRGB(x, y, z); 
            }
            if (iLed > 3) {
              x = x - 50;
              if (x < 0) { x = 0; }
              y = y - 50;
              if (y < 0) { y = 0; }
              z = z - 50;
              if (z < 0) { z = 0; }
     	      leds[iLed - 4] = CRGB(x, 0, 0); 
            }
	    LEDS.show();
	    delay(1);
        }
        break;
        
 case 10:
        // zapolnijo krog naključno in nato ugašajo in prižigajo
        for(int iLed = 0; iLed < NUM_LEDS; iLed++) {
 	    leds[iLed] = CRGB(50 * random(5), 50 * random(5), 50 * random(5)); 
        }
  	LEDS.show();
        delay(1000);
        for (int i = 0; i < 30; i++) {
          x = random(25);
          y = random(25);
          z = random(25);
          leds[x] = CRGB(0,0,0);
          leds[y] = CRGB(0,0,0);
          leds[z] = CRGB(0,0,0);
          LEDS.show();
          delay(100);
          leds[x] = CRGB(50 * random(5), 50 * random(5), 50 * random(5)); 
          leds[y] = CRGB(50 * random(5), 50 * random(5), 50 * random(5)); 
          leds[z] = CRGB(50 * random(5), 50 * random(5), 50 * random(5)); 
          LEDS.show();
          delay(100);
        }
        break;
  case 11:
	// petkrat zažarijo
        for(int i = 0; i < 5; i++) {
    	  for(int scale = 0; scale < 250; scale++) { 
	    LEDS.showColor(CRGB(xr, xg, xb), scale);
	    delay(1);
	  }
	  for(int scale = 250; scale > 0; scale--) { 
	    LEDS.showColor(CRGB(xr,xg,xb), scale);
	    delay(1);
	  }
        }
        break;

  case 12:
      // se prižigajo od ene proti vsem 
      j = int(NUM_LEDS / 2);
      leds[j] = CRGB(xr, xg, xb); 
      LEDS.show();
      delay(100);
      for(int iLed = 1; iLed < j; iLed++) {
            leds[j - iLed] = CRGB(xr, xg, xb); 
            leds[j + iLed] = CRGB(xr, xg, xb); 
            LEDS.show();
            delay(30);
      }
      break;
  
  default:
        // vse skupaj naenkrat
        LEDS.showColor(CRGB(xr, xg, xb), 200);
        delay(1000);
        break; 
  }
 
  for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, HIGH);
  }
 
  for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, HIGH);
  }
  delay (100);
 
  switch(xrand1) {
    
  case 1:
      //prižgeajo se na za drugo
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
          delay(200);
      }
      break;
  
  case 2:
      //nekajkrat utripnejo vse hkrati
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
      }
      delay (200);
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, HIGH);
      }
      delay (200);
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
      }
      delay (200);
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, HIGH);
      }
      delay (200);
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
      }
      break;    
  case 3:
      //prižgeajo se na za drugo, nato nazaj
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
          delay(100);
      }
      for (int i = rele_max; i >= rele_min; i--) {
          digitalWrite(i, HIGH);
          delay(100);
      }

      break;
  case 4:
      //prižgeajo se ena za drugo in sproti ugašajo
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
          delay(100);
          digitalWrite(i, HIGH);
          delay(100);
      }
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
          delay(100);
          digitalWrite(i, HIGH);
          delay(100);
      }
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
          delay(100);
          digitalWrite(i, HIGH);
          delay(100);
      }
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
          delay(100);
          digitalWrite(i, HIGH);
          delay(100);
      }
      break;
  case 5:
      //od sredine navzven in nazaj
      x = rele_min + (rele_max - rele_min) / 2;
      digitalWrite(x, LOW);
      delay(100);
      digitalWrite(x - 1, LOW);
      digitalWrite(x + 1, LOW);
      delay(100);
      digitalWrite(x - 2, LOW);
      digitalWrite(x + +2, LOW);
      delay(100);
      digitalWrite(x - 2, HIGH);
      digitalWrite(x + 2, HIGH);
      delay(100);
      digitalWrite(x - 1, HIGH);
      digitalWrite(x + 1, HIGH);
      delay(100);
      digitalWrite(x, HIGH);
      delay(100);
      digitalWrite(x, LOW);
      delay(100);
      digitalWrite(x - 1, LOW);
      digitalWrite(x + 1, LOW);
      delay(100);
      digitalWrite(x - 2, LOW);
      digitalWrite(x + +2, LOW);
      delay(100);
      digitalWrite(x - 2, HIGH);
      digitalWrite(x + 2, HIGH);
      delay(100);
      digitalWrite(x - 1, HIGH);
      digitalWrite(x + 1, HIGH);
      delay(100);
      digitalWrite(x, HIGH);
      delay(100);
      break;
  default:
      for (int i = rele_min; i <= rele_max; i++) {
          digitalWrite(i, LOW);
      }
      break;
  }
}
