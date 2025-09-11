#include "ShapeParser.h"
#include <iostream>

int main() {
    try {
        auto shapes = ShapeParser::ParseFromInput();

        if (shapes.empty()) {
            std::cout << "No shapes were entered." << std::endl;
            return 0;
        }

        auto maxAreaShape = ShapeParser::FindMaxArea(shapes);
        auto minPerimeterShape = ShapeParser::FindMinPerimeter(shapes);

        std::cout << "Shape with the maximum area:" << std::endl;
        ShapeParser::PrintShapeInfo(maxAreaShape);

        std::cout << "\nShape with the minimum perimeter:" << std::endl;
        ShapeParser::PrintShapeInfo(minPerimeterShape);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}