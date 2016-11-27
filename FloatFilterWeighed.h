#ifndef FLOATFILTERWEIGHED_H
#define FLOATFILTERWEIGHED_H

#include "FloatFilter.h"

class FloatFilterWeighed: public FloatFilter
{
    public:
    void pushValue(float value);
    float getFilteredValue();
    bool isReady();
    
    private:
    float currValue = 0;
    unsigned int initSamplesRead = 0;
};
#endif
