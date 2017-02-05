/*
 * Button.cpp
 *
 *  Created on: 05.02.2017
 *      Author: stefan
 */

#include "Button.h"
#include "Arduino.h"

#define BUTTON_DEBOUNCE 25 // in ms

Button::Button(int pin) {
	this->pin = pin;

	// Set initial values
	lastChange = -1;
	lastReading = false;
	isPressed = false;
	isChanged = false;

	// Init Button Pin
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

bool Button::isButtonPressed() {
	return isPressed;
}

bool Button::isButtonChanged() {
	return isChanged;
}

void Button::tick() {
	isChanged = false;
	bool reading = !digitalRead(pin);
	if (reading != lastReading) {
		lastChange = millis();
	}
	if ((millis() - lastChange) > BUTTON_DEBOUNCE) {

		isChanged = reading != isPressed;
		isPressed = reading;
	}

	lastReading = reading;
}

