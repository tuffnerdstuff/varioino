/*
 * VolumeScreen.cpp
 *
 *  Created on: 20.03.2017
 *      Author: stefan
 */

#include "ScreenVolume.h"
#include "utilities.h"

ScreenVolume::ScreenVolume(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons)
{
	this->manager=manager;
	this->display=display;
	this->buzzer=buzzer;
	this->buttons=buttons;
}

void ScreenVolume::init()
{
}

void ScreenVolume::tick()
{
	display->clearDisplay();
	char volString[3];
	getIntString(volString, 3, this->buzzer->getVolume());
	display->printString("Volume", 50, 0, 1, false);
	display->printString(volString, display->getScreenWidth()/2-10, display->getScreenHeight()/2-2, 2, false);
	display->drawDisplay();
}

