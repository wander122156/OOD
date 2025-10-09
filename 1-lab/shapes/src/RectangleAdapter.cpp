#include "RectangleAdapter.h"

RectangleAdapter::RectangleAdapter(const CPoint& P1, const CPoint& P2)
{
    float width = std::abs(P2.GetX() - P1.GetX());
    float height = std::abs(P2.GetY() - P1.GetY());
    float left = std::min(P1.GetX(), P2.GetX());
    float top = std::min(P1.GetY(), P2.GetY());

    m_rectangle.setSize(sf::Vector2f(width, height));
    m_rectangle.setPosition(left, top);

    m_rectangle.setFillColor(sf::Color::Yellow);
    m_rectangle.setOutlineColor(sf::Color::Black);
    m_rectangle.setOutlineThickness(2.0f);
}

float RectangleAdapter::GetArea() const
{
    return m_rectangle.getSize().x * m_rectangle.getSize().y;
}

float RectangleAdapter::GetPerimeter() const
{
    return 2 * (m_rectangle.getSize().x + m_rectangle.getSize().y);
}

void RectangleAdapter::Draw(sf::RenderWindow& window) const
{
    window.draw(m_rectangle);
}

