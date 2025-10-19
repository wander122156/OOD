#pragma once
#include "IShape.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>

class SelectionManager
{
public:
    void SelectShape(IShape *shape);
    void DeselectShape(IShape *shape);
    void ClearSelection();

    IShape *GetSelectedShape() const;

    bool HasSelection() const;

    // Проверка попадания точки в фигуру
    IShape *GetShapeAtPoint(const std::vector<std::unique_ptr<IShape> > &shapes, float x, float y);

    // Отрисовка выделения
    void DrawSelection(sf::RenderWindow &window) const;

private:
    IShape *m_selectedShape = nullptr;
};
