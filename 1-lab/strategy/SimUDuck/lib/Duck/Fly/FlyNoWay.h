#ifndef FLYNOWAY_H
#define FLYNOWAY_H

#include "IFlyBehavior.h"

class FlyNoWay : public IFlyBehavior
{
public:
    void Fly() override{}

    int GetFlightCount() const override
    {
        return 0;
    }
};

#endif
