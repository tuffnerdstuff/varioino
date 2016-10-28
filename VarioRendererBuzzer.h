#ifndef VARIORENDERERBUZZER_H
#define VARIORENDERERBUZZER_H

#include "VarioRenderer.h"

class VarioRendererBuzzer: public VarioRenderer
{
    public:
    void init();
    bool renderLoading(unsigned long pollDelay);
    void renderValues(float vario, float altitude, float temp, long renderDelay);

    private:
    int initTones[13] = {660,660,0,660,0,510,660,0,770,0,0,0,380};
    int initTonesLength = 13;
    bool initToneStarted = false;
    unsigned long lastToneStart = 0;
    int initToneIndex = 0;
};

#endif
