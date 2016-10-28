#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

class MovingAverage
{
    public:
    MovingAverage(int size);
    ~MovingAverage();
    void push(float data);
    float getAverage();
    bool isFull();
    
    private:
    int cSize;
    float *cBufferData;
    int cNextFreeIndex;
    int cSlotsFilled;
    inline int positive_modulo(int i, int n);
};

#endif

