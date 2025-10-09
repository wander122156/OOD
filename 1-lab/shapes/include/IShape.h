#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

class IShape
{
public:
    virtual ~IShape() = default;

    virtual float GetArea() const = 0;
    virtual float GetPerimeter() const = 0;

    virtual void Draw(sf::RenderWindow &window) const = 0;
};
