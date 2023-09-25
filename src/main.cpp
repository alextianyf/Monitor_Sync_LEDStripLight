#include <Arduino.h>
#include <FastLED.h>
#include <stdint.h>

#define serialRate 115200
#define LED_PIN 16
#define NUM_LEDS 18
#define DATA_PIN 16
CRGB leds[NUM_LEDS];

uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;



void setup() {
  //使用 NEO 像素保持真实色彩
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  //初始化
  LEDS.showColor(CRGB(255, 0, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 255, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 255));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 0));
  
  Serial.begin(serialRate);
  //发送口令
  Serial.print("Ada\n");
}

void loop() {
  //等待串口返回口令
  for(i = 0; i < sizeof prefix; ++i) {
    waitLoop: while (!Serial.available()) ;;
    //读取串口数据，直至收到Ada口令词退出
    if(prefix[i] == Serial.read()) continue;
    i = 0;
    goto waitLoop;
  }
  
  // 读取并校验 Hi, Lo, Checksum  
  while (!Serial.available()) ;;
  hi=Serial.read();
  while (!Serial.available()) ;;
  lo=Serial.read();
  while (!Serial.available()) ;;
  chk=Serial.read();
  
  //如果校验和不匹配，返回等待
  if (chk != (hi ^ lo ^ 0x55)) {
    i=0;
    goto waitLoop;
  }
  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  //读取传输数据并设置 LED 值
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    byte r, g, b;    
    while(!Serial.available());
    r = Serial.read();
    while(!Serial.available());
    g = Serial.read();
    while(!Serial.available());
    b = Serial.read();
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
  }
  //刷新点亮
  FastLED.show();
}

