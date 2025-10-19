#include "../include/SelectionManager.h"

void SelectionManager::SelectShape(IShape *shape)
{
    m_selectedShape = shape;
}

void SelectionManager::DeselectShape(IShape *shape)
{
    if (m_selectedShape == shape)
    {
        m_selectedShape = nullptr;
    }
}

void SelectionManager::ClearSelection()
{
    m_selectedShape = nullptr;
}

IShape *SelectionManager::GetSelectedShape() const
{
    return m_selectedShape;
}

bool SelectionManager::HasSelection() const
{
    return m_selectedShape != nullptr;
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

void SelectionManager::DrawSelection(sf::RenderWindow &window) const
{
    if (HasSelection())
    {
        RectD frame = m_selectedShape->GetFrame();

        sf::RectangleShape selectionFrame;
        selectionFrame.setSize(sf::Vector2f(static_cast<float>(frame.width),
                                            static_cast<float>(frame.height)));
        selectionFrame.setPosition(static_cast<float>(frame.left),
                                   static_cast<float>(frame.top));
        selectionFrame.setFillColor(sf::Color::Transparent);
        selectionFrame.setOutlineColor(sf::Color::Magenta );
        selectionFrame.setOutlineThickness(2.0f);

        window.draw(selectionFrame);
    }
}
