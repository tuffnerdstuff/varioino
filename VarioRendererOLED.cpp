#include <stdint.h>
#include <math.h>

#include "VarioRendererOLED.h"


#define OLED_RESET 4
#define OLED_ADDRESS 0x3C
#define OLED_INVERT false

VarioRendererOLED::~VarioRendererOLED()
{
  delete display;
}

void VarioRendererOLED::init()
{
    display = new Adafruit_SSD1306(OLED_RESET);
    display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display->clearDisplay();
    display->display();
}

void VarioRendererOLED::renderValues(float vario, float altitude, float temp)
{
  display->clearDisplay();
  display->setTextSize(1);
  display->setCursor(0,0);

  char lineString[25];
  char valueString[10];
  // VARIO
  float roundVario = roundNearest(vario,1);
  setTextColor(roundVario);
  getFloatString(valueString, 10, roundVario, 1);
  sprintf(lineString,"VAR: %s m/s", valueString);
  display->println(lineString);

  // ALTITUDE
  setTextColor(altitude);
  getFloatString(valueString, 10, altitude, 1);
  sprintf(lineString,"ALT: %s m", valueString);
  display->println(lineString);

  // TEMPERATURE
  setTextColor(temp);
  getFloatString(valueString, 10, temp, 1);
  sprintf(lineString,"TMP: %s %cC", valueString, (char)247);
  display->println(lineString);
  
  display->display();
}

// PRIVATE

void VarioRendererOLED::setTextColor(float value)
{
  if (OLED_INVERT && value < 0 )
  {
    display->setTextColor(BLACK, WHITE);
  }
  else
  {
    display->setTextColor(WHITE, BLACK);
  }
}

void VarioRendererOLED::getFloatString(char *buff, int buffLen, float value, int n)
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

int VarioRendererOLED::countDigits(int num)
{
    int n = 0;
    while(num) {
        num /= 10;
        n++;
    }
    return n;
}

float VarioRendererOLED::roundNearest(float val, int decim)
{
  float decimFact = pow(10,decim);
  return roundf(val * decimFact) / decimFact;
}


