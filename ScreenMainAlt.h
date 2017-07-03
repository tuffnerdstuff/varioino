/*
 * ScreenMainAlt.h
 *
 *  Created on: 02.07.2017
 *      Author: stefan
 */

#ifndef SCREENMAINALT_H_
#define SCREENMAINALT_H_

#include "ScreenMain.h"

class ScreenMainAlt: public ScreenMain {
public:
	ScreenMainAlt(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor);
protected:
	void renderValues();
	void onLeftButtonPressed();
	void onRightButtonPressed();
};

#endif /* SCREENMAINALT_H_ */
