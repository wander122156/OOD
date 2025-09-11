#include "CCircle.h"
#include <sstream>
#include <iomanip>
#include <cmath>

CCircle::CCircle(const CPoint &center, double radius,
                 uint32_t outlineColor, uint32_t fillColor)
        : m_center(center),
          m_radius(radius),
          m_outlineColor(outlineColor),
          m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
    std::ostringstream oss;
    oss << "Circle: center(" << m_center.GetX() << ", " << m_center.GetY() << "), "
        << "Radius=" << m_radius << ", "
        << "Outline color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor << ", "
        << "Fill color: #" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;
    return oss.str();
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}


