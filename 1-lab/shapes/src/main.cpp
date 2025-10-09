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

std::vector<std::unique_ptr<IShape> > ReadShapesFromFile(const std::string &filename)
{
    std::vector<std::unique_ptr<IShape> > shapes;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()){
        std::cerr << "ERROR: Cannot open file: " << filename << std::endl;
        return shapes;
    }

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string shapeType;
        ss >> shapeType;

        if (shapeType == "TRIANGLE"){
            std::string p1, p2, p3;
            float x1, y1, x2, y2, x3, y3;

            ss >> p1 >> x1 >> y1 >> p2 >> x2 >> y2 >> p3 >> x3 >> y3;

            if (p1 == "P1" && p2 == "P2" && p3 == "P3"){
                shapes.push_back(std::make_unique<ConvexAdapter>(
                    CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3)
                ));
            }
        } else if (shapeType == "RECTANGLE"){
            std::string p1, p2;
            float x1, y1, x2, y2;

            ss >> p1 >> x1 >> y1 >> p2 >> x2 >> y2;

            if (p1 == "P1" && p2 == "P2"){
                shapes.push_back(std::make_unique<RectangleAdapter>(
                    CPoint(x1, y1), CPoint(x2, y2)
                ));
            }
        } else if (shapeType == "CIRCLE"){
            std::string center, radius;
            float x, y, r;

            ss >> center >> x >> y >> radius >> r;

            if (center == "C" && radius == "R"){
                shapes.push_back(std::make_unique<CircleAdapter>(
                    CPoint(x, y), static_cast<float>(r)
                ));
            }
        }
    }

    return shapes;
}

void PrintShapesInfo(const std::vector<std::unique_ptr<IShape> > &shapes)
{
    std::cout << "=== Shapes Information ===" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i){
        std::cout << "Shape " << (i + 1) << ":" << std::endl;
        std::cout << "  Area: " << shapes[i]->GetArea() << std::endl;
        std::cout << "  Perimeter: " << shapes[i]->GetPerimeter() << std::endl;
        std::cout << std::endl;
    }
}

int main()
{
    auto shapes = ReadShapesFromFile("shapes.txt");

    // Вывод информации в консоль
    PrintShapesInfo(shapes);

    // Визуализация в SFML
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Shapes");

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (auto &shape: shapes){
            shape->Draw(window);
        }

        window.display();
    }

    return 0;
}
