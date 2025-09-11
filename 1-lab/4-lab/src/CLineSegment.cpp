#include "CLineSegment.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CLineSegment::CLineSegment(const CPoint &start, const CPoint &end, uint32_t outlineColor)
        : m_start(start), m_end(end), m_outlineColor(outlineColor)
{}

double CLineSegment::GetArea() const
{ return 0.0; }

double CLineSegment::GetPerimeter() const
{
    double dx = m_end.GetX() - m_start.GetX();
    double dy = m_end.GetY() - m_start.GetY();
    return sqrt(dx * dx + dy * dy);
}

std::string CLineSegment::ToString() const
{
    std::ostringstream oss;
    oss << "LineSegment: Start(" << m_start.GetX() << ", " << m_start.GetY()
        << "), End(" << m_end.GetX() << ", " << m_end.GetY()
        << "), OutlineColor=#" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor;
    return oss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{ return m_outlineColor; }

