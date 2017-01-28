#include "VarioRendererBuzzer.h"
#include "toneAC.h"

#define TONE_LENGTH 100
#define TONE_VOL 10
#define TONE_MULT 300
#define MIN_VARIO 0.5

void VarioRendererBuzzer::init()
{
  // Buzzer's always ready to buzz :)
}

void VarioRendererBuzzer::setMelody(int* tones) {
}

void VarioRendererBuzzer::setTone(int freq, int length) {

}

void VarioRendererBuzzer::tick()
{
  if(toneIndex >= tonesLength)
  {
   return;
  }
  else if (!toneStarted || millis() - lastToneStart >= TONE_LENGTH)
  {
    lastToneStart = millis();
    toneStarted = true;
    int freq = tones[toneIndex++];
    if (freq > 0)
    {
      toneAC(freq, TONE_VOL, TONE_LENGTH, true);
    }
    else
    {
      noToneAC();
    }

  }
  
}

/*void VarioRendererBuzzer::renderValues(float vario, float altitude, float temp, long renderDelay)
{

  if (vario > MIN_VARIO)
  {
    toneAC(690 + (150 * vario), TONE_VOL, renderDelay * 0.6, true);
  }

}
*/

