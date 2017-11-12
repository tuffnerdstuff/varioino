#include "ScreenMain.h"

#define BEEP_RISE_VARIO 0.5F
#define BEEP_MAX_GAP 500
#define BEEP_SINK_FREQ 250
#define BEEP_SINK_VARIO -1.5F

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

	// Test Buttons
		bool isOKPressed = buttons->isButtonPressed(Buttons::OK) && buttons->isButtonChanged(Buttons::OK);
		bool isLeftPressed = buttons->isButtonPressed(Buttons::LEFT) && buttons->isButtonChanged(Buttons::LEFT);
		bool isRightPressed = buttons->isButtonPressed(Buttons::RIGHT) && buttons->isButtonChanged(Buttons::RIGHT);

	// OPT Button pressed?
	if (isOKPressed)
	{
		manager->setScreen(ScreenManager::OPT);
		return;
	}
	else if (isLeftPressed)
	{
		this->onLeftButtonPressed();
		return;
	}
	else if (isRightPressed)
	{
		this->onRightButtonPressed();
		return;
	}

	// Display
	renderValues();

	// Buzzer
	if (sensor->getVario() >= BEEP_RISE_VARIO)
	{
		unsigned int freq = 690 + (150 * sensor->getVario());
		unsigned int length = (BEEP_MAX_GAP * BEEP_RISE_VARIO) / sensor->getVario();
		//unsigned int length = 0;
		unsigned int tones[2] = {freq,0};
		unsigned int toneLengths[2] = {length,length};
		buzzer->setMelody(2, tones, toneLengths);
	}
	else if(sensor->getVario() <= BEEP_SINK_VARIO)
	{
		unsigned int tones[5] = {BEEP_SINK_FREQ,BEEP_SINK_FREQ*0.75,BEEP_SINK_FREQ*0.5,BEEP_SINK_FREQ*0.25,0};
		unsigned int toneLengths[5] = {10,10,10,10,10};
		buzzer->setMelody(5, tones, toneLengths);
	}
}

/*
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
	  sprintf(lineString,"TMP: %s °C", valueString);
	  display->printString(lineString, 0, 2, 1, false);

	  // Free Mem
	  getFloatString(valueString, OLED_VALUELEN, freeMemory(), 1);
	  sprintf(lineString,"MEM: %s b", valueString);
	  display->printString(lineString, 0, 3, 1, false);
 */


