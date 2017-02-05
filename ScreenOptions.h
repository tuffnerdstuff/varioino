/*
 * ScreenOptions.h
 *
 *  Created on: 05.02.2017
 *      Author: stefan
 */

#ifndef SCREENOPTIONS_H_
#define SCREENOPTIONS_H_

#include "Screen.h"
#include "ScreenManager.h"
#include "VarioRendererOLED.h"
#include "VarioRendererBuzzer.h"
#include "Buttons.h"
#include "Sensor.h"

class ScreenOptions: public Screen {
public:
	ScreenOptions(ScreenManager *manager, VarioRendererOLED *display, VarioRendererBuzzer *buzzer, Buttons *buttons, Sensor *sensor);
	virtual ~ScreenOptions();
	void init();
	void tick();
private:
	ScreenManager *manager;
	VarioRendererOLED *display;
	VarioRendererBuzzer *buzzer;
	Buttons *buttons;
	Sensor *sensor;

};

#endif /* SCREENOPTIONS_H_ */
