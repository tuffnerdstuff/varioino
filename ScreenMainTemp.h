/*
 * ScreenMainTemp.h
 *
 *  Created on: 02.07.2017
 *      Author: stefan
 */

#ifndef SCREENMAINTEMP_H_
#define SCREENMAINTEMP_H_

#include "ScreenMain.h"

class ScreenMainTemp: public ScreenMain {
public:
	ScreenMainTemp(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor);
protected:
	void renderValues();
	void onLeftButtonPressed();
	void onRightButtonPressed();
};

#endif /* SCREENMAINTEMP_H_ */
