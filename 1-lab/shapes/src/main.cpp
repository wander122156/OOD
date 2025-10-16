#include <sstream>
#include <SFML/Graphics.hpp>
#include "IShape.h"
#include "ShapeController.h"
// вынести цикл в контроллер draw

// объясвить controller
// controller.run

int main()
{
    auto shapes = ShapeController::ReadShapesFromFile("shapes.txt");

    ShapeController::PrintShapesInfo(shapes);

    sf::RenderWindow window(sf::VideoMode(1000, 800),"Shapes Visualization");

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

    return 0;
}
