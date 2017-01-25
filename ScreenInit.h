#ifndef SCREENINIT_H
#define SCREENINIT_H

#include "Screen.h"
#include "ScreenManager.h"
#include "VarioRendererOLED.h"

class ScreenInit: public Screen
{
    public:
        ScreenInit(ScreenManager &manager, VarioRendererOLED &display);
        void tick( long lastTick );
}

#endif
