#include "ScreenManager.h"
#include "ScreenInit.h"
#include "ScreenMain.h"

ScreenManager::ScreenManager(VarioRendererOLED *display, VarioRendererBuzzer *buzzer, Buttons *buttons)
{
	this->screen = NULL;
    this->display = display;
    this->buzzer = buzzer;
    this->buttons = buttons;
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
    if (newScreen == NULL)
    {
        return;
    }
    
    // Delete old screen
    delete this->screen;
    
    // Instantiate new screen
    switch(newScreen)
    {
        case INIT:
            this->screen = new ScreenInit(this, display);
            break;
        case MAIN:
            this->screen = new ScreenMain(this, display, buzzer, buttons);
            break;
    }
    
    // Init new screen
    this->screen->init();
}

void ScreenManager::tick( long lastTick )
{
    if (this->screen == NULL)
    {
        return;
    }
    
    // Tick the current screen
    this->screen->tick( lastTick );
}
