#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include "IShapeStrategy.h"

class IShape
{
public:
    virtual ~IShape() = default;

    virtual double GetArea() const = 0;

    virtual double GetPerimeter() const = 0;

    virtual void Draw() const = 0;

protected:
    std::unique_ptr<IShapeStrategy> m_shapeStrategy;
    std::string m_color;
};