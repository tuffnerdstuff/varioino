/*
 * Button.h
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

class Buttons {
public:
	enum Button{OK,LEFT,RIGHT};
	Buttons();
	virtual ~Buttons();
	void init();
	void loop();
	bool isButtonPressed(Button button);
private:
	long lastLeftChange;
	long lastRightChange;
	long lastOKChange;
	bool isLeftPressed;
	bool isRightPressed;
	bool isOKPressed;
	bool isPinTriggered(int buttonPin);
	void updateButton(int pin, bool& buttonState, long& lastChangeTime);
	void initButtonPin(int buttonPin);
};

#endif /* BUTTONS_H_ */
