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
        std::cerr << StringConstants::ERROR_OPEN_FILE << filename << std::endl;
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
                CPoint(x, y), r
            ));
        }
    }

    return shapes;
}

void ShapeController::PrintShapesInfo(const std::vector<std::unique_ptr<IShape> > &shapes)
{
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout << StringConstants::SHAPE_SHAPE << (i + 1) << ":" << std::endl;
        std::cout << StringConstants::SHAPE_AREA << shapes[i]->GetArea() << std::endl;
        std::cout << StringConstants::SHAPE_PERIMETR << shapes[i]->GetPerimeter() << std::endl;
        std::cout << std::endl;
    }
}

void ShapeController::DrawShapes(sf::RenderWindow &window, std::vector<std::unique_ptr<IShape> > &shapes)
{
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (auto &shape: shapes)
        {
            shape->Draw(window);
        }
        
        window.display();
    }
}

void ShapeController::Run()
{
    auto shapes = ReadShapesFromFile("shapes.txt");
    PrintShapesInfo(shapes);

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Shapes Visualization");

    DrawShapes(window, shapes);
}
