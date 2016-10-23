// MAIN
#include <stdint.h>
#include "MovingAverage.h"
#define SERIAL_BAUD 57600
#define SAMPLES 25
#define SAMPLE_DELAY 10
// I2C
#include "Wire.h"
// SENSOR
#include "SparkFunBME280.h"
BME280 sensor;
// OLED
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <math.h>
#define OLED_RESET 4
#define OLED_INVERT false
Adafruit_SSD1306 display(OLED_RESET);
// Buzzer
#include "toneAC.h"
#define BEEP_DELAY 250L
#define TONE_VOL 10
#define TONE_MULT 300


MovingAverage buffAlt(SAMPLES);
MovingAverage buffTemp(SAMPLES);
float lastAvgAlt = 0;
unsigned long lastTime = 0;


void setup() {

  // Begin serial console
  Serial.begin(SERIAL_BAUD);

  // Init
  initSensor();
  initBeep();
  initOLED();

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
    renderOLED(avgAltPerSecond, currAvgAlt, buffTemp.getAverage());

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
  delay(10);
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

void initOLED()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.display();
}

void renderOLED(float vario, float altitude, float temp)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);

  char lineString[25];
  char valueString[10];
  // VARIO
  float roundVario = roundNearest(vario,1);
  setTextColor(roundVario);
  getFloatString(valueString, 10, roundVario, 1);
  sprintf(lineString,"VAR: %s m/s", valueString);
  display.println(lineString);

  // ALTITUDE
  setTextColor(altitude);
  getFloatString(valueString, 10, altitude, 1);
  sprintf(lineString,"ALT: %s m", valueString);
  display.println(lineString);

  // TEMPERATURE
  setTextColor(temp);
  getFloatString(valueString, 10, temp, 1);
  sprintf(lineString,"TMP: %s %cC", valueString, (char)247);
  display.println(lineString);
  
  display.display();
}

void setTextColor(float value)
{
  if (OLED_INVERT && value < 0 )
  {
    display.setTextColor(BLACK, WHITE);
  }
  else
  {
    display.setTextColor(WHITE, BLACK);
  }
}

void getFloatString(char *buff, int buffLen, float value, int n)
{
  
  int intValue = abs((int)(value * pow(10,n)));
  char sign = value >= 0 ? '+' : '-';
  int digitCount = countDigits(intValue);
  if (digitCount+3 > buffLen)
  {
    int idx;
    for (idx = 0; idx < buffLen-2; idx++)
    {
      buff[idx] = '-';
    }
    buff[idx] = '\0';
    
  }
  else
  {

    int i;
    int count = 0;
    buff[buffLen-1] = '\0';
  
    for (i = buffLen - 2; i > 0; i--)
    {
      if (count == n)
      {
        buff[i] = '.';
      }
      else if (intValue <= 0)
      {
        if (count <= n+1)
        {
          buff[i] = '0';
        }
        else
        {
          buff[i] = ' ';
        }
        
      }
      else
      {
        buff[i] = '0' + (intValue % 10);
        intValue /= 10;
      }

      count++;
    }

    // Sign
    buff[0]=sign;

    
  }


}

int countDigits(int num)
{
    int n = 0;
    while(num) {
        num /= 10;
        n++;
    }
    return n;
}

float roundNearest(float val, int decim)
{
  float decimFact = pow(10,decim);
  return roundf(val * decimFact) / decimFact;
}

