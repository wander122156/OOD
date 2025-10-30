#include "RectangleAdapter.h"

RectangleAdapter::RectangleAdapter(const CPoint &P1, const CPoint &P2)
{
    float width = std::abs(P2.GetX() - P1.GetX());
    float height = std::abs(P2.GetY() - P1.GetY());
    float left = std::min(P1.GetX(), P2.GetX());
    float top = std::min(P1.GetY(), P2.GetY());

    m_rectangle.setSize(sf::Vector2f(width, height));
    m_rectangle.setPosition(left, top);

    m_rectangle.setFillColor(sf::Color::Yellow);
}

RectD RectangleAdapter::GetFrame() const
{
    sf::FloatRect bounds = m_rectangle.getGlobalBounds();
    return {bounds.left, bounds.top, bounds.width, bounds.height};
}

float RectangleAdapter::GetArea() const
{
    return m_rectangle.getSize().x * m_rectangle.getSize().y;
}

float RectangleAdapter::GetPerimeter() const
{
    return 2 * (m_rectangle.getSize().x + m_rectangle.getSize().y);
}

void RectangleAdapter::Move(CPoint &dxy)
{
    sf::Vector2f currentPos = m_rectangle.getPosition();

    m_rectangle.setPosition(currentPos.x + dxy.GetX(),
                            currentPos.y + dxy.GetY());
}

void RectangleAdapter::Draw(sf::RenderWindow &window) const
{
    window.draw(m_rectangle);
}

