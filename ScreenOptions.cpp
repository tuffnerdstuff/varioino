/*
 * ScreenOptions.cpp
 *
 *  Created on: 05.02.2017
 *      Author: stefan
 */

#include "ScreenOptions.h"

#define BAR_HEIGHT 11
#define BAR_PADDING 2
#define MARGIN 5

ScreenOptions::ScreenOptions(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor) {
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
	bool isOKPressed = buttons->isButtonPressed(Buttons::OK) && buttons->isButtonChanged(Buttons::OK);
	bool isLeftPressed = buttons->isButtonPressed(Buttons::LEFT) && buttons->isButtonChanged(Buttons::LEFT);
	bool isRightPressed = buttons->isButtonPressed(Buttons::RIGHT) && buttons->isButtonChanged(Buttons::RIGHT);

	// Move cursor
	int curDir = 0;
	if (isLeftPressed)
	{
		curDir = -1;
	}
	else if(isRightPressed)
	{
		curDir = 1;
	}
	selectedIndex = (selectedIndex + curDir) % entriesLength;
    selectedIndex = (selectedIndex < 0) ? 0 : selectedIndex; // Negative correction

	// Option selected?
	switch(selectedIndex)
	{
		case 0:
			sensor->setAltitudeReference();
			break;
		case 1:
			break;
		case 2:
			if (isOKPressed)
			{
				manager->setScreen(ScreenManager::MAIN);
				return;
			}
			break;

	}

	// Draw
	display->clearDisplay();
	for (int i = 0; i < entriesLength; ++i) {
		int x = MARGIN;
		int y = MARGIN + i*BAR_HEIGHT;
		bool isHighlighted = i == selectedIndex;
		if (isHighlighted) {
			display->fillRect(0, y-BAR_PADDING, display->getScreenWidth(), BAR_HEIGHT);
		}
		display->printString(entries[i], x,y,1,isHighlighted);
	}
	display->drawDisplay();
}
