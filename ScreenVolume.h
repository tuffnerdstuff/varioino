/*
 * VolumeScreen.h
 *
 *  Created on: 20.03.2017
 *      Author: stefan
 */

#ifndef SCREENVOLUME_H_
#define SCREENVOLUME_H_

#include "Screen.h"
#include "ScreenManager.h"
#include "Buttons.h"
#include "DisplayOLED.h"
#include "SpeakerPWM.h"

class ScreenVolume: public Screen {
public:
	ScreenVolume(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons);
	void init();
	void tick();
private:
		ScreenManager *manager;
        DisplayOLED *display;
        SpeakerPWM *buzzer;
        Buttons *buttons;
};

#endif /* SCREENVOLUME_H_ */
