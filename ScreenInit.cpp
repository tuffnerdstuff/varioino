#include "ScreenInit.h"

ScreenInit::ScreenInit(ScreenManager *manager, VarioRendererOLED *display)
{
    this->manager = manager;
    this->display = display;
}

void ScreenInit::init()
{
    display->clearDisplay();
    display->renderLoading();
    display->drawDisplay();
}

void ScreenInit::tick( long lastTick )
{
    // NOP
}
