#include "SpeakerPWM.h"

#include "toneAC.h"

#define TONE_VOL 10
#define TICK_LENGTH 200

void SpeakerPWM::init()
{
  // Buzzer's always ready to buzz :)
}

void SpeakerPWM::setMelody(int* tones) {
	// TODO: implement setMelody
}

void SpeakerPWM::reset() {
	toneStartTime = 0;
	firstToneTick = true;
	toneIndex = 0;
}

void SpeakerPWM::setTone(unsigned int freq, unsigned int length) {

	if (!isPlaying())
	{
		tones[0] = freq;
		toneLengths[0] = length;
		tonesCount = 1;
		reset();
	}
}

bool SpeakerPWM::isPlaying() {
	return toneIndex >= 0 && toneIndex < tonesCount;
}

void SpeakerPWM::tick()
{
	if (isPlaying())
  {
	  if (!firstToneTick && millis() - toneStartTime >= toneLengths[toneIndex])
	  {
		  // tone end = next tone
		  noToneAC();
		  firstToneTick = true;
		  toneIndex++;
	  }
	  else
	  {
		  if (firstToneTick)
		  {
			  // reset tone start time
			  toneStartTime = millis();
			  firstToneTick = false;
		  }
		  // continue current tone
		  if (tones[toneIndex] > 0)
		  {
			  toneAC(tones[toneIndex], TONE_VOL, TICK_LENGTH, true);
		  }
	  }
  }

  
}

int SpeakerPWM::getVolume() {
	return volume;
}

void SpeakerPWM::setVolume(int vol) {
	volume = vol;
}
/*void VarioRendererBuzzer::renderValues(float vario, float altitude, float temp, long renderDelay)
{

  if (vario > MIN_VARIO)
  {
    toneAC(690 + (150 * vario), TONE_VOL, renderDelay * 0.6, true);
  }

}
*/

