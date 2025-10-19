#pragma once
#include "IShape.h"

struct RectD
{
    double left = 0;
    double top = 0;
    double width = 0;
    double height = 0;

    RectD(double left, double top, double width, double height)
        : left(left), top(top), width(width), height(height) {}

    bool ContainsPoint(double x, double y) const
    {
        return x >= left && x <= left + width &&
               y >= top && y <= top + height;
    }
};
