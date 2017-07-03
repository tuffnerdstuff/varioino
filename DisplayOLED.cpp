#include "DisplayOLED.h"

#include <stdint.h>
#include <math.h>

#include "logo.h"


#define OLED_RESET 4
#define OLED_ADDRESS 0x3C

#define ICON_UP {B00010000,B00110000,B01110000,B11111111,B11111111,B01110000,B00110000,B00010000}

DisplayOLED::DisplayOLED()
{
	U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8G2_R0, OLED_RESET);
	display = &u8x8;
	u8g2_SetI2CAddress(display, OLED_ADDRESS);
}

DisplayOLED::~DisplayOLED()
{
  delete display;
}

void DisplayOLED::init()
{
	display->begin();
    
}

void DisplayOLED::drawDisplay()
{
	//display->display();
}

void DisplayOLED::clearDisplay()
{
	display->clearDisplay();
}

void DisplayOLED::renderLoading()
{
}


// PRIVATE

void DisplayOLED::printString(const char text[], int x, int y,
		unsigned int size, bool invert) {

	if ( invert )
	{
		display->setInverseFont(1);
	}
	else
	{
		display->setInverseFont(0);
	}

	display->setFont(u8x8_font_pxplusibmcga_f);
	if (size > 1)
	{
		display->draw2x2UTF8(x, y, text);
	}
	else
	{
		display->drawUTF8(x, y, text);
	}

}

int DisplayOLED::getScreenHeight() {
	return 64;
}

int DisplayOLED::getScreenWidth() {
	return 128;
}

void DisplayOLED::drawRect(int x, int y, int w, int h) {
}

void DisplayOLED::drawLine(int x0, int y0, int x1, int y1) {
}

void DisplayOLED::fillRect(int x, int y, int w, int h) {
}

void DisplayOLED::printIcon(Icon icon, int x, int y, unsigned int size) {
	uint8_t tile[8] = ICON_UP;
	display->drawTile(x, y, 1, tile);
}
