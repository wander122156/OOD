#pragma once
#include <memory>

#include "IShape.h"

class ShapeFactory
{
public:
    static std::unique_ptr<IShape> CreateShape(std::string &);

    static std::unique_ptr<IShape> CreateTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
    static std::unique_ptr<IShape> CreateRectangle(float x1, float y1, float x2, float y2);
    static std::unique_ptr<IShape> CreateCircle(float x, float y, float r);

private:
    struct ShapeConstants
    {
        static constexpr auto SHAPE_TYPE_TRIANGLE = "TRIANGLE";
        static constexpr auto SHAPE_TYPE_RECTANGLE = "RECTANGLE";
        static constexpr auto SHAPE_TYPE_CIRCLE = "CIRCLE";
    };
};
