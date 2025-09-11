#pragma once

#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
    CTriangle(const CPoint &v1, const CPoint &v2, const CPoint &v3,
              uint32_t outlineColor, uint32_t fillColor);

    double GetArea() const override;

    double GetPerimeter() const override;

    std::string ToString() const override;

    uint32_t GetOutlineColor() const override;

    uint32_t GetFillColor() const override;


private:
    CPoint m_v1;
    CPoint m_v2;
    CPoint m_v3;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};