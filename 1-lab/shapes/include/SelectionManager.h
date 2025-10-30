#pragma once
#include "IShape.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>

class SelectionManager
{
public:
    void SelectShape(IShape *shape);
    void SelectShapes(const std::vector<IShape*>& shapes);
    void AddToSelection(IShape* shape);
    void DeselectShape(IShape *shape);
    void ClearSelection();

    IShape *GetSelectedShape() const;

    const std::vector<IShape*>& GetSelectedShapes() const;
    bool HasSelection() const;
    bool HasMultipleSelection() const;

    IShape *GetShapeAtPoint(const std::vector<std::unique_ptr<IShape> > &shapes, float x, float y);

    void DrawSelection(sf::RenderWindow &window) const;

private:
    std::vector<IShape*> m_selectedShapes;
};
