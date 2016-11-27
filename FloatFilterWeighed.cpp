#include "FloatFilterWeighed.h"

#define WEIGHT_CURRENT_VALUE 0.025F
#define WEIGHT_LAST_VALUE 1.0F - WEIGHT_CURRENT_VALUE

void FloatFilterWeighed::pushValue(float value)
{
    currValue = (currValue * (1.0F - WEIGHT_CURRENT_VALUE)) + (value * WEIGHT_CURRENT_VALUE);
    if (!this->isReady()) initSamplesRead++;
}

float FloatFilterWeighed::getFilteredValue()
{
    return currValue;
}

bool FloatFilterWeighed::isReady()
{
    return initSamplesRead * WEIGHT_CURRENT_VALUE >= 1.0F;
}
