#pragma once

#include <CPoint.h>
#include "IShape.h"
#include "SFML/Graphics/RectangleShape.hpp"

class RectangleAdapter : public IShape
{
public:
    RectangleAdapter(const CPoint &P1, const CPoint &P2);

    float GetArea() const override;

    float GetPerimeter() const override;

    void Draw(sf::RenderWindow &window) const override;

private:
    sf::RectangleShape m_rectangle;
};