#ifndef OOD_3CURSE__DANCEMINUET_H
#define OOD_3CURSE__DANCEMINUET_H

#include <iostream>
#include "IDanceBehavior.h"

class DanceMinuet : public IDanceBehavior
{
public:
    void Dance() override
    {
        std::cout << "I'm dancing Minuet!!" << std::endl;
    }
};

#endif