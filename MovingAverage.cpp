#include "MovingAverage.h"
#include <stdio.h>
#include <stdint.h>

MovingAverage::MovingAverage(int size)
{   
    
    cBufferData = new float[size];
    cSize = (cBufferData != NULL) ? size : 0;
    cNextFreeIndex = 0;
    cSlotsFilled = 0;
}

MovingAverage::~MovingAverage()
{
    delete[] cBufferData;
}

void MovingAverage::pushValue(float data)
{
    if (cSize > 0)
    {
      cBufferData[cNextFreeIndex] = data;
      
      cNextFreeIndex = (cNextFreeIndex + 1) % cSize;
      
      if (cSlotsFilled < cSize)
      {
          cSlotsFilled++;
      }
    }
}

float MovingAverage::getFilteredValue()
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

bool MovingAverage::isReady()
{
  return cSize == cSlotsFilled;
}

inline int MovingAverage::positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

