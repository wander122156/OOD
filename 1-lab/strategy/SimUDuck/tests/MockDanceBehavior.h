#ifndef MOCKDANCEBEHAVIOR_H
#define MOCKDANCEBEHAVIOR_H


#include "../lib/Duck/Dance/IDanceBehavior.h"
#include "../googletest/googlemock/include/gmock/gmock.h"
#include "../googletest/googletest/include/gtest/gtest.h"

class MockDanceBehavior : public IDanceBehavior {
public:
    MOCK_METHOD(void, Dance, (), (override));
};

#endif //MOCKDANCEBEHAVIOR_H
