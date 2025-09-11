#ifndef OOD_3CURSE__IDANCEBEHAVIOR_H
#define OOD_3CURSE__IDANCEBEHAVIOR_H

struct IDanceBehavior
{
    virtual ~IDanceBehavior(){};
    virtual void Dance() = 0;
};

#endif
