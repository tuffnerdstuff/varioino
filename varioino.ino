// MAIN
#include <stdint.h>
#include "MovingAverage.h"
#define SERIAL_BAUD 57600
#define SAMPLES 25
#define SAMPLE_DELAY 10
// I2C
#include "Wire.h"
// OLED
#include "VarioRendererOLED.h"
VarioRendererOLED display;
// SENSOR
#include "SparkFunBME280.h"
BME280 sensor;


// Buzzer
#include "toneAC.h"
#define BEEP_DELAY 250L
#define TONE_VOL 0
#define TONE_MULT 300


MovingAverage buffAlt(SAMPLES);
MovingAverage buffTemp(SAMPLES);
float lastAvgAlt = 0;
unsigned long lastTime = 0;


void setup() {

  // Begin serial console
  Serial.begin(SERIAL_BAUD);

  // Init
  delay(10);
  initSensor();
  initBeep();
  display.init();

  // set first sensor reading to avoid peak
  lastAvgAlt = sensor.readFloatAltitudeMeters();
  lastTime = micros();
}

void loop() {

  // Push new sensor reading into ring buffer
  buffAlt.push(sensor.readFloatAltitudeMeters());
  buffTemp.push(sensor.readTempC());

  // time difference
  unsigned long currTime = micros();
  unsigned long timeSinceLastBeep = currTime - lastTime;

  if (timeSinceLastBeep >= BEEP_DELAY * 1000)
  {
  
    // Get average altitude
    float currAvgAlt = buffAlt.getAverage();
    float avgAltPerSecond = ((currAvgAlt - lastAvgAlt) / timeSinceLastBeep) * 1000000;
  
    Serial.println(avgAltPerSecond,10);

    // Render
    renderBeep(avgAltPerSecond);
    display.renderValues(avgAltPerSecond, currAvgAlt, buffTemp.getAverage());

    // Set values for next loop
    lastAvgAlt = currAvgAlt;
    lastTime = currTime;

  }


  delay(SAMPLE_DELAY);

}

void initSensor()
{
  // Configure sensor
  Serial.println("init sensor ...");
  sensor.settings.commInterface = I2C_MODE;
  sensor.settings.I2CAddress = 0x76;
  sensor.settings.runMode = 3; // Normal (auto poll)
  sensor.settings.tStandby = 0; // 0.5ms
  sensor.settings.filter = 4; 
  sensor.settings.tempOverSample = 5;
  sensor.settings.pressOverSample = 5;
  sensor.settings.humidOverSample = 0;

  // Initialize sensor
  
  sensor.begin();
}

void initBeep()
{
  
}

void renderBeep(float vario)
{
  if (vario > 0.3)
  {
    toneAC(690 + (150 * vario), TONE_VOL, BEEP_DELAY * 0.6, true);
  }
}





