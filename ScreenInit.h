#ifndef SCREENINIT_H
#define SCREENINIT_H

#include "DisplayOLED.h"
#include "Screen.h"
#include "ScreenManager.h"

class ScreenInit: public Screen
{
    public:
        ScreenInit(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer);
        void init();
        void tick();
    private:
        ScreenManager *manager;
        DisplayOLED *display;
        SpeakerPWM *buzzer;
};

#endif
