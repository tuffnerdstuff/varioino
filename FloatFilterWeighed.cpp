#include "FloatFilterWeighed.h"

FloatFilterWeighed::FloatFilterWeighed(float currValWeight, float initValue) {
	this->currValWeight = currValWeight;
	this->currValue = initValue;
}

void FloatFilterWeighed::pushValue(float value)
{
    currValue = (currValue * (1.0F - currValWeight)) + (value * currValWeight);
    if (!this->isReady()) initSamplesRead++;
}

float FloatFilterWeighed::getFilteredValue()
{
    return currValue;
}

bool FloatFilterWeighed::isReady()
{
    return initSamplesRead * currValWeight >= 1.0F;
}

