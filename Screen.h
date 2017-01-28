#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:
		virtual void init() = 0;
        virtual void tick() = 0;
};

#endif
