#ifndef VARIORENDEREROLED_H
#define VARIORENDEREROLED_H

#include "U8g2lib.h"



class DisplayOLED
{
    public:
    enum Icon {UP, DOWN};

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
    void printIcon(Icon icon, int x, int y, unsigned int size);
    int getScreenHeight();
    int getScreenWidth();


    
    private:
    U8X8_SSD1306_128X64_NONAME_HW_I2C *display;
    
};

#endif
