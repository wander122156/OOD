// Group.h
#pragma once
#include "IGroup.h"
#include <vector>
#include <memory>

class Group : public IGroup
{
public:
    Group() = default;

    // IGroup
    size_t GetShapesCount() const override;
    IShape* GetShapeAtIndex(size_t index) const override;
    void InsertShape(std::unique_ptr<IShape> shape, size_t index = std::numeric_limits<size_t>::max()) override;
    void RemoveShape(size_t index) override;

    // IShape
    void Draw(sf::RenderWindow& window) const override;
    void Move(CPoint& delta) override;
    RectD GetFrame() const override;
    float GetArea() const override;
    float GetPerimeter() const override;

    bool ContainsPoint(float x, float y) const;

private:
    std::vector<std::unique_ptr<IShape>> m_shapes;

    RectD CalculateFrame() const;
};