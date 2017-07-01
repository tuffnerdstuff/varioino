#include "ScreenInit.h"

#define NLN 64 // Note-length 1/16 note--> 1024ms = 1 bar

ScreenInit::ScreenInit(ScreenManager *manager, DisplayOLED *display, SpeakerPWM *buzzer)
{
    this->manager = manager;
    this->display = display;
    this->buzzer = buzzer;
}

void ScreenInit::init()
{
    // Display Image
	display->clearDisplay();
    display->renderLoading();
    display->drawDisplay();

    // Play Init Tune
    //unsigned int tones[13] = {660,660,0,660,0,510,660,0,770,0,0,0,380};
    //unsigned int toneLengths[13] = {100,100,100,100,100,100,100,100,100,100,100,100,100};
    unsigned int tones[15] = 	{
    							660,000,660,000        ,660,000,
    							        510,000,660,000,
								770,000,
								380,000,
    							};
    unsigned int toneLengths[15] = {
    							NLN,NLN,NLN,3*NLN      ,NLN,3*NLN,
										NLN,NLN,NLN,3*NLN,
								NLN,7*NLN,
								NLN,7*NLN
    };
    buzzer->setMelody(15, tones, toneLengths);

}

void ScreenInit::tick( )
{
    if (!buzzer->isPlaying())
	{
    	manager->setScreen(ScreenManager::MAIN);
	}
}
