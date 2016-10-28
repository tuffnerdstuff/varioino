#include "VarioRendererBuzzer.h"
#include "toneAC.h"

#define TONE_LENGTH 100
#define TONE_VOL 1
#define TONE_MULT 300

void VarioRendererBuzzer::init()
{
  // Buzzer's always ready to buzz :)
}

bool VarioRendererBuzzer::renderLoading(unsigned long pollDelay)
{
  if(initToneIndex >= initTonesLength)
  {
   return false; 
  }
  else if (!initToneStarted || millis() - lastToneStart >= TONE_LENGTH)
  {
    lastToneStart = millis();
    initToneStarted = true;
    int freq = initTones[initToneIndex++];
    if (freq > 0)
    {
      toneAC(freq, TONE_VOL, TONE_LENGTH, true);
    }
    else
    {
      noToneAC();
    }

    return true;
    
  }
  
}

void VarioRendererBuzzer::renderValues(float vario, float altitude, float temp, long renderDelay)
{

  if (vario > 0.3)
  {
    toneAC(690 + (150 * vario), TONE_VOL, renderDelay * 0.6, true);
  }

}

