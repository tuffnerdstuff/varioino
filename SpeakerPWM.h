#ifndef VARIORENDERERBUZZER_H
#define VARIORENDERERBUZZER_H

class SpeakerPWM
{
    public:
    void init();
    void setMelody(int *tones);
    void setTone(unsigned int freq, unsigned int length);
    void tick();
    int getVolume();
    void setVolume(int vol);

    private:
    int tonesCount = 13;
    unsigned int tones[13] = {660,660,0,660,0,510,660,0,770,0,0,0,380};
    unsigned int toneLengths[13] = {100,100,100,100,100,100,100,100,100,100,100,100,100};
    unsigned long toneStartTime = 0;
    bool firstToneTick = true;
    int toneIndex = 0;
    int volume = 10;

	void reset();
	bool isPlaying();
};

#endif
