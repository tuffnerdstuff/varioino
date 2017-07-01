#ifndef VARIORENDERERBUZZER_H
#define VARIORENDERERBUZZER_H

#define MAX_TONES 15

class SpeakerPWM
{
    public:
    void init();
    void setMelody(unsigned int tonesCount, unsigned int* tones, unsigned int* toneLengths);
    void setTone(unsigned int freq, unsigned int length);
    void tick();
    int getVolume();
    void setVolume(int vol);
	bool isPlaying();

    private:
    int tonesCount = 0;
    unsigned int tones[MAX_TONES];
    unsigned int toneLengths[MAX_TONES];
    unsigned long toneStartTime = 0;
    bool firstToneTick = false;
    int toneIndex = MAX_TONES;
    int volume = 1;

	void reset();
};

#endif
