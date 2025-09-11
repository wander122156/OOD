#ifndef ISHAPESTRATEGY_H
#define ISHAPESTRATEGY_H
#include "IShape.h"

struct IShapeStrategy
{
    virtual ~IShapeStrategy() {};
    virtual void Draw() = 0;
    virtual void SetBounds() = 0;
};
#endif //ISHAPESTRATEGY_H
