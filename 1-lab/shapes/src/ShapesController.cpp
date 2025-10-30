#include "ShapesController.h"

#include <fstream>
#include <sstream>

#include "ConvexAdapter.h"
#include "iostream"
#include "ShapeFactory.h"

ShapesController::ShapesController()
{
    LoadShapesFromFile("shapes.txt");
}

void ShapesController::LoadShapesFromFile(const std::string &filename)
{
    std::vector<std::unique_ptr<IShape> > shapes;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << StringConstants::ERROR_OPEN_FILE << filename << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        auto shape = ShapeFactory::CreateShape(line);
        if (shape)
        {
            m_picture.AddShape(std::move(shape));
        } else
        {
            std::cout << StringConstants::ERROR_CREATE_SHAPE << line << std::endl;
        }
    }

    file.close();

    PrintShapesInfo();
}

void ShapesController::PrintShapesInfo()
{
    auto &shapes = m_picture.GetShapes();

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout << StringConstants::SHAPE_SHAPE << (i + 1) << std::endl;
        std::cout << StringConstants::SHAPE_AREA << shapes[i]->GetArea() << std::endl;
        std::cout << StringConstants::SHAPE_PERIMETR << shapes[i]->GetPerimeter() << std::endl;
    }
}

void ShapesController::Run()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shape Editor");

    while (window.isOpen())
    {
        ProcessEvents(window);
        Draw(window);
    }
}

void ShapesController::Draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);

    auto &shapes = m_picture.GetShapes();
    for (auto &shape: shapes)
    {
        m_picture.DrawShape( window, shape.get());
    }

    // выделение
    m_selectionManager.DrawSelection(window);

    window.display();
}

void ShapesController::ProcessEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    HandleMouseClick(static_cast<float>(event.mouseButton.x),
                                     static_cast<float>(event.mouseButton.y));
                }
                break;

            case sf::Event::KeyPressed:
                HandleKeyPress(event.key.code);
                break;

            default:
                break;
        }
    }
}

void ShapesController::HandleMouseClick(float x, float y)
{
    auto &shapes = m_picture.GetShapes();
    IShape *clickedShape = m_selectionManager.GetShapeAtPoint(shapes, x, y);

    //временно
    if (clickedShape)
    {
        m_selectionManager.SelectShape(clickedShape);
        std::cout << "Shape selected at (" << x << ", " << y << ")" << std::endl;
    } else
    {
        m_selectionManager.ClearSelection();
        std::cout << "Selection cleared" << std::endl;
    }
}

void ShapesController::HandleKeyPress(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Delete:
            if (m_selectionManager.HasSelection())
            {
                IShape *selected = m_selectionManager.GetSelectedShape();
                m_picture.RemoveShape(selected);
                m_selectionManager.ClearSelection();
            }
            break;

        case sf::Keyboard::Escape:
            m_selectionManager.ClearSelection();
            break;

        default:
            break;
    }
}
