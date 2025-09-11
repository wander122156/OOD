#include "CRectangle.h"
#include <sstream>
#include <iomanip>

CRectangle::CRectangle(const CPoint &topLeft, double width, double height,
                       uint32_t outlineColor, uint32_t fillColor)
        : m_leftTop(topLeft), m_width(width), m_height(height),
          m_outlineColor(outlineColor), m_fillColor(fillColor)
{}

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
    std::ostringstream oss;
    oss << "Rectangle: top left(" << m_leftTop.GetX() << ", " << m_leftTop.GetY() << "), "
        << "width= " << m_width << ", height= " << m_height << ", "
        << "Outline color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor
        << "Fill color: #" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;
    return oss.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

