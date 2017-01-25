#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.h"
#include "VarioRendererOLED.h"
#include "VarioRendererBuzzer.h"
#include "Buttons.h"

class ScreenManager: public Screen
{
    private:
        Screen *screen;
        VarioRendererOLED *display;
        VarioRendererBuzzer *buzzer;
        Buttons *buttons;
        
    public:
        enum ScreenEnum {INIT, MAIN, OPT};
    
        ScreenManager(VarioRendererOLED &display, VarioRendererBuzzer &buzzer, Buttons &buttons);
        ~ScreenManager();
        void tick( long lastTick );
        void setScreen(ScreenEnum newScreen);
        
}


#endif


