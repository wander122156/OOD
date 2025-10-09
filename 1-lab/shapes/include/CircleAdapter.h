#pragma once
#include <CPoint.h>
#include "IShape.h"
#include "SFML/Graphics/CircleShape.hpp"

class CircleAdapter : public IShape
{
public:
    CircleAdapter(const CPoint &m_center, float m_radius);

    float GetArea() const override;
    float GetPerimeter() const override;

    void Draw(sf::RenderWindow& window) const override;

private:
    sf::CircleShape m_circle;
};
