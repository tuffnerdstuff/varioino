/*
 * Button.cpp
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 */

#include "Buttons.h"
#include "Arduino.h"

#define BUTTON_LEFT 11
#define BUTTON_RIGHT 12
#define BUTTON_OK 13
#define BUTTON_DEBOUNCE 50 // in ms

Buttons::Buttons() {
	lastOKChange = -1;
	lastLeftChange = -1;
	lastRightChange = -1;
	isLeftPressed = false;
	isRightPressed = false;
	isOKPressed = false;

}

Buttons::~Buttons() {
	// TODO Auto-generated destructor stub
}

void Buttons::init() {
	initButtonPin(BUTTON_OK);
	initButtonPin(BUTTON_LEFT);
	initButtonPin(BUTTON_RIGHT);
}

bool Buttons::isButtonPressed(Button button) {
	switch (button)
	{
	case OK:
		return isOKPressed;
	case LEFT:
		return isLeftPressed;
	case RIGHT:
		return isRightPressed;
	default:
		return false;
	}
}

void Buttons::tick() {
	updateButton(BUTTON_OK, isOKPressed, lastOKChange);
	updateButton(BUTTON_OK, isLeftPressed, lastLeftChange);
	updateButton(BUTTON_OK, isRightPressed, lastRightChange);
}

void Buttons::initButtonPin(int buttonPin) {
	pinMode(buttonPin, INPUT);
	digitalWrite(buttonPin, HIGH);
}

void Buttons::updateButton(int pin, bool& buttonState, long& lastChangeTime) {
	bool reading = isPinTriggered(pin);
	if (reading != buttonState) {
		lastChangeTime = millis();
	}
	if ((millis() - lastChangeTime) > BUTTON_DEBOUNCE) {
		buttonState = reading;
	}
}

bool Buttons::isPinTriggered(int buttonPin)
{
  return !digitalRead(buttonPin);
}
