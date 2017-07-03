#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Buttons.h"
#include "DisplayOLED.h"
#include "Screen.h"
#include "Sensor.h"
#include "SpeakerPWM.h"

class ScreenManager
{
    private:
        Screen *screen;
        DisplayOLED *display;
        SpeakerPWM *buzzer;
        Buttons *buttons;
        Sensor *sensor;
        unsigned long lastScreenChangeTime = 0;
        
    public:
        enum ScreenEnum {INIT, VARIO, OPT, VOL, TEMP, ALT};
    
        ScreenManager(DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor);
        ~ScreenManager();
        void init();
        void tick();
        void setScreen(ScreenEnum newScreen);
        
};


#endif


