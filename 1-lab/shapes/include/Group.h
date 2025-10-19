#pragma once
#include "IGroup.h"

class Group : public IGroup
{
public:


    size_t GetShapesCount() const override
    {
        return m_shapes.size();
    }
    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override
    {
        return std::shared_ptr<IShape>((index < m_shapes.size())
                                           ? m_shapes[index]
                                           : nullptr);
    }
    void InsertShape(std::shared_ptr<IShape> shape, size_t index) const override
    {
        if (index <= m_shapes.size())
        {
            m_shapes.insert(m_shapes.begin() + index, shape);
        }
    }
    void RemoveShape(size_t index) const
    {
        if (index < m_shapes.size())
        {
            m_shapes.erase(m_shapes.begin() + index);
        }
    }

private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
};
