#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <stdio.h>
#include "FloatFilter.h"

class FloatFilterMovingAverage: public FloatFilter
{
    public:
    FloatFilterMovingAverage(int size);
    ~FloatFilterMovingAverage();
    void pushValue(float value);
    float getFilteredValue();
    bool isReady();
    
    private:
    int cSize;
    float *cBufferData = NULL;
    int cNextFreeIndex;
    int cSlotsFilled;
    inline int positive_modulo(int i, int n);
};

#endif

