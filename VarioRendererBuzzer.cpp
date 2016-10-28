#include "VarioRendererBuzzer.h"
#include "toneAC.h"


#define TONE_VOL 0
#define TONE_MULT 300

void VarioRendererBuzzer::init()
{
  
}

bool VarioRendererBuzzer::renderLoading(unsigned long pollDelay)
{
  return false;
}

void VarioRendererBuzzer::renderValues(float vario, float altitude, float temp, long renderDelay)
{

  if (vario > 0.3)
  {
    toneAC(690 + (150 * vario), TONE_VOL, renderDelay * 0.6, true);
  }

}

