/*
 * Button.cpp
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 */

#include "Buttons.h"


Buttons::Buttons() {

}

Buttons::~Buttons() {
	// TODO Auto-generated destructor stub
}


bool Buttons::isButtonPressed(ButtonIndex button) {
	return getButton(button).isButtonPressed();
}

bool Buttons::isButtonChanged(ButtonIndex button) {
	return getButton(button).isButtonChanged();
}

void Buttons::tick() {
	getButton(OK).tick();
	getButton(LEFT).tick();
	getButton(RIGHT).tick();
}

Button& Buttons::getButton(ButtonIndex button) {
	switch (button)
	{
	case OK:
		return btnOK;
	case LEFT:
		return btnLeft;
	default:
		return btnRight;
	}
}




