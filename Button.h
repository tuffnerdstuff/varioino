/*
 * Button.h
 *
 *  Created on: 05.02.2017
 *      Author: stefan
 */

#ifndef BUTTON_H_
#define BUTTON_H_

class Button {
public:
	Button(int pin);
	virtual ~Button();
	bool isButtonPressed();
	bool isButtonChanged();
	void tick();

private:
	int pin;
	long lastChange;
	bool lastReading;
	bool isPressed;
	bool isChanged;

};

#endif /* BUTTON_H_ */
