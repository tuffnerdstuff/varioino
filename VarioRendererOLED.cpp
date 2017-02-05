#include <stdint.h>
#include <math.h>

#include "VarioRendererOLED.h"
// Logo
#include "logo.h"


#define OLED_RESET 4
#define OLED_ADDRESS 0x3C
#define OLED_INVERT false
#define OLED_VALUELEN 9
#define OLED_BARWIDTH 25
#define OLED_PADDING 5
#define OLED_MAXVARIO 2
#define OLED_MINLOADINGTIME 2000

VarioRendererOLED::VarioRendererOLED()
{
}

VarioRendererOLED::~VarioRendererOLED()
{
  delete display;
}

void VarioRendererOLED::init()
{
    display = new Adafruit_SSD1306(OLED_RESET);
    display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    clearDisplay();
    
}

void VarioRendererOLED::drawDisplay()
{
	display->display();
}

void VarioRendererOLED::clearDisplay()
{
	display->clearDisplay();
}

void VarioRendererOLED::renderLoading()
{
    display->drawBitmap(0, 0, header_data, SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT, WHITE);
}

void VarioRendererOLED::renderValues(float vario, float altitude, float temp)
{
  //vario = -7;

  // ~~~~ BAR ~~~~
  bool rising = vario >= 0;
  float barSegment = ((SSD1306_LCDHEIGHT/2)/(float)OLED_MAXVARIO);
  int barHeight = abs(vario * barSegment);
  barHeight = barHeight > SSD1306_LCDHEIGHT/2 ? SSD1306_LCDHEIGHT/2 : barHeight;
  int barStartY = rising ? SSD1306_LCDHEIGHT/2 - barHeight  : SSD1306_LCDHEIGHT/2;
  
  display->drawRect(0,0,OLED_BARWIDTH-OLED_PADDING,SSD1306_LCDHEIGHT,WHITE);
  display->drawLine(0,SSD1306_LCDHEIGHT/2,OLED_BARWIDTH-OLED_PADDING-1,SSD1306_LCDHEIGHT/2,WHITE);
  display->fillRect(0,barStartY,OLED_BARWIDTH-OLED_PADDING,barHeight,WHITE);

  // ~~~~ VALUES ~~~~
  display->setTextSize(1);

  char lineString[25];
  char valueString[OLED_VALUELEN];
  // VARIO
  float roundVario = roundNearest(vario,1);
  display->setCursor(OLED_BARWIDTH,0);
  setTextColor(roundVario);
  getFloatString(valueString, OLED_VALUELEN, roundVario, 1);
  sprintf(lineString,"VAR: %s m/s", valueString);
  display->println(lineString);

  // ALTITUDE
  display->setCursor(OLED_BARWIDTH,27);
  setTextColor(altitude);
  getFloatString(valueString, OLED_VALUELEN, altitude, 1);
  sprintf(lineString,"ALT: %s m", valueString);
  display->println(lineString);

  // TEMPERATURE
  display->setCursor(OLED_BARWIDTH,54);
  setTextColor(temp);
  getFloatString(valueString, OLED_VALUELEN, temp, 1);
  sprintf(lineString,"TMP: %s %cC", valueString, (char)247);
  display->println(lineString);
  
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

void VarioRendererOLED::printString(const char text[], int x, int y,
		unsigned int size) {
	display->setTextSize(size);
	display->setCursor(x, y);
	display->println(text);
}
