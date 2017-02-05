#include "ScreenMain.h"

#define BEEP_MIN_VARIO 0.3F
#define OLED_VALUELEN 9
#define OLED_BARWIDTH 25
#define OLED_PADDING 5
#define OLED_MAXVARIO 2

ScreenMain::ScreenMain(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor) {
	this->manager = manager;
	this->display = display;
	this->buzzer = buzzer;
	this->buttons = buttons;
	this->sensor = sensor;

}

void ScreenMain::init() {

}

void ScreenMain::tick() {

	// OPT Button pressed?
	if (buttons->isButtonPressed(Buttons::OK) && buttons->isButtonChanged(Buttons::OK))
	{
		manager->setScreen(ScreenManager::OPT);
	}

	// Display
	display->clearDisplay();
	renderValues(sensor->getVario(), sensor->getRelativeAltitude(), sensor->getTemp());
	display->drawDisplay();

	// Buzzer
	if (sensor->getVario() > BEEP_MIN_VARIO)
	{
		unsigned int freq = 690 + (150 * sensor->getVario());
		unsigned int length = 100 - (50 * (sensor->getVario() - BEEP_MIN_VARIO) );
		buzzer->setTone(freq, length);
	}
}

ScreenMain::~ScreenMain() {
	// TODO Auto-generated destructor stub
}

void ScreenMain::renderValues(float vario, float altitude, float temp)
{

  // ~~~~ BAR ~~~~
  bool rising = vario >= 0;
  float barSegment = ((display->getScreenHeight()/2)/(float)OLED_MAXVARIO);
  int barHeight = abs(vario * barSegment);
  barHeight = barHeight > display->getScreenHeight()/2 ? display->getScreenHeight()/2 : barHeight;
  int barStartY = rising ? display->getScreenHeight()/2 - barHeight  : display->getScreenHeight()/2;

  display->drawRect(0,0,OLED_BARWIDTH-OLED_PADDING,SSD1306_LCDHEIGHT);
  display->drawLine(0,display->getScreenHeight()/2,OLED_BARWIDTH-OLED_PADDING-1,display->getScreenHeight()/2);
  display->fillRect(0,barStartY,OLED_BARWIDTH-OLED_PADDING,barHeight);

  // ~~~~ VALUES ~~~~

  char lineString[25];
  char valueString[OLED_VALUELEN];
  // VARIO
  float roundVario = roundNearest(vario,1);
  getFloatString(valueString, OLED_VALUELEN, roundVario, 1);
  sprintf(lineString,"VAR: %s m/s", valueString);
  display->printString(lineString, OLED_BARWIDTH, 0, 1, false);

  // ALTITUDE
  getFloatString(valueString, OLED_VALUELEN, altitude, 1);
  sprintf(lineString,"ALT: %s m", valueString);
  display->printString(lineString, OLED_BARWIDTH, 28, 1, false);

  // TEMPERATURE
  getFloatString(valueString, OLED_VALUELEN, temp, 1);
  sprintf(lineString,"TMP: %s %cC", valueString, (char)247);
  display->printString(lineString, OLED_BARWIDTH, 57, 1, false);

}

void ScreenMain::getFloatString(char *buff, int buffLen, float value, int n)
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

int ScreenMain::countDigits(int num)
{
    int n = 0;
    while(num) {
        num /= 10;
        n++;
    }
    return n;
}

float ScreenMain::roundNearest(float val, int decim)
{
  float decimFact = pow(10,decim);
  return roundf(val * decimFact) / decimFact;
}

