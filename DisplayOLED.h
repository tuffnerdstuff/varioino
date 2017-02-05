#ifndef VARIORENDEREROLED_H
#define VARIORENDEREROLED_H

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class DisplayOLED
{
    public:
	DisplayOLED();
    ~DisplayOLED();
    void init();
    void clearDisplay();
    void drawDisplay();
    void renderLoading();
    void printString(const char text[], int x, int y, unsigned int size, bool invert);
    void drawRect(int x, int y, int w, int h);
    void drawLine(int x0, int y0, int x1, int y1);
    void fillRect(int x, int y, int w, int h);
    int getScreenHeight();
    int getScreenWidth();

    
    private:
    Adafruit_SSD1306 *display;
    
};

#endif
