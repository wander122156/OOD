#include "../include/ShapeFactory.h"

#include <CPoint.h>
#include <fstream>
#include <sstream>

#include "CircleAdapter.h"
#include "ConvexAdapter.h"
#include "RectangleAdapter.h"

std::unique_ptr<IShape> ShapeFactory::CreateShape(std::string& description)
{
    std::istringstream iss(description);
    std::string shapeType;
    iss >> shapeType;
    if (shapeType == ShapeConstants::SHAPE_TYPE_TRIANGLE) {
        std::string p1, p2, p3;
        float x1, y1, x2, y2, x3, y3;

        if (iss >> p1 >> x1 >> y1 >> p2 >> x2 >> y2 >> p3 >> x3 >> y3) {
            return CreateTriangle(x1, y1, x2, y2, x3, y3);
        }
    }
    else if (shapeType == ShapeConstants::SHAPE_TYPE_RECTANGLE) {
        std::string p1, p2;
        float x1, y1, x2, y2;

        if (iss >> p1 >> x1 >> y1 >> p2 >> x2 >> y2) {
            return CreateRectangle(x1, y1, x2, y2);
        }
    }
    else if (shapeType == ShapeConstants::SHAPE_TYPE_CIRCLE) {
        std::string center, radius;
        float x, y, r;

        if (iss >> center >> x >> y >> radius >> r) {
            return CreateCircle(x, y, r);
        }
    }

    return nullptr;
}

std::unique_ptr<IShape> ShapeFactory::CreateTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    return std::make_unique<ConvexAdapter>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3));
}

std::unique_ptr<IShape> ShapeFactory::CreateRectangle(float x1, float y1, float x2, float y2)
{
    return std::make_unique<RectangleAdapter>(CPoint(x1, y1), CPoint(x2, y2));
}

std::unique_ptr<IShape> ShapeFactory::CreateCircle(float x, float y, float r)
{
    return std::make_unique<CircleAdapter>(CPoint(x, y), r);
}