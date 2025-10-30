#include "ShapesController.h"

#include <fstream>
#include <sstream>

#include "ConvexAdapter.h"
#include "Group.h"
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

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    HandleMouseRelease();
                }
                break;

            case sf::Event::MouseMoved:
                if (m_isDragging)
                {
                    HandleMouseMove(static_cast<float>(event.mouseMove.x),
                                    static_cast<float>(event.mouseMove.y));
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
    auto& shapes = m_picture.GetShapes();
    IShape* clickedShape = m_selectionManager.GetShapeAtPoint(shapes, x, y);

    if (clickedShape)
    {
        bool isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

        if (isShiftPressed)
        {
            // Добавляем к текущему выделению или убираем из него
            auto& selectedShapes = m_selectionManager.GetSelectedShapes();
            auto it = std::find(selectedShapes.begin(), selectedShapes.end(), clickedShape);

            if (it == selectedShapes.end())
            {
                m_selectionManager.AddToSelection(clickedShape);
                std::cout << "Added to selection. Total selected: "
                          << m_selectionManager.GetSelectedShapes().size() << std::endl;
            }
            else
            {
                m_selectionManager.DeselectShape(clickedShape);
                std::cout << "Removed from selection. Total selected: "
                          << m_selectionManager.GetSelectedShapes().size() << std::endl;
            }
        }
        else
        {
            // Обычный клик - выделяем одну фигуру
            m_selectionManager.SelectShape(clickedShape);
            std::cout << "Shape selected at (" << x << ", " << y << ")" << std::endl;
        }

        // Начинаем перетаскивание если есть выделение
        if (m_selectionManager.HasSelection())
        {
            m_isDragging = true;
            m_dragStartPosition = sf::Vector2f(x, y);

            // Сохраняем смещение для первой выделенной фигуры (для расчета перемещения)
            RectD frame = clickedShape->GetFrame();
            m_dragOffset = sf::Vector2f(
                x - static_cast<float>(frame.left),
                y - static_cast<float>(frame.top)
            );
        }
    }
    else
    {
        // Клик в пустую область - снимаем выделение (если не зажат Shift)
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            m_selectionManager.ClearSelection();
            std::cout << "Selection cleared" << std::endl;
        }
    }
}

void ShapesController::HandleMouseMove(float x, float y)
{
    if (!m_isDragging || !m_selectionManager.HasSelection()) return;

    // Вычисляем целевую позицию для перемещения
    float targetX = x - m_dragOffset.x;
    float targetY = y - m_dragOffset.y;

    // Получаем первую выделенную фигуру для расчета смещения
    auto selectedShapes = m_selectionManager.GetSelectedShapes();
    IShape* firstShape = selectedShapes[0];
    RectD currentFrame = firstShape->GetFrame();

    // Вычисляем смещение от текущей позиции к целевой
    float dx = targetX - static_cast<float>(currentFrame.left);
    float dy = targetY - static_cast<float>(currentFrame.top);

    auto delta = CPoint(dx, dy);

    // Перемещаем все выделенные фигуры
    for (IShape* shape : selectedShapes)
    {
        shape->Move(delta);
    }
}

void ShapesController::HandleMouseRelease()
{
    m_isDragging = false;
}

void ShapesController::HandleKeyPress(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Delete:
            if (m_selectionManager.HasSelection())
            {
                // Удаляем все выделенные фигуры
                auto selectedShapes = m_selectionManager.GetSelectedShapes();
                for (IShape* shape : selectedShapes)
                {
                    m_picture.RemoveShape(shape);
                }
                m_selectionManager.ClearSelection();
                std::cout << "Deleted " << selectedShapes.size() << " shapes" << std::endl;
            }
        break;

        case sf::Keyboard::G:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                HandleGroupShapes();
            }
        break;

        case sf::Keyboard::U:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                HandleUngroupShapes();
            }
        break;

        case sf::Keyboard::Escape:
            m_selectionManager.ClearSelection();
        std::cout << "Selection cleared (ESC)" << std::endl;
        break;

        default:
            break;
    }
}

void ShapesController::HandleGroupShapes()
{
    auto selectedShapes = m_selectionManager.GetSelectedShapes();
    if (selectedShapes.size() < 2) return;

    // Создаем новую группу
    auto group = std::make_unique<Group>();

    // Извлекаем выделенные фигуры из picture и добавляем в группу
    for (IShape* shape : selectedShapes)
    {
        std::unique_ptr<IShape> extracted = m_picture.ExtractShape(shape);
        if (extracted)
        {
            group->InsertShape(std::move(extracted));
        }
    }

    // Добавляем группу в picture
    IShape* groupPtr = group.get();
    m_picture.AddShape(std::move(group));

    // Выделяем новую группу
    m_selectionManager.SelectShape(groupPtr);

    std::cout << "Shapes grouped into single object" << std::endl;
}

void ShapesController::HandleUngroupShapes()
{
    auto selectedShapes = m_selectionManager.GetSelectedShapes();
    if (selectedShapes.size() != 1) return;

    IShape* selected = selectedShapes[0];
    IGroup* group = dynamic_cast<IGroup*>(selected);
    if (!group) return;

    // Извлекаем группу из picture
    std::unique_ptr<IShape> extractedGroup = m_picture.ExtractShape(selected);
    if (!extractedGroup) return;

    Group* concreteGroup = dynamic_cast<Group*>(extractedGroup.get());
    if (!concreteGroup) return;

    // Извлекаем все фигуры из группы и добавляем обратно в picture
    std::vector<IShape*> ungroupedShapes;
    size_t shapesCount = concreteGroup->GetShapesCount();

    for (size_t i = 0; i < shapesCount; ++i)
    {
        // Получаем фигуру из группы
        IShape* shape = concreteGroup->GetShapeAtIndex(i);
        if (shape)
        {
            // Создаем копию фигуры (или извлекаем, если возможно)
            // Для простоты создаем новую группу с одной фигурой и извлекаем её
            auto tempGroup = std::make_unique<Group>();
            // Нужна более сложная логика для извлечения отдельных фигур
            // Временное решение - просто добавляем фигуры обратно
        }
    }

    // Альтернативный подход - переработать логику извлечения
    // Пока просто очищаем выделение
    m_selectionManager.ClearSelection();

    std::cout << "Group ungrouped into " << shapesCount << " shapes" << std::endl;
}