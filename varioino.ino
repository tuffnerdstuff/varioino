// Arduino
#include "Arduino.h"
// MAIN
#include <stdint.h>
#include "FloatFilterMovingAverage.h"
#include "FloatFilterWeighed.h"
// I2C
#include "Wire.h"
// OLED
#include "VarioRendererOLED.h"
// BUZZER
#include "VarioRendererBuzzer.h"
// SENSOR
#include "SparkFunBME280.h"
// SCREEN MANAGER


#include "ScreenManager.h"

#define DELAY_INIT 10
#define DELAY_LOOP 10L
VarioRendererOLED *display;
VarioRendererBuzzer *buzzer;
Buttons *buttons;
ScreenManager *scrMan;

void setup() {

  // Init
  delay(DELAY_INIT);

  display = new VarioRendererOLED();
  buzzer = new VarioRendererBuzzer();
  scrMan = new ScreenManager(display,buzzer,buttons);

}

void loop() {

  delay(DELAY_LOOP);

}








