/*
 * ScreenMainVario.cpp
 *
 *  Created on: 02.07.2017
 *      Author: stefan
 */

#include "ScreenMainVario.h"
#include "utilities.h"


#define OLED_VALUELEN 6

ScreenMainVario::ScreenMainVario(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor) : ScreenMain(manager, display, buzzer, buttons, sensor) {
	// call super constructor
}

ScreenMainVario::~ScreenMainVario() {
	// TODO Auto-generated destructor stub
}

void ScreenMainVario::renderValues() {

	float vario = sensor->getVario();

	// ~~~~ VALUES ~~~~
	char lineString[25];
	char valueString[OLED_VALUELEN];
	// VARIO
	display->printString("VARIO", 0, 0, 1, false);
	float roundVario = roundNearest(vario,1);
	getFloatString(valueString, OLED_VALUELEN, roundVario, 1);
	sprintf(lineString,"%s", valueString);
	display->printString(lineString, 0, 2, 2, false);
	display->printString("m/s", 11, 3, 1, false);
}

void ScreenMainVario::onLeftButtonPressed() {
	manager->setScreen(ScreenManager::TEMP);
}

void ScreenMainVario::onRightButtonPressed() {
	manager->setScreen(ScreenManager::ALT);
}
