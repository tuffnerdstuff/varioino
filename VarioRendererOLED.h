#ifndef VARIORENDEREROLED_H
#define VARIORENDEREROLED_H

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "VarioRenderer.h"



class VarioRendererOLED: public VarioRenderer
{
    public:
    ~VarioRendererOLED();
    void init();
    bool renderLoading(unsigned long pollDelay);
    void renderValues(float vario, float altitude, float temp, long renderDelay);

    
    private:
    Adafruit_SSD1306 *display;
    unsigned long loadingStartTime = 0;
    bool loadingImagePainted = false;
    
    void setTextColor(float value);
    void getFloatString(char *buff, int buffLen, float value, int n);
    int countDigits(int num);
    float roundNearest(float val, int decim);
    
};

#endif
