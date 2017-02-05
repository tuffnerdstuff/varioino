#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "VarioRendererOLED.h"
#include "VarioRendererBuzzer.h"
#include "Buttons.h"
#include "Screen.h"
#include "Sensor.h"

class ScreenManager: public Screen
{
    private:
        Screen *screen;
        VarioRendererOLED *display;
        VarioRendererBuzzer *buzzer;
        Buttons *buttons;
        Sensor *sensor;
        unsigned long lastScreenChangeTime = 0;
        
    public:
        enum ScreenEnum {INIT, MAIN, OPT};
    
        ScreenManager(VarioRendererOLED *display, VarioRendererBuzzer *buzzer, Buttons *buttons, Sensor *sensor);
        ~ScreenManager();
        void init();
        void tick();
        void setScreen(ScreenEnum newScreen);
        
};


#endif


