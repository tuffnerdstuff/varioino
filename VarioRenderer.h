#ifndef VARIORENDERER_H
#define VARIORENDERER_H

class VarioRenderer
{
    public:
    virtual void init() = 0;
    virtual void renderValues(float vario, float altitude, float temp) = 0;
    
};

#endif
