#include "ScreenInit.h"
#define DURATION 3000

ScreenInit::ScreenInit(ScreenManager *manager, DisplayOLED *display)
{
    this->manager = manager;
    this->display = display;
    this->startTime = 0;
}

void ScreenInit::init()
{
    display->clearDisplay();
    display->renderLoading();
    display->drawDisplay();
    startTime = millis();
}

void ScreenInit::tick( )
{
    if (millis() > startTime + DURATION)
	{
    	manager->setScreen(ScreenManager::MAIN);
	}
}
