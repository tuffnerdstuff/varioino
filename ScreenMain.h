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
#include "VarioRendererOLED.h"
#include "VarioRendererBuzzer.h"
#include "Buttons.h"

class ScreenMain: public Screen {
public:
	ScreenMain(ScreenManager *manager, VarioRendererOLED *display, VarioRendererBuzzer *buzzer, Buttons *buttons);
	virtual ~ScreenMain();
	void init();
	void tick(long lastTick);
private:
	ScreenManager *manager;
	VarioRendererOLED *display;
	VarioRendererBuzzer *buzzer;
	Buttons *buttons;
};

#endif /* SCREENMAIN_H_ */
