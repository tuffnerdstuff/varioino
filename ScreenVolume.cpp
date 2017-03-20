/*
 * VolumeScreen.cpp
 *
 *  Created on: 20.03.2017
 *      Author: stefan
 */

#include "ScreenVolume.h"

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
	display->printString("Volume", 0, 0, 1, false);
	display->drawDisplay();
}

