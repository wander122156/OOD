#pragma once
#include "vector"
#include <fstream>
#include <memory>
#include "IShape.h"

class ShapeController
{
public:
    static std::vector<std::unique_ptr<IShape> > ReadShapesFromFile(const std::string &filename);
    static void PrintShapesInfo(const std::vector<std::unique_ptr<IShape> > &shapes);
    void DrawShapes(sf::RenderWindow &window, std::vector<std::unique_ptr<IShape>> &shapes);

    void Run();
private:
    struct StringConstants
    {
        static constexpr auto ERROR_OPEN_FILE = "ERROR: Cannot open file: ";

        static constexpr auto SHAPE_TYPE_TRIANGLE = "TRIANGLE";
        static constexpr auto SHAPE_TYPE_RECTANGLE = "RECTANGLE";
        static constexpr auto SHAPE_TYPE_CIRCLE = "CIRCLE";

        static constexpr auto SHAPE_SHAPE = "Shape ";
        static constexpr auto SHAPE_AREA = " Area: ";
        static constexpr auto SHAPE_PERIMETR = "  Perimeter: ";
    };
};