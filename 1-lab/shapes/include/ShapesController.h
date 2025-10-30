#pragma once
#include "Picture.h"
#include "PictureService.h"
#include "SFML/Graphics.hpp"

class ShapesController
{
public:
    ShapesController();

    void Run();

private:
    void LoadShapesFromFile(const std::string &filename);

    void PrintShapesInfo();

    //временно
    void Draw(sf::RenderWindow &window);

    void HandleMouseClick(float x, float y);

    void ProcessEvents(sf::RenderWindow &window);

    void HandleKeyPress(sf::Keyboard::Key key);

    Picture m_picture;
    SelectionManager m_selectionManager;

    struct StringConstants
    {
        static constexpr auto ERROR_OPEN_FILE = "ERROR: Cannot open file: ";
        static constexpr auto ERROR_CREATE_SHAPE = "Failed to create shape from: " ;

        static constexpr auto SHAPE_SHAPE = "Shape ";
        static constexpr auto SHAPE_AREA = "  Area: ";
        static constexpr auto SHAPE_PERIMETR = "  Perimeter: ";
    };
};
