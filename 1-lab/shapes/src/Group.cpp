// Group.cpp
#include "Group.h"
#include <algorithm>
#include <limits>

size_t Group::GetShapesCount() const
{
    return m_shapes.size();
}

IShape* Group::GetShapeAtIndex(size_t index) const
{
    if (index >= m_shapes.size())
    {
        return nullptr;
    }
    return m_shapes[index].get();
}

void Group::InsertShape(std::unique_ptr<IShape> shape, size_t index )
{
    if (index == std::numeric_limits<size_t>::max() || index >= m_shapes.size())
    {
        m_shapes.push_back(std::move(shape));
    }
    else
    {
        // Вставляем по указанному индексу
        m_shapes.insert(m_shapes.begin() + index, std::move(shape));
    }
}

void Group::RemoveShape(size_t index)
{
    if (index < m_shapes.size())
    {
        m_shapes.erase(m_shapes.begin() + index);
    }
}

void Group::Draw(sf::RenderWindow& window) const
{
    for (const auto& shape : m_shapes)
    {
        shape->Draw(window);
    }
}

void Group::Move(CPoint& delta)
{
    for (auto& shape : m_shapes)
    {
        shape->Move(delta);
    }
}

RectD Group::GetFrame() const
{
    return CalculateFrame();
}

float Group::GetArea() const
{
    float totalArea = 0.0f;
    for (const auto& shape : m_shapes)
    {
        totalArea += shape->GetArea();
    }
    return totalArea;
}

float Group::GetPerimeter() const
{
    float totalPerimeter = 0.0f;
    for (const auto& shape : m_shapes)
    {
        totalPerimeter += shape->GetPerimeter();
    }
    return totalPerimeter;
}

bool Group::ContainsPoint(float x, float y) const
{
    for (const auto& shape : m_shapes)
    {
        RectD frame = shape->GetFrame();
        if (frame.ContainsPoint(x, y))
        {
            return true;
        }
    }
    return false;
}

RectD Group::CalculateFrame() const
{
    if (m_shapes.empty())
    {
        return {0, 0, 0, 0};
    }

    // Находим общий bounding box для всех фигур в группе
    RectD firstFrame = m_shapes[0]->GetFrame();
    float minX = firstFrame.left;
    float minY = firstFrame.top;
    float maxX = firstFrame.left + firstFrame.width;
    float maxY = firstFrame.top + firstFrame.height;

    for (size_t i = 1; i < m_shapes.size(); ++i)
    {
        RectD shapeFrame = m_shapes[i]->GetFrame();
        minX = std::min(minX, static_cast<float>(shapeFrame.left));
        minY = std::min(minY, static_cast<float>(shapeFrame.top));
        maxX = std::max(maxX, static_cast<float>(shapeFrame.left + shapeFrame.width));
        maxY = std::max(maxY, static_cast<float>(shapeFrame.top + shapeFrame.height));
    }

    return {minX, minY, maxX - minX, maxY - minY};
}