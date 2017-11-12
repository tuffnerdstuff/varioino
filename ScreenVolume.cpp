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
	display->clearDisplay();
}

void ScreenVolume::tick()
{
	// Test Buttons
	bool isOKPressed = buttons->isButtonPressed(Buttons::OK) && buttons->isButtonChanged(Buttons::OK);
	bool isLeftPressed = buttons->isButtonPressed(Buttons::LEFT) && buttons->isButtonChanged(Buttons::LEFT);
	bool isRightPressed = buttons->isButtonPressed(Buttons::RIGHT) && buttons->isButtonChanged(Buttons::RIGHT);

	if (isOKPressed)
	{
		manager->setScreen(ScreenManager::VARIO);
		return;
	}
	else if (isLeftPressed && buzzer->getVolume() < SpeakerPWM::MAX_VOL)
	{
		buzzer->setVolume(buzzer->getVolume() + 1);
	}
	else if ( isRightPressed && buzzer->getVolume() > SpeakerPWM::MIN_VOL)
	{
		buzzer->setVolume(buzzer->getVolume() - 1);
	}

	// Title
	display->printString("Volume", 0, 0, 1, false);

	// Value
	char volString[3];
	getIntString(volString, 3, this->buzzer->getVolume());
	display->printString(volString, 5, 3, 2, false);
}

