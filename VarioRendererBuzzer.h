#ifndef VARIORENDERERBUZZER_H
#define VARIORENDERERBUZZER_H

#include "VarioRenderer.h"

class VarioRendererBuzzer: public VarioRenderer
{
    public:
    void init();
    bool renderLoading(unsigned long pollDelay);
    void renderValues(float vario, float altitude, float temp, long renderDelay);  
};

#endif
