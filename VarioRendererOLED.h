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
    void renderValues(float vario, float altitude, float temp);
    
    private:
    Adafruit_SSD1306 *display;
    void setTextColor(float value);
    void getFloatString(char *buff, int buffLen, float value, int n);
    int countDigits(int num);
    float roundNearest(float val, int decim);
};

#endif
