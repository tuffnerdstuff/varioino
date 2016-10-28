// MAIN
#include <stdint.h>
#include "MovingAverage.h"
// I2C
#include "Wire.h"
// OLED
#include "VarioRendererOLED.h"
VarioRendererOLED display;
// BUZZER
#include "VarioRendererBuzzer.h"
VarioRendererBuzzer buzzer;
// SENSOR
#include "SparkFunBME280.h"


#define SERIAL_BAUD 57600
#define SAMPLES 25
#define SAMPLE_DELAY 10L
#define RENDER_DELAY 250L

// Sensor
BME280 sensor;
// Smoothing buffers
MovingAverage buffAlt(SAMPLES);
MovingAverage buffTemp(SAMPLES);
float lastAvgAlt = 0;
unsigned long lastTime = 0;
bool initDone = false;


void setup() {

  // Begin serial console
  // Serial.begin(SERIAL_BAUD);

  // Init
  delay(10);
  initSensor();
  buzzer.init();
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

  if (!initDone)
  {
    // Make sure that all modules have been initialized
    initDone = !display.renderLoading(SAMPLE_DELAY) && !buzzer.renderLoading(SAMPLE_DELAY) && buffAlt.isFull() && buffTemp.isFull();
  }
  
  if (timeSinceLastBeep >= RENDER_DELAY * 1000)
  {
  
    // Get average altitude
    float currAvgAlt = buffAlt.getAverage();
    float avgAltPerSecond = ((currAvgAlt - lastAvgAlt) / timeSinceLastBeep) * 1000000;
  
    // Serial.println(avgAltPerSecond,10);

    // Render
    if (initDone)
    {
      buzzer.renderValues(avgAltPerSecond, currAvgAlt, buffTemp.getAverage(), RENDER_DELAY);
      display.renderValues(avgAltPerSecond, currAvgAlt, buffTemp.getAverage(), RENDER_DELAY);
    }

    // Set values for next loop
    lastAvgAlt = currAvgAlt;
    lastTime = currTime;

  }


  delay(SAMPLE_DELAY);

}

void initSensor()
{
  // Configure sensor
  // Serial.println("init sensor ...");
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





