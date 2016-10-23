#include "MovingAverage.h"
#include <stdint.h>

MovingAverage::MovingAverage(int size)
{   
    cSize = size;
    cBufferData = new float[size];
    cNextFreeIndex = 0;
    cSlotsFilled = 0;
}

MovingAverage::~MovingAverage()
{
    delete[] cBufferData;
}

void MovingAverage::push(float data)
{
    cBufferData[cNextFreeIndex] = data;
    
    cNextFreeIndex = (cNextFreeIndex + 1) % cSize;
    
    if (cSlotsFilled < cSize)
    {
        cSlotsFilled++;
    }
}

float MovingAverage::getAverage()
{
    float sum = 0;
    int count = cSlotsFilled < cSize ? cSlotsFilled : cSize;
    int i;
    
    for (i = 0; i < count; i++)
    {
        sum += cBufferData[positive_modulo((cNextFreeIndex-1-i) , cSize)];
    }
    
    if (count > 0)
    {
        sum /= count;
    }
    
    return sum;
    
}

inline int MovingAverage::positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

