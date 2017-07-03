/*
 * ScreenMainAlt.cpp
 *
 *  Created on: 02.07.2017
 *      Author: stefan
 */

#include "ScreenMainAlt.h"
#include "utilities.h"

#define OLED_VALUELEN 8

ScreenMainAlt::ScreenMainAlt(ScreenManager* manager, DisplayOLED* display,
		SpeakerPWM* buzzer, Buttons* buttons, Sensor* sensor) : ScreenMain(manager, display, buzzer, buttons, sensor) {
}

void ScreenMainAlt::renderValues() {
	char lineString[25];
	char valueString[OLED_VALUELEN];

	// ALTITUDE
	display->printString("ALTITUDE", 0, 0, 1, false);
	getFloatString(valueString, OLED_VALUELEN, sensor->getAltitude(),1);
	sprintf(lineString,"%s", valueString);
	display->printString(lineString, 0, 2, 2, false);
	display->printString("m", 15, 3, 1, false);
}

void ScreenMainAlt::onLeftButtonPressed() {
	manager->setScreen(ScreenManager::VARIO);
}

void ScreenMainAlt::onRightButtonPressed() {
	manager->setScreen(ScreenManager::TEMP);
}
