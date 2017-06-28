#include "ScreenManager.h"
#include "ScreenInit.h"
#include "ScreenMain.h"
#include "ScreenOptions.h"
#include "ScreenVolume.h"

ScreenManager::ScreenManager(DisplayOLED *display, SpeakerPWM *buzzer, Buttons *buttons, Sensor *sensor)
{
	this->screen = NULL;
    this->display = display;
    this->buzzer = buzzer;
    this->buttons = buttons;
    this->sensor = sensor;
}

ScreenManager::~ScreenManager()
{
    delete this->screen;
}

void ScreenManager::init()
{
    // Start with init screen
    setScreen(INIT);
}

void ScreenManager::setScreen(ScreenEnum newScreen)
{
    
    // Delete old screen
    delete this->screen;
    
    // Instantiate new screen
    switch(newScreen)
    {
        case INIT:
            this->screen = new ScreenInit(this, display, buzzer);
            break;
        case MAIN:
            this->screen = new ScreenMain(this, display, buzzer, buttons, sensor);
            break;
        case OPT:
        	this->screen = new ScreenOptions(this, display, buzzer, buttons, sensor);
			break;
        case VOL:
        	this->screen = new ScreenVolume(this, display, buzzer, buttons);
    }
    

    // Init new screen
    this->screen->init();


}

void ScreenManager::tick()
{
    if (this->screen == NULL)
    {
        return;
    }
    
    // Tick the current screen
    this->screen->tick();
}
