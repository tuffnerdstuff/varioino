/*
 * ScreenOptions.cpp
 *
 *  Created on: 05.02.2017
 *      Author: stefan
 */

#include "ScreenOptions.h"

ScreenOptions::ScreenOptions(ScreenManager *manager, VarioRendererOLED *display, VarioRendererBuzzer *buzzer, Buttons *buttons, Sensor *sensor) {
	this->manager = manager;
	this->display = display;
	this->buzzer = buzzer;
	this->buttons = buttons;
	this->sensor = sensor;

}

ScreenOptions::~ScreenOptions() {
	// TODO Auto-generated destructor stub
}

void ScreenOptions::init() {
}

void ScreenOptions::tick() {

	// Test Buttons
	if (buttons->isButtonPressed(Buttons::OK) && buttons->isButtonChanged(Buttons::OK))
	{
		manager->setScreen(ScreenManager::MAIN);
	}

	// Draw
	display->clearDisplay();
	display->printString("Test", 0,0,2);
	display->drawDisplay();
}
