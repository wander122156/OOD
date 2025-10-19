#include "Picture.h"

void Picture::AddShape(std::unique_ptr<IShape> shape)
{
    m_shapes.push_back(std::move(shape));
}

void Picture::RemoveShape(IShape *shape)
{
    m_shapes.erase(
        std::remove_if(m_shapes.begin(), m_shapes.end(),
                       [shape](const std::unique_ptr<IShape> &ptr)
                       {
                           return ptr.get() == shape;
                       }),
        m_shapes.end()
    );
}

const std::vector<std::unique_ptr<IShape> > &Picture::GetShapes() const
{
    return m_shapes;
}

size_t Picture::GetShapesCount() const
{
    return m_shapes.size();
}

// IShape* Picture::GetShapePtr(size_t index) const
// {
//     return (index < m_shapes.size())
//         ? m_shapes[index].get()
//         : nullptr;
// }
