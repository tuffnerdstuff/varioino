#ifndef SCREENINIT_H
#define SCREENINIT_H

#include "DisplayOLED.h"
#include "Screen.h"
#include "ScreenManager.h"

class ScreenInit: public Screen
{
    public:
        ScreenInit(ScreenManager *manager, DisplayOLED *display);
        void init();
        void tick();
    private:
        ScreenManager *manager;
        DisplayOLED *display;
        unsigned long startTime;
};

#endif
