#include "ScreenMain.h"

ScreenMain::ScreenMain(ScreenManager &manager, VarioRendererOLED &display, VarioRendererBuzzer &buzzer, Buttons &buttons)
{
    this->manager = manager;
    this->display = display;
    this->buzzer = buzzer;
    this->buttons = buttons;
}

void ScreenMain::init()
{
    
}

void ScreenMain::tick( lastTick )
{
    // NOP
}