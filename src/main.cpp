#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 16
#define NUM_LEDS 18
#define DATA_PIN 16
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds,NUM_LEDS);
}

void loop() {
  LEDS.showColor(CRGB(255,0,0));
  delay(500);
  LEDS.showColor(CRGB(0,255,0));
  delay(500);
  LEDS.showColor(CRGB(0,0,255));
  delay(500);
}

