#include "ConvexAdapter.h"
#include <cmath>

ConvexAdapter::ConvexAdapter(const CPoint &v1, const CPoint &v2, const CPoint &v3)
{
    m_convex.setPointCount(3);

    m_convex.setPoint(0, sf::Vector2f(v1.GetX(), v1.GetY()));
    m_convex.setPoint(1, sf::Vector2f(v2.GetX(), v2.GetY()));
    m_convex.setPoint(2, sf::Vector2f(v3.GetX(), v3.GetY()));

    m_convex.setFillColor(sf::Color::Red);
}

RectD ConvexAdapter::GetFrame() const
{
    sf::FloatRect bounds = m_convex.getGlobalBounds();
    return {bounds.left, bounds.top, bounds.width, bounds.height};
}

float ConvexAdapter::GetArea() const
{
    sf::Vector2f p1 = m_convex.getPoint(0);
    sf::Vector2f p2 = m_convex.getPoint(1);
    sf::Vector2f p3 = m_convex.getPoint(2);

    return std::abs((p1.x * (p2.y - p3.y) +
                        p2.x * (p3.y - p1.y) +
                        p3.x * (p1.y - p2.y)) / 2.0f
    );
}

float ConvexAdapter::GetPerimeter() const
{
    sf::Vector2f p1 = m_convex.getPoint(0);
    sf::Vector2f p2 = m_convex.getPoint(1);
    sf::Vector2f p3 = m_convex.getPoint(2);

    float side1 = CalculateDistance(CPoint(p1.x, p1.y), CPoint(p2.x, p2.y));
    float side2 = CalculateDistance(CPoint(p2.x, p2.y), CPoint(p3.x, p3.y));
    float side3 = CalculateDistance(CPoint(p3.x, p3.y), CPoint(p1.x, p1.y));

    return side1 + side2 + side3;
}

void ConvexAdapter::Draw(sf::RenderWindow &window) const
{
    window.draw(m_convex);
}

float ConvexAdapter::CalculateDistance(const CPoint &a, const CPoint &b)
{
    float dx = b.GetX() - a.GetX();
    float dy = b.GetY() - a.GetY();
    return std::sqrt(dx * dx + dy * dy);
}