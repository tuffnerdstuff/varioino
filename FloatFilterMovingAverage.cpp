#include "FloatFilterMovingAverage.h"
#include <stdio.h>
#include <stdint.h>

FloatFilterMovingAverage::FloatFilterMovingAverage(int size)
{   
    
    cBufferData = new float[size];
    cSize = (cBufferData != NULL) ? size : 0;
    cNextFreeIndex = 0;
    cSlotsFilled = 0;
}

FloatFilterMovingAverage::~FloatFilterMovingAverage()
{
    delete[] cBufferData;
}

void FloatFilterMovingAverage::pushValue(float data)
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

float FloatFilterMovingAverage::getFilteredValue()
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

bool FloatFilterMovingAverage::isReady()
{
  return cSize == cSlotsFilled;
}

inline int FloatFilterMovingAverage::positive_modulo(int i, int n)
{
    return (i % n + n) % n;
}

