#include "ScreenInit.h"
#include "logo.h"

ScreenInit::ScreenInit(ScreenManager &manager, VarioRendererOLED &display)
{
    this->manager = manager;
    this->display = display;
}

void ScreenInit::init()
{
    this->display->drawBitmap(header_data);
    this->display->display();
}

void ScreenInit::tick( lastTick )
{
    // NOP
}
