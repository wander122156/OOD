#pragma once

#include <CPoint.h>
#include "IShape.h"
#include "SFML/Graphics/CircleShape.hpp"

class CircleAdapter : public IShape
{
public:
    CircleAdapter(const CPoint &m_center, float m_radius);

    RectD GetFrame() const override;
    // void SetFrame(const RectD& frame) override;

    float GetArea() const override;
    float GetPerimeter() const override;

    void Move(CPoint &dxy) override;

    void Draw(sf::RenderWindow &window) const override;

private:
    sf::CircleShape m_circle;
};
