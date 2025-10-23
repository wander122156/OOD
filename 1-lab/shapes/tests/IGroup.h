#pragma once
#include <memory>

#include "../include/IShape.h"

class IGroup: IShape
{
public:
    virtual ~IGroup() = default;

    virtual size_t GetShapesCount() const = 0;
    virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;

    virtual void InsertShape(std::shared_ptr<IShape>, size_t index) const = 0;
    virtual void RemoveShape(size_t index) const = 0;

};
