#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:
		virtual void init() = 0;
        virtual void tick( long lastTick ) = 0;
};

#endif
