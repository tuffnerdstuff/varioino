#ifndef VARIORENDERERBUZZER_H
#define VARIORENDERERBUZZER_H

class VarioRendererBuzzer
{
    public:
    void init();
    void setMelody(int *tones);
    void setTone(int freq, int length);
    void tick();

    private:
    int tones[13] = {660,660,0,660,0,510,660,0,770,0,0,0,380};
    int tonesLength = 13;
    bool toneStarted = false;
    unsigned long lastToneStart = 0;
    int toneIndex = 0;
};

#endif
