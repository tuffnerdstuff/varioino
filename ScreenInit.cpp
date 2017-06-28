#include "ScreenInit.h"
#define DURATION 3000

ScreenInit::ScreenInit(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer)
{
    this->manager = manager;
    this->display = display;
    this->buzzer = buzzer;
    this->startTime = 0;
}

void ScreenInit::init()
{
    // Display Image
	display->clearDisplay();
    display->renderLoading();
    display->drawDisplay();

    // Play Init Tune
    unsigned int tones[13] = {660,660,0,660,0,510,660,0,770,0,0,0,380};
    unsigned int toneLengths[13] = {100,100,100,100,100,100,100,100,100,100,100,100,100};
    buzzer->setMelody(13, tones, toneLengths);

    startTime = millis();
}

void ScreenInit::tick( )
{
    if (millis() > startTime + DURATION)
	{
    	manager->setScreen(ScreenManager::MAIN);
	}
}
