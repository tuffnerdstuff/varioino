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
	~ScreenMain();
	void init();
	void tick();
private:
	ScreenManager *manager;
	DisplayOLED *display;
	SpeakerPWM *buzzer;
	Buttons *buttons;
	Sensor *sensor;
	void renderValues(float vario, float altitude, float temp);
	void getFloatString(char *buff, int buffLen, float value, int n);
	int countDigits(int num);
	float roundNearest(float val, int decim);
};

#endif /* SCREENMAIN_H_ */
