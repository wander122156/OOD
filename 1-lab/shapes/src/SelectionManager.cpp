#include "../include/SelectionManager.h"

void SelectionManager::SelectShape(IShape* shape)
{
    m_selectedShapes.clear();
    if (shape)
    {
        m_selectedShapes.push_back(shape);
    }
}

void SelectionManager::SelectShapes(const std::vector<IShape*>& shapes)
{
    m_selectedShapes = shapes;
    // Убираем дубликаты
    auto last = std::unique(m_selectedShapes.begin(), m_selectedShapes.end());
    m_selectedShapes.erase(last, m_selectedShapes.end());
}

void SelectionManager::AddToSelection(IShape* shape)
{
    if (shape && std::find(m_selectedShapes.begin(), m_selectedShapes.end(), shape) == m_selectedShapes.end())
    {
        m_selectedShapes.push_back(shape);
    }
}

void SelectionManager::DeselectShape(IShape* shape)
{
    m_selectedShapes.erase(
        std::remove(m_selectedShapes.begin(), m_selectedShapes.end(), shape),
        m_selectedShapes.end()
    );
}

void SelectionManager::ClearSelection()
{
    m_selectedShapes.clear();
}

IShape* SelectionManager::GetSelectedShape() const
{
    return m_selectedShapes.empty() ? nullptr : m_selectedShapes[0];
}

const std::vector<IShape*>& SelectionManager::GetSelectedShapes() const
{
    return m_selectedShapes;
}

bool SelectionManager::HasSelection() const
{
    return !m_selectedShapes.empty();
}

bool SelectionManager::HasMultipleSelection() const
{
    return m_selectedShapes.size() > 1;
}

IShape *SelectionManager::GetShapeAtPoint(const std::vector<std::unique_ptr<IShape> > &shapes, float x, float y)
{
    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it)
    {
        RectD frame = (*it)->GetFrame();
        if (frame.ContainsPoint(x, y))
        {
            return it->get();
        }
    }
    return nullptr;
}

void SelectionManager::DrawSelection(sf::RenderWindow& window) const
{
    for (IShape* shape : m_selectedShapes)
    {
        RectD frame = shape->GetFrame();

        sf::RectangleShape selectionFrame;
        selectionFrame.setSize(sf::Vector2f(static_cast<float>(frame.width),
                                            static_cast<float>(frame.height)));
        selectionFrame.setPosition(static_cast<float>(frame.left),
                                   static_cast<float>(frame.top));
        selectionFrame.setFillColor(sf::Color::Transparent);
        selectionFrame.setOutlineColor(sf::Color::Magenta);
        selectionFrame.setOutlineThickness(2.0f);

        window.draw(selectionFrame);
    }
}

