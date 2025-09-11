#include "CTriangle.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CTriangle::CTriangle(const CPoint &v1, const CPoint &v2, const CPoint &v3,
                     uint32_t outlineColor, uint32_t fillColor)
        : m_v1(v1), m_v2(v2), m_v3(v3),
          m_outlineColor(outlineColor), m_fillColor(fillColor)
{}

double CTriangle::GetArea() const
{
    return 0.5 * abs(
            (m_v2.GetX() - m_v1.GetX()) * (m_v3.GetY() - m_v1.GetY()) -
            (m_v3.GetX() - m_v1.GetX()) * (m_v2.GetY() - m_v1.GetY())
    );
}

double CTriangle::GetPerimeter() const
{
    double side1 = sqrt(pow(m_v2.GetX() - m_v1.GetX(), 2) + pow(m_v2.GetY() - m_v1.GetY(), 2));
    double side2 = sqrt(pow(m_v3.GetX() - m_v2.GetX(), 2) + pow(m_v3.GetY() - m_v2.GetY(), 2));
    double side3 = sqrt(pow(m_v1.GetX() - m_v3.GetX(), 2) + pow(m_v1.GetY() - m_v3.GetY(), 2));

    return side1 + side2 + side3;
}

std::string CTriangle::ToString() const
{
    std::ostringstream oss;
    oss << "Triangle: "
        << "Vertex1(" << m_v1.GetX() << ", " << m_v1.GetY() << "), "
        << "Vertex2(" << m_v2.GetX() << ", " << m_v2.GetY() << "), "
        << "Vertex3(" << m_v3.GetX() << ", " << m_v3.GetY() << "), "
        << "OutlineColor=#" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor
        << ", FillColor=#" << std::setw(6) << m_fillColor;
    return oss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

