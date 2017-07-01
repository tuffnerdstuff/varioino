/*
 * Button.h
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdio.h>
#include "Button.h"

#define BUTTON_LEFT 11
#define BUTTON_RIGHT 12
#define BUTTON_OK 7

class Buttons {
public:
	enum ButtonIndex{OK,LEFT,RIGHT};
	Buttons();
	virtual ~Buttons();
	void tick();
	bool isButtonChanged(ButtonIndex button);
	bool isButtonPressed(ButtonIndex button);
private:
	Button btnLeft = Button(BUTTON_LEFT);
	Button btnRight = Button(BUTTON_RIGHT);
	Button btnOK = Button(BUTTON_OK);
	Button& getButton(ButtonIndex button);

};

#endif /* BUTTONS_H_ */
