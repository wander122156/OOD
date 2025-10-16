#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "IShape.h"
#include "CircleAdapter.h"
#include "RectangleAdapter.h"
#include "ConvexAdapter.h"
#include "ShapeController.h"


std::vector<std::unique_ptr<IShape> > ShapeController::ReadShapesFromFile(const std::string &filename)
{
    std::vector<std::unique_ptr<IShape> > shapes;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << ShapeController::StringConstants::ERROR_OPEN_FILE << filename << std::endl;
        return shapes;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string shapeType;
        ss >> shapeType;

        if (shapeType == StringConstants::SHAPE_TYPE_TRIANGLE)
        {
            std::string p1, p2, p3;
            float x1, y1, x2, y2, x3, y3;

            ss >> p1 >> x1 >> y1 >> p2 >> x2 >> y2 >> p3 >> x3 >> y3;

            shapes.push_back(std::make_unique<ConvexAdapter>(
                    CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3)
            ));
        } else if (shapeType == StringConstants::SHAPE_TYPE_RECTANGLE)
        {
            std::string p1, p2;
            float x1, y1, x2, y2;

            ss >> p1 >> x1 >> y1 >> p2 >> x2 >> y2;

            shapes.push_back(std::make_unique<RectangleAdapter>(
                    CPoint(x1, y1), CPoint(x2, y2)
            ));

        } else if (shapeType == StringConstants::SHAPE_TYPE_CIRCLE)
        {
            std::string center, radius;
            float x, y, r;

            ss >> center >> x >> y >> radius >> r;

            shapes.push_back(std::make_unique<CircleAdapter>(
                    CPoint(x, y), static_cast<float>(r)
            ));
        }
    }

    return shapes;
}

void ShapeController::PrintShapesInfo(const std::vector<std::unique_ptr<IShape> > &shapes)
{
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout << ShapeController::StringConstants::SHAPE_SHAPE << (i + 1) << ":" << std::endl;
        std::cout << ShapeController::StringConstants::SHAPE_AREA << shapes[i]->GetArea() << std::endl;
        std::cout << ShapeController::StringConstants::SHAPE_PERIMETR << shapes[i]->GetPerimeter() << std::endl;
        std::cout << std::endl;
    }
}