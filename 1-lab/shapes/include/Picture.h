#pragma once
#include "vector"
#include <memory>
#include "IShape.h"

class Picture
{
public:
    void AddShape(std::unique_ptr<IShape> shape);
    void RemoveShape(IShape *shape);

    const std::vector<std::unique_ptr<IShape> > &GetShapes() const;

    size_t GetShapesCount() const;

    void DrawShape(sf::RenderWindow &window, IShape *shape);

private:
    std::vector<std::unique_ptr<IShape> > m_shapes;
};
