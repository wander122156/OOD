
// ВЫНЕСТИ В КЛАСС
//SHARED PTR ВМЕСТО UNIC
// КОДИНГ КОНВЕНТИОНС
#pragma once

#include <vector>
#include <memory>
#include "IShape.h"

class ShapeParser
{
public:
    static std::vector<std::shared_ptr<IShape>> ParseFromInput();
    static std::shared_ptr<IShape> ParseShape(const std::string &line);

    static std::shared_ptr<IShape> FindMaxArea(const std::vector<std::shared_ptr<IShape>> &shapes);
    static std::shared_ptr<IShape> FindMinPerimeter(const std::vector<std::shared_ptr<IShape>> &shapes);

    static void PrintShapeInfo(const std::shared_ptr<IShape> &shape);

    class Validator
    {
    public:
        static bool IsTriangleValid(const CPoint &v1, const CPoint &v2, const CPoint &v3);
        static bool IsRectangleValid(double width, double height);
        static bool IsCircleValid(double radius);
        static bool IsLineSegmentValid(const CPoint &start, const CPoint &end);
    };

private:
    static std::shared_ptr<IShape> ParseLine(std::istream &iss);
    static std::shared_ptr<IShape> ParseTriangle(std::istream &iss);
    static std::shared_ptr<IShape> ParseRectangle(std::istream &iss);
    static std::shared_ptr<IShape> ParseCircle(std::istream &iss);
    static CPoint ParsePoint(std::istream &iss);
    static uint32_t ParseColor(const std::string &colorStr);

    struct StringConstants
    {
        static constexpr auto END_MARKER = "end";
        static constexpr auto ERROR_PARSING_SHAPE = "Error parsing shape: ";
        static constexpr auto SHAPE_NULL = "Shape is null";
        static constexpr auto AREA_LABEL = "Area: ";
        static constexpr auto PERIMETER_LABEL = "Perimeter: ";
        static constexpr auto OUTLINE_COLOR_LABEL = "Outline color: #";
        static constexpr auto FILL_COLOR_LABEL = "Fill color: #";

        static constexpr auto DEGENERATE_LINE = "Degenerate line segment";
        static constexpr auto DEGENERATE_TRIANGLE = "Degenerate triangle";
        static constexpr auto INVALID_RECTANGLE = "Invalid rectangle dimensions";
        static constexpr auto INVALID_CIRCLE = "Invalid circle radius";

        static constexpr auto TYPE_LINE = "line";
        static constexpr auto TYPE_TRIANGLE = "triangle";
        static constexpr auto TYPE_RECTANGLE = "rectangle";
        static constexpr auto TYPE_CIRCLE = "circle";
    };
};