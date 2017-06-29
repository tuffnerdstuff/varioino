#ifndef FLOATFILTER_H
#define FLOATFILTER_H

class FloatFilter
{
    public:
	virtual ~FloatFilter(){};
    virtual void pushValue(float value) = 0;
    virtual float getFilteredValue() = 0;
    virtual bool isReady() = 0;
};
#endif
