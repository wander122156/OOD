#ifndef OOD_3CURSE__DANCEWALTZ_H
#define OOD_3CURSE__DANCEWALTZ_H

#include <iostream>
#include "IDanceBehavior.h"

class DanceWaltz : public IDanceBehavior
{
public:
    void Dance() override
    {
        std::cout << "I'm dancing Waltz!!" << std::endl;
    }
};
#endif
