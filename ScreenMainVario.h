/*
 * ScreenMainVario.h
 *
 *  Created on: 02.07.2017
 *      Author: stefan
 */

#ifndef SCREENMAINVARIO_H_
#define SCREENMAINVARIO_H_

#include "ScreenMain.h"

class ScreenMainVario: public ScreenMain {
public:
	ScreenMainVario(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor);
	virtual ~ScreenMainVario();
protected:
	void renderValues();
	void onLeftButtonPressed();
	void onRightButtonPressed();
};

#endif /* SCREENMAINVARIO_H_ */
