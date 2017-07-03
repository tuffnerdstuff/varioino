/*
 * ScreenMain.h
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 */

#ifndef SCREENMAIN_H_
#define SCREENMAIN_H_

#include "Screen.h"
#include "ScreenManager.h"
#include "Buttons.h"
#include "DisplayOLED.h"
#include "Sensor.h"
#include "SpeakerPWM.h"

class ScreenMain: public Screen {
public:
	ScreenMain(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor);
	virtual ~ScreenMain(){};
	void init();
	void tick();
protected:
	virtual void renderValues()=0;
	virtual void onLeftButtonPressed()=0;
	virtual void onRightButtonPressed()=0;
	ScreenManager *manager;
	DisplayOLED *display;
	SpeakerPWM *buzzer;
	Buttons *buttons;
	Sensor *sensor;
};

#endif /* SCREENMAIN_H_ */
