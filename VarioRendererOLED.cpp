#include <stdint.h>
#include <math.h>

#include "VarioRendererOLED.h"
// Logo
#include "logo.h"


#define OLED_RESET 4
#define OLED_ADDRESS 0x3C

VarioRendererOLED::VarioRendererOLED()
{
}

VarioRendererOLED::~VarioRendererOLED()
{
  delete display;
}

void VarioRendererOLED::init()
{
    display = new Adafruit_SSD1306(OLED_RESET);
    display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    clearDisplay();
    
}

void VarioRendererOLED::drawDisplay()
{
	display->display();
}

void VarioRendererOLED::clearDisplay()
{
	display->clearDisplay();
}

void VarioRendererOLED::renderLoading()
{
    display->drawBitmap(0, 0, header_data, SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT, WHITE);
}


// PRIVATE

void VarioRendererOLED::printString(const char text[], int x, int y,
		unsigned int size, bool invert) {

	if ( invert )
	{
		display->setTextColor(BLACK, WHITE);
	}
	else
	{
		display->setTextColor(WHITE, BLACK);
	}

	display->setTextSize(size);
	display->setCursor(x, y);
	display->println(text);
}

int VarioRendererOLED::getScreenHeight() {
	return SSD1306_LCDHEIGHT;
}

int VarioRendererOLED::getScreenWidth() {
	return SSD1306_LCDWIDTH;
}

void VarioRendererOLED::drawRect(int x, int y, int w, int h) {
	display->drawRect(x, y, w, h, WHITE);
}

void VarioRendererOLED::drawLine(int x0, int y0, int x1, int y1) {
	display->drawLine(x0, y0, x1, y1, WHITE);
}

void VarioRendererOLED::fillRect(int x, int y, int w, int h) {
	display->fillRect(x, y, w, h, WHITE);
}
