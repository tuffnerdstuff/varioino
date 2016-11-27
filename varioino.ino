// MAIN
#include <stdint.h>
#include "FloatFilterMovingAverage.h"
#include "FloatFilterWeighed.h"
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
#define SAMPLES 50
#define SAMPLE_DELAY 10L
#define RENDER_DELAY 250L
#define BUTTON_OK 13
#define BUTTON_DEBOUNCE 20 // in ms


// Sensor
BME280 sensor;
// Smoothing buffers
FloatFilterMovingAverage buffAlt(SAMPLES);
//FloatFilterMovingAverage buffTemp(1);
//FloatFilterWeighed buffAlt;
FloatFilterWeighed buffTemp;

// Buttons
long lastOKPress = -1;

// Values
float groundAlt = 0;
float lastAvgAlt = 0;
unsigned long lastTime = 0;

// init
bool initDone = false;


void setup() {

  // Begin serial console
  // Serial.begin(SERIAL_BAUD);

  // Init
  delay(10);
  initButtons();
  initSensor();
  buzzer.init();
  display.init();

  // set first sensor reading to avoid peak
  lastAvgAlt = sensor.readFloatAltitudeMeters();
  lastTime = micros();
}

void loop() {

  // Push new sensor reading into ring buffer
  buffAlt.pushValue(sensor.readFloatAltitudeMeters());
  buffTemp.pushValue(sensor.readTempC());

  // time difference
  unsigned long currTime = micros();
  unsigned long timeSinceLastBeep = currTime - lastTime;

  if (!initDone)
  {
    // Make sure that all modules have been initialized
    bool logoDone = !display.renderLoading(SAMPLE_DELAY);
    bool tonDone = !buzzer.renderLoading(SAMPLE_DELAY);
    
    initDone = logoDone && tonDone && buffAlt.isReady() && buffTemp.isReady();
  }
  else // button handling
  {
    if (buttonPressed(BUTTON_OK))
    {
      if (millis() - lastOKPress >= BUTTON_DEBOUNCE)
      {
        // Pressed
        groundAlt = buffAlt.getFilteredValue();
      }
    }
    else
    {
      lastOKPress = millis();
    }
   
  }
  
  if (timeSinceLastBeep >= RENDER_DELAY * 1000)
  {
  
    // Get average altitude
    float currAvgAlt = buffAlt.getFilteredValue();
    float avgAltPerSecond = ((currAvgAlt - lastAvgAlt) / timeSinceLastBeep) * 1000000;
  
    // Serial.println(avgAltPerSecond,10);

    // Render
    if (initDone)
    {
      buzzer.renderValues(avgAltPerSecond, -1, -1, RENDER_DELAY);
      display.renderValues(avgAltPerSecond, currAvgAlt - groundAlt, buffTemp.getFilteredValue(), RENDER_DELAY);
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
  //filter can be off or number of FIR coefficients to use:
  //  0, filter off
  //  1, coefficients = 2
  //  2, coefficients = 4
  //  3, coefficients = 8
  //  4, coefficients = 16
  sensor.settings.filter = 16;
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively 
  sensor.settings.tempOverSample = 1;
  sensor.settings.pressOverSample = 5;
  sensor.settings.humidOverSample = 0;

  // Initialize sensor
  
  sensor.begin();
}

void initButtons()
{
  pinMode(BUTTON_OK,INPUT);
  digitalWrite(BUTTON_OK,HIGH);
}

bool buttonPressed(int buttonPin)
{
  return !digitalRead(buttonPin);
}


