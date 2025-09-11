#include "ShapeParser.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

std::vector<std::shared_ptr<IShape>> ShapeParser::ParseFromInput()
{
    std::vector<std::shared_ptr<IShape>> shapes;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line == ShapeParser::StringConstants::END_MARKER) break;

        try
        {
            auto shape = ParseShape(line);
            if (shape) shapes.push_back(shape);
        } catch (const std::exception &e)
        {
            std::cerr << ShapeParser::StringConstants::ERROR_PARSING_SHAPE << e.what()
                      << "\nInput: " << line << std::endl;
        }
    }
    return shapes;
}

std::shared_ptr<IShape> ShapeParser::ParseShape(const std::string &line)
{
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == ShapeParser::StringConstants::TYPE_LINE) return ParseLine(iss);
    if (type == ShapeParser::StringConstants::TYPE_TRIANGLE) return ParseTriangle(iss);
    if (type == ShapeParser::StringConstants::TYPE_RECTANGLE) return ParseRectangle(iss);
    if (type == ShapeParser::StringConstants::TYPE_CIRCLE) return ParseCircle(iss);

    throw std::invalid_argument("Unknown shape type: " + type);
}

std::shared_ptr<IShape> ShapeParser::ParseLine(std::istream &iss)
{
    CPoint start = ParsePoint(iss);
    CPoint end = ParsePoint(iss);
    std::string colorStr;
    iss >> colorStr;

    if (!Validator::IsLineSegmentValid(start, end))
    {
        throw std::invalid_argument(StringConstants::DEGENERATE_LINE);
    }

    return std::make_shared<CLineSegment>(start, end, ParseColor(colorStr));
}

std::shared_ptr<IShape> ShapeParser::ParseTriangle(std::istream &iss)
{
    CPoint v1 = ParsePoint(iss);
    CPoint v2 = ParsePoint(iss);
    CPoint v3 = ParsePoint(iss);
    std::string outlineColor, fillColor;
    iss >> outlineColor >> fillColor;

    if (!Validator::IsTriangleValid(v1, v2, v3))
    {
        throw std::invalid_argument(StringConstants::DEGENERATE_TRIANGLE);
    }

    return std::make_shared<CTriangle>(v1, v2, v3,ParseColor(outlineColor), ParseColor(fillColor));
}

std::shared_ptr<IShape> ShapeParser::ParseRectangle(std::istream &iss)
{
    CPoint leftTop = ParsePoint(iss);
    double width, height;
    std::string outlineColor, fillColor;
    iss >> width >> height >> outlineColor >> fillColor;

    if (!Validator::IsRectangleValid(width, height))
    {
        throw std::invalid_argument(StringConstants::INVALID_RECTANGLE);
    }

    return std::make_shared<CRectangle>(leftTop, width, height,
                                        ParseColor(outlineColor), ParseColor(fillColor));
}

std::shared_ptr<IShape> ShapeParser::ParseCircle(std::istream &iss)
{
    CPoint center = ParsePoint(iss);
    double radius;
    std::string outlineColor, fillColor;
    iss >> radius >> outlineColor >> fillColor;

    if (!Validator::IsCircleValid(radius))
    {
        throw std::invalid_argument(StringConstants::INVALID_CIRCLE);
    }

    return std::make_shared<CCircle>(center, radius,
                                     ParseColor(outlineColor), ParseColor(fillColor));
}

std::shared_ptr<IShape> ShapeParser::FindMaxArea(const std::vector<std::shared_ptr<IShape>> &shapes)
{
    if (shapes.empty()) return nullptr;
    //* сам элемент
    return *std::max_element(shapes.begin(), shapes.end(),
                             [](const auto &a, const auto &b)
                             { return a->GetArea() < b->GetArea(); });
}

std::shared_ptr<IShape> ShapeParser::FindMinPerimeter(const std::vector<std::shared_ptr<IShape>> &shapes)
{
    if (shapes.empty()) return nullptr;
    return *std::min_element(shapes.begin(), shapes.end(),
                             [](const auto &a, const auto &b)
                             { return a->GetPerimeter() < b->GetPerimeter(); });
}

void ShapeParser::PrintShapeInfo(const std::shared_ptr<IShape> &shape)
{
    if (!shape)
    {
        std::cout << StringConstants::SHAPE_NULL << std::endl;
        return;
    }

    std::cout << shape->ToString() << std::endl
              << StringConstants::AREA_LABEL << shape->GetArea() << std::endl
              << StringConstants::PERIMETER_LABEL << shape->GetPerimeter() << std::endl
              << StringConstants::OUTLINE_COLOR_LABEL
              << std::hex << std::setw(6) << std::setfill('0')
              << shape->GetOutlineColor() << std::dec;

    if (auto solidShape = std::dynamic_pointer_cast<ISolidShape>(shape))
    {
        std::cout << std::endl << StringConstants::FILL_COLOR_LABEL
                  << std::setw(6) << solidShape->GetFillColor() << std::dec;
    }
}

bool ShapeParser::Validator::IsTriangleValid(const CPoint &v1, const CPoint &v2, const CPoint &v3)
{
    double area = 0.5 * std::abs(
            (v2.GetX() - v1.GetX()) * (v3.GetY() - v1.GetY()) -
            (v3.GetX() - v1.GetX()) * (v2.GetY() - v1.GetY()));
    return area > 0;
}

bool ShapeParser::Validator::IsRectangleValid(double width, double height)
{
    return width > 0 && height > 0;
}

bool ShapeParser::Validator::IsCircleValid(double radius)
{
    return radius > 0;
}

bool ShapeParser::Validator::IsLineSegmentValid(const CPoint &start, const CPoint &end)
{
    double dx = end.GetX() - start.GetX();
    double dy = end.GetY() - start.GetY();
    return (dx * dx + dy * dy) > 0;
}

CPoint ShapeParser::ParsePoint(std::istream &iss)
{
    double x, y;
    if (!(iss >> x >> y))
    {
        throw std::invalid_argument("Invalid point coordinates");
    }
    return CPoint(x, y);
}

uint32_t ShapeParser::ParseColor(const std::string &colorStr)
{
    try
    {
        return std::stoul(colorStr, nullptr, 16);
    } catch (...)
    {
        throw std::invalid_argument("Invalid color format: " + colorStr);
    }
}