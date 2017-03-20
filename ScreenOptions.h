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
#include "Buttons.h"
#include "DisplayOLED.h"
#include "Sensor.h"
#include "SpeakerPWM.h"

class ScreenOptions: public Screen {
public:
	ScreenOptions(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor);
	void init();
	void tick();
private:
	ScreenManager *manager;
	DisplayOLED *display;
	SpeakerPWM *buzzer;
	Buttons *buttons;
	Sensor *sensor;
	char* entries[3] = {"Reset Altitude", "Volume", "Exit"};
	int entriesLength = 3;
	int selectedIndex = 0;

};

#endif /* SCREENOPTIONS_H_ */
