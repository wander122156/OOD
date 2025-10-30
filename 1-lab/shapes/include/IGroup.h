#pragma once
#include <limits>

#include "IShape.h"
#include <memory>

class IGroup : public IShape
{
public:
    virtual ~IGroup() = default;

    // Получение количества фигур в группе
    virtual size_t GetShapesCount() const = 0;

    // Получение фигуры по индексу
    virtual IShape* GetShapeAtIndex(size_t index) const = 0;

    // Вставка фигуры в группу
    virtual void InsertShape(std::unique_ptr<IShape> shape, size_t index = std::numeric_limits<size_t>::max()) = 0;

    // Удаление фигуры из группы
    virtual void RemoveShape(size_t index) = 0;
};