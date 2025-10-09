#include "CircleAdapter.h"
#include <iomanip>
#include <cmath>

#include "SFML/Graphics/CircleShape.hpp"


CircleAdapter::CircleAdapter(const CPoint &center, float radius)
{
    m_circle.setRadius(radius);
    m_circle.setPosition(center.GetX() - radius, center.GetY() - radius);

    m_circle.setFillColor(sf::Color::Blue);
    m_circle.setOutlineColor(sf::Color::Black);
    m_circle.setOutlineThickness(2.0f);
}

float CircleAdapter::GetArea() const
{
    float area = M_PI * m_circle.getRadius() * m_circle.getRadius();
    return area;
}

float CircleAdapter::GetPerimeter() const
{
    float perimeter = 2 * M_PI * m_circle.getRadius();
    return perimeter;
}

void CircleAdapter::Draw(sf::RenderWindow& window) const
{
    window.draw(m_circle);
}
