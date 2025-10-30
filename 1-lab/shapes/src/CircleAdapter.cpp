#include "CircleAdapter.h"
#include <iomanip>
#include <cmath>

#include "SFML/Graphics/CircleShape.hpp"

CircleAdapter::CircleAdapter(const CPoint &center, float radius)
{
    m_circle.setRadius(radius);
    m_circle.setPosition(center.GetX() - radius, center.GetY() - radius);

    m_circle.setFillColor(sf::Color::Black);
}

RectD CircleAdapter::GetFrame() const
{
    sf::FloatRect bounds = m_circle.getGlobalBounds();
    return {bounds.left, bounds.top, bounds.width, bounds.height};
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

void CircleAdapter::Move(CPoint &dxy)
{

    sf::Vector2f currentPos = m_circle.getPosition();

    m_circle.setPosition(currentPos.x + dxy.GetX(),
                         currentPos.y + dxy.GetY());
}

void CircleAdapter::Draw(sf::RenderWindow &window) const
{
    window.draw(m_circle);
}
