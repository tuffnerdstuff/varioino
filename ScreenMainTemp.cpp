/*
 * ScreenMainTemp.cpp
 *
 *  Created on: 02.07.2017
 *      Author: stefan
 */

#include "ScreenMainTemp.h"
#include "utilities.h"

#define OLED_VALUELEN 6

ScreenMainTemp::ScreenMainTemp(ScreenManager* manager, DisplayOLED* display,
		SpeakerPWM* buzzer, Buttons* buttons, Sensor* sensor) : ScreenMain(manager, display, buzzer, buttons, sensor) {
}

void ScreenMainTemp::renderValues() {
	// ~~~~ VALUES ~~~~
	char lineString[25];
	char valueString[OLED_VALUELEN];
	// VARIO
	display->printString("TEMPERATURE", 0, 0, 1, false);
	float roundVario = roundNearest(sensor->getTemp(),1);
	getFloatString(valueString, OLED_VALUELEN, roundVario, 1);
	sprintf(lineString,"%s", valueString);
	display->printString(lineString, 0, 2, 2, false);
	display->printString("°C", 11, 3, 1, false);
}

void ScreenMainTemp::onLeftButtonPressed() {
	manager->setScreen(ScreenManager::ALT);
}

void ScreenMainTemp::onRightButtonPressed() {
	manager->setScreen(ScreenManager::VARIO);
}
