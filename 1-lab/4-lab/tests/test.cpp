#include <gtest/gtest.h>
#include "CPoint.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "ShapeParser.h"
#include <cmath>

TEST(FindExtremesTest, FindsMinPerimeterCorrectly) {
    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(std::make_shared<CRectangle>(CPoint(0, 0), 10, 20,
                                                  0xFF0000, 0x00FF00)); // S 200
    shapes.push_back(std::make_shared<CCircle>(CPoint(0, 0), 5,
                                               0x0000FF, 0xFFFFFF)); // S 78.54
    shapes.push_back(std::make_shared<CTriangle>(CPoint(0, 0), CPoint(0, 3), CPoint(4, 0),
                                                 0x00FF00, 0x0000FF)); // S 6
    auto result = ShapeParser::FindMinPerimeter(shapes);
    //не null
    ASSERT_NE(result, nullptr);
    EXPECT_NEAR(result->GetPerimeter(), 12.0, 0.5);
}

TEST(FindExtremesTest, EmptyVector) {
    std::vector<std::shared_ptr<IShape>> empty_shapes;

    auto max_result = ShapeParser::FindMaxArea(empty_shapes);
    EXPECT_EQ(max_result, nullptr);

    auto min_result = ShapeParser::FindMinPerimeter(empty_shapes);
    EXPECT_EQ(min_result, nullptr);
}

TEST(FindExtremesTest, WorksWithEqualAreas) {
    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(std::make_shared<CRectangle>(CPoint(0, 0), 10, 20, 0xFF0000, 0x00FF00)); // S 200
    shapes.push_back(std::make_shared<CCircle>(CPoint(0, 0), 5, 0x0000FF, 0xFFFFFF)); // S 78.54
    shapes.push_back(std::make_shared<CTriangle>(CPoint(0, 0), CPoint(0, 3), CPoint(4, 0),0x00FF00, 0x0000FF)); // S 6
    // S прямоуг как у круга
    shapes.push_back(std::make_shared<CRectangle>(CPoint(0, 0), 78.54, 1, 0x000000, 0x000000));

    auto result = ShapeParser::FindMaxArea(shapes);
    ASSERT_NE(result, nullptr);
    EXPECT_NEAR(result->GetArea(), 200, 0.5);
}

TEST(FindExtremesTest, WorksWithSingleShape) {
    std::vector<std::shared_ptr<IShape>> single_shape = {
            std::make_shared<CCircle>(CPoint(0, 0), 10, 0xFF, 0xFF)
    };

    auto max_result = ShapeParser::FindMaxArea(single_shape);
    auto min_result = ShapeParser::FindMinPerimeter(single_shape);

    ASSERT_NE(max_result, nullptr);
    ASSERT_NE(min_result, nullptr);
    EXPECT_EQ(max_result, min_result);
}
// точка
TEST(CPointTest, CoordinatesAreSetCorrectly)
{
    CPoint point(3.5, 4.2);
    EXPECT_DOUBLE_EQ(point.GetX(), 3.5);
    EXPECT_DOUBLE_EQ(point.GetY(), 4.2);
}

TEST(CPointTest, DistanceCalculation)
{
    CPoint p1(1, 2);
    CPoint p2(4, 6);
    double dx = p2.GetX() - p1.GetX();
    double dy = p2.GetY() - p1.GetY();
    EXPECT_DOUBLE_EQ(sqrt(dx * dx + dy * dy), 5.0);
}

// вырожденность
TEST(DegenerateShapesTest, LineSegmentValidation)
{
    EXPECT_FALSE(ShapeParser::Validator::IsLineSegmentValid(
            CPoint(1, 1), CPoint(1, 1)));
}

TEST(DegenerateShapesTest, TriangleValidation)
{
    // все точки на одной прямой
    EXPECT_FALSE(ShapeParser::Validator::IsTriangleValid(
            CPoint(0, 0), CPoint(1, 1), CPoint(2, 2)));
    // две точки совпадают
    EXPECT_FALSE(ShapeParser::Validator::IsTriangleValid(
            CPoint(0, 0), CPoint(0, 0), CPoint(1, 1)));
    // три точки совпадают
    EXPECT_FALSE(ShapeParser::Validator::IsTriangleValid(
            CPoint(1, 1), CPoint(1, 1), CPoint(1, 1)));
}

TEST(DegenerateShapesTest, RectangleValidation)
{
    // нулевая ширина
    EXPECT_FALSE(ShapeParser::Validator::IsRectangleValid(0, 10));
    //нулевая высота
    EXPECT_FALSE(ShapeParser::Validator::IsRectangleValid(5, 0));
    // отрицательная ширина
    EXPECT_FALSE(ShapeParser::Validator::IsRectangleValid(-5, 10));
}

TEST(DegenerateShapesTest, CircleValidation)
{
    // нулевой радиус
    EXPECT_FALSE(ShapeParser::Validator::IsCircleValid(0.0));
    //отрицательный радиус
    EXPECT_FALSE(ShapeParser::Validator::IsCircleValid(-2.5));
}
// информация
TEST(LineSegmentTest, ToString)
{
    CLineSegment line(CPoint(1, 2), CPoint(4, 6), 0xFF0000);
    std::string expected = "LineSegment: Start(1, 2), End(4, 6), OutlineColor=#ff0000";
    EXPECT_EQ(line.ToString(), expected);
}

TEST(TriangleTest, ToString)
{
    CTriangle tri(CPoint(0, 0), CPoint(0, 3), CPoint(4, 0), 0x00FF00, 0x0000FF);
    std::string expected = "Triangle: Vertex1(0, 0), Vertex2(0, 3), Vertex3(4, 0), OutlineColor=#00ff00, FillColor=#0000ff";
    EXPECT_EQ(tri.ToString(), expected);
}

TEST(RectangleTest, ToString)
{
    CRectangle rect(CPoint(1, 1), 3, 4, 0x112233, 0xAABBCC);
    std::string expected = "Rectangle: top left(1, 1), width= 3, height= 4, Outline color: #112233Fill color: #aabbcc";
    EXPECT_EQ(rect.ToString(), expected);
}

TEST(CircleTest, ToString)
{
    CCircle circle(CPoint(0, 0), 5, 0x123456, 0xABCDEF);
    std::string expected = "Circle: center(0, 0), Radius=5, Outline color: #123456, Fill color: #abcdef";
    EXPECT_EQ(circle.ToString(), expected);
}
// остальное
TEST(TriangleTest, TriangleAreaCalculation)
{
    CPoint v1(0, 0), v2(0, 3), v3(4, 0);
    CTriangle triangle(v1, v2, v3, 0xFF0000, 0x00FF00);
    EXPECT_DOUBLE_EQ(triangle.GetArea(), 6.0);
}

TEST(TriangleTest, WrongTriangle)
{
    CPoint v1(0, 0), v2(5, 0), v3(10, 0);
    CTriangle triangle(v1, v2, v3, 0xFF0000, 0x00FF00);
    EXPECT_DOUBLE_EQ(triangle.GetArea(), 0.0);
}

TEST(TriangleTest, TrianglePerimeterCalculation)
{
    CTriangle triangle(CPoint(0, 0), CPoint(0, 3), CPoint(4, 0), 0xFF0000, 0x00FF00);
    EXPECT_DOUBLE_EQ(triangle.GetPerimeter(), 12.0);
}

TEST(TriangleTest, TriangleGetFill)
{
    CTriangle triangle(CPoint(0, 0), CPoint(0, 3), CPoint(4, 0), 0xFF0000, 0x00FF00);
    EXPECT_EQ(triangle.GetFillColor(), 65280);
}

TEST(RectangleTest, AreaCalculation)
{
    CRectangle rect(CPoint(0, 0), 5, 10, 0x000000, 0xFFFFFF);
    EXPECT_DOUBLE_EQ(rect.GetArea(), 50.0);
}

TEST(RectangleTest, RectanglePerimeter)
{
    CRectangle rect(CPoint(0, 0), 5, 10, 0x000000, 0xFFFFFF);
    EXPECT_DOUBLE_EQ(rect.GetPerimeter(), 30.0);
}

TEST(CircleTest, AreaCalculation)
{
    CCircle circle(CPoint(0, 0), 5, 0x123456, 0xABCDEF);
    EXPECT_DOUBLE_EQ(circle.GetArea(), M_PI * 25);
}

TEST(CircleTest, PerimeterCalculation)
{
    CCircle circle(CPoint(0, 0), 5, 0x123456, 0xABCDEF);
    EXPECT_DOUBLE_EQ(circle.GetPerimeter(), M_PI * 10);
}

TEST(CircleTest, CircleToString)
{
    CCircle circle(CPoint(0, 0), 5, 0x123456, 0xABCDEF);
    std::string expected = "Circle: center(0, 0), Radius=5, Outline color: #123456, Fill color: #abcdef";
    EXPECT_EQ(circle.ToString(), expected);
}

TEST(LineSegmentTest, LengthCalculation)
{
    CLineSegment line(CPoint(0, 0), CPoint(3, 4), 0xFF0000);
    EXPECT_DOUBLE_EQ(line.GetPerimeter(), 5.0);
}

TEST(LineSegmentTest, ZeroLength)
{
    CLineSegment line(CPoint(1, 1), CPoint(1, 1), 0x00FF00);
    EXPECT_DOUBLE_EQ(line.GetPerimeter(), 0.0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}