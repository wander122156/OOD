#pragma once

#include <CPoint.h>

#include "SFML/Graphics/RenderWindow.hpp"
#include "RectD.h"

class IShape
{
public:
    virtual ~IShape() = default;

    virtual float GetArea() const = 0;

    virtual float GetPerimeter() const = 0;

    virtual RectD GetFrame() const = 0;
    // virtual void SetFrame(const RectD& frame) = 0;

    virtual void Move(CPoint &dxy) = 0;

    virtual void Draw(sf::RenderWindow &window) const = 0;
};
