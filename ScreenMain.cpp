#include "ScreenMain.h"
#include "utilities.h"
#include "MemoryFree.h"

#define BEEP_MIN_VARIO 0.3F
#define OLED_VALUELEN 8
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
	display->clearDisplay();
}

void ScreenMain::tick() {

	// OPT Button pressed?
	if (buttons->isButtonPressed(Buttons::OK) && buttons->isButtonChanged(Buttons::OK))
	{
		manager->setScreen(ScreenManager::OPT);
		return;
	}

	// Display
	renderValues(sensor->getVario(), sensor->getRelativeAltitude(), sensor->getTemp());

	// Buzzer
	if (sensor->getVario() > BEEP_MIN_VARIO)
	{
		unsigned int freq = 690 + (150 * sensor->getVario());
		unsigned int length = 100 - (50 * (sensor->getVario() - BEEP_MIN_VARIO) );
		buzzer->setTone(freq, length);
	}
}

void ScreenMain::renderValues(float vario, float altitude, float temp)
{

  // ~~~~ BAR ~~~~
  bool rising = vario >= 0;
  float barSegment = ((display->getScreenHeight()/2)/(float)OLED_MAXVARIO);
  int barHeight = abs(vario * barSegment);
  barHeight = barHeight > display->getScreenHeight()/2 ? display->getScreenHeight()/2 : barHeight;
  int barStartY = rising ? display->getScreenHeight()/2 - barHeight  : display->getScreenHeight()/2;

  display->drawRect(0,0,OLED_BARWIDTH-OLED_PADDING,display->getScreenHeight());
  display->drawLine(0,display->getScreenHeight()/2,OLED_BARWIDTH-OLED_PADDING-1,display->getScreenHeight()/2);
  display->fillRect(0,barStartY,OLED_BARWIDTH-OLED_PADDING,barHeight);

  // ~~~~ VALUES ~~~~

  char lineString[25];
  char valueString[OLED_VALUELEN];
  // VARIO
  float roundVario = roundNearest(vario,1);
  getFloatString(valueString, OLED_VALUELEN, roundVario, 1);
  sprintf(lineString,"VAR: %s m/s", valueString);
  display->printString(lineString, 0, 0, 1, false);

  // ALTITUDE
  getFloatString(valueString, OLED_VALUELEN, altitude, 1);
  sprintf(lineString,"ALT: %s m", valueString);
  display->printString(lineString, 0, 1, 1, false);

  // TEMPERATURE
  getFloatString(valueString, OLED_VALUELEN, temp, 1);
  sprintf(lineString,"TMP: %s °", valueString);
  display->printString(lineString, 0, 2, 1, false);

  // Free Mem
  getFloatString(valueString, OLED_VALUELEN, freeMemory(), 1);
  sprintf(lineString,"MEM: %s b", valueString);
  display->printString(lineString, 0, 3, 1, false);

}


