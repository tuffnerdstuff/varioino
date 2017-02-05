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

	// Display
	display->clearDisplay();
	display->renderValues(sensor->getVario(), sensor->getRelativeAltitude(), sensor->getTemp());
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

