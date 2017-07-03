/*
 * ScreenOptions.cpp
 *
 *  Created on: 05.02.2017
 *      Author: stefan
 */

#include "ScreenOptions.h"

#define INDEX_RESET 0
#define INDEX_VOLUME 1
#define INDEX_EXIT 2

#define BAR_HEIGHT 1
#define BAR_PADDING 0
#define MARGIN 0

ScreenOptions::ScreenOptions(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor) {
	this->manager = manager;
	this->display = display;
	this->buzzer = buzzer;
	this->buttons = buttons;
	this->sensor = sensor;

}

void ScreenOptions::init() {
	display->clearDisplay();
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
    selectedIndex = (selectedIndex < 0) ? entriesLength - 1 : selectedIndex; // Negative correction

	// Option selected?
    if (isOKPressed)
    {
    	switch(selectedIndex)
    	{
    	case INDEX_RESET:
    		sensor->setAltitudeReference();
    		manager->setScreen(ScreenManager::VARIO);
    		break;
    	case INDEX_VOLUME:
    		manager->setScreen(ScreenManager::VOL);
    		break;
    	case INDEX_EXIT:
    		manager->setScreen(ScreenManager::VARIO);
    		break;

    	}
		return; // Prevent redraw as we are changing screens
    }

	// Draw
	for (int i = 0; i < entriesLength; ++i) {
		int x = MARGIN;
		int y = MARGIN + i*BAR_HEIGHT;
		bool isHighlighted = i == selectedIndex;
		if (isHighlighted) {
			display->fillRect(0, y-BAR_PADDING, display->getScreenWidth(), BAR_HEIGHT);
		}
		display->printString(entries[i], x,y,1,isHighlighted);
	}
}
