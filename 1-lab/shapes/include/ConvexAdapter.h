#pragma once

#include "CPoint.h"
#include "IShape.h"
#include <SFML/Graphics/ConvexShape.hpp>

#include "SFML/Graphics/RenderWindow.hpp"

class ConvexAdapter : public IShape
{
public:
    ConvexAdapter(const CPoint &v1, const CPoint &v2, const CPoint &v3);

    RectD GetFrame() const override;

    float GetArea() const override;

    float GetPerimeter() const override;

    void Draw(sf::RenderWindow &window) const override;

private:
    sf::ConvexShape m_convex;

    static float CalculateDistance(const CPoint &a, const CPoint &b);
};
