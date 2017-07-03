#include "SpeakerPWM.h"

#include "toneAC.h"

#define TONE_VOL 2

void SpeakerPWM::init()
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
}

void SpeakerPWM::setMelody(unsigned int tonesCount, unsigned int* tones, unsigned int* toneLengths) {

	if (!isPlaying()&&tonesCount <= MAX_TONES)
	{
		for (unsigned int i = 0; i < tonesCount; ++i) {
			this->tones[i]=tones[i];
			this->toneLengths[i]=toneLengths[i];
		}
		this->tonesCount = tonesCount;
		reset();
	}

}

void SpeakerPWM::reset() {
	toneStartTime = 0;
	firstToneTick = false;
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
	return toneIndex >= 0 && toneIndex < tonesCount && toneIndex < MAX_TONES;
}

void SpeakerPWM::tick()
{
	if (isPlaying())
	{
		if (!firstToneTick) // Start current tone
		{
			toneStartTime = millis();
			firstToneTick = true;
			if (tones[toneIndex] > 0)
			{
				toneAC(tones[toneIndex], TONE_VOL, 0, true);
				digitalWrite(LED_BUILTIN, HIGH); // LED ON
			}
			else
			{
				noToneAC();
				digitalWrite(LED_BUILTIN, LOW); // LED OFF
			}
		}
		else if(millis() - toneStartTime >= toneLengths[toneIndex]) // current tone done
		{
			digitalWrite(LED_BUILTIN, LOW); // LED OFF
			noToneAC();
			firstToneTick = false;
			toneIndex++;
		}





		/*
	  if (!firstToneTick && millis() - toneStartTime >= toneLengths[toneIndex])
	  {
		  // tone end = next tone
		  noToneAC();
		  digitalWrite(LED_BUILTIN, LOW);
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

			  // continue current tone
			  if (tones[toneIndex] > 0)
			  {
				  toneAC(tones[toneIndex], TONE_VOL, TICK_LENGTH, true);
				  digitalWrite(LED_BUILTIN, HIGH);
			  }
		  }

	  }*/
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

