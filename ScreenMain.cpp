#include "ScreenMain.h"

#define BEEP_MIN_VARIO 0.3F

ScreenMain::ScreenMain(ScreenManager *manager, VarioRendererOLED *display, VarioRendererBuzzer *buzzer, Buttons *buttons, Sensor *sensor) {
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
	display->renderValues(sensor->getVario(), sensor->getRelativeAltitude(), sensor->getTemp());

	// debug button
	display->printString(buttons->isButtonPressed(Buttons::OK)?"P=YES":"P=NO", 0, 0, 1);
	display->printString(buttons->isButtonChanged(Buttons::OK)?"C=YES":"C=NO", 0, 5, 1);

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

