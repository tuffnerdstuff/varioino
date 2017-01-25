#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:
        virtual void tick( long lastTick ) = 0;
}

#endif
