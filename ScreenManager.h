#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "VarioRendererOLED.h"
#include "VarioRendererBuzzer.h"
#include "Buttons.h"
#include "Screen.h"

class ScreenManager: public Screen
{
    private:
        Screen *screen;
        VarioRendererOLED *display;
        VarioRendererBuzzer *buzzer;
        Buttons *buttons;
        
    public:
        enum ScreenEnum {INIT, MAIN, OPT};
    
        ScreenManager(VarioRendererOLED *display, VarioRendererBuzzer *buzzer, Buttons *buttons);
        ~ScreenManager();
        void init();
        void tick( long lastTick );
        void setScreen(ScreenEnum newScreen);
        
};


#endif


