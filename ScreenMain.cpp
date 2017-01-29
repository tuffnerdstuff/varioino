#include "ScreenMain.h"

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
	display->clearDisplay();
	display->renderValues(1, 2, 5.12678);
	//display->renderValues(sensor->getVario(), sensor->getRelativeAltitude(), sensor->getTemp());
	display->drawDisplay();
}

ScreenMain::~ScreenMain() {
	// TODO Auto-generated destructor stub
}

