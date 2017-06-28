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
	char volString[3];
	getIntString(volString, 3, this->buzzer->getVolume());
	display->printString("Volume", 0, 0, 1, false);
	//display->printString(volString, 0, 1, 1, false);
}

