// #include "../googletest/googlemock/include/gmock/gmock.h"
// #include "../googletest/googletest/include/gtest/gtest.h"

#include "../lib/Duck/Duck.h"
#include "MockFlyBehavior.h"
#include "MockQuackBehavior.h"
#include "MockDanceBehavior.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;

TEST(DuckTest, FlyCallsFlyBehavior) {
    auto mockFly = std::make_unique<MockFlyBehavior>();
    auto mockQuack = std::make_unique<MockQuackBehavior>();
    auto mockDance = std::make_unique<MockDanceBehavior>();

    // Ожидаем вызов Fly() один раз
    EXPECT_CALL(*mockFly, Fly()).Times(1);

    Duck duck(std::move(mockFly), std::move(mockQuack), std::move(mockDance));
    duck.Fly();
}

TEST(DuckTest, QuackCallsQuackBehavior) {
    auto mockFly = std::make_unique<MockFlyBehavior>();
    auto mockQuack = std::make_unique<MockQuackBehavior>();
    auto mockDance = std::make_unique<MockDanceBehavior>();

    EXPECT_CALL(*mockQuack, Quack()).Times(1);

    Duck duck(std::move(mockFly), std::move(mockQuack), std::move(mockDance));
    duck.Quack();
}

TEST(DuckTest, CanQuackReturnsFalseForMuteQuack) {
    auto mockFly = std::make_unique<MockFlyBehavior>();
    auto muteQuack = std::make_unique<MuteQuackBehavior>(); // Реальная немая стратегия
    auto mockDance = std::make_unique<MockDanceBehavior>();

    Duck duck(std::move(mockFly), std::move(muteQuack), std::move(mockDance));
    EXPECT_FALSE(duck.CanQuack());
}

TEST(DuckTest, CanQuackReturnsTrueForNonMuteQuack) {
    auto mockFly = std::make_unique<MockFlyBehavior>();
    auto mockQuack = std::make_unique<MockQuackBehavior>(); // Не немая стратегия
    auto mockDance = std::make_unique<MockDanceBehavior>();

    Duck duck(std::move(mockFly), std::move(mockQuack), std::move(mockDance));
    EXPECT_TRUE(duck.CanQuack());
}

TEST(DuckTest, FlyWithEvenCountCallsQuack) {
    auto mockFly = std::make_unique<MockFlyBehavior>();
    auto mockQuack = std::make_unique<MockQuackBehavior>();
    auto mockDance = std::make_unique<MockDanceBehavior>();

    // Настраиваем mock чтобы GetFlightCount возвращал 2
    EXPECT_CALL(*mockFly, Fly()).Times(1);
    EXPECT_CALL(*mockFly, GetFlightCount()).WillOnce(Return(2));
    EXPECT_CALL(*mockQuack, Quack()).Times(1); // Ожидаем вызов Quack()

    Duck duck(std::move(mockFly), std::move(mockQuack), std::move(mockDance));
    duck.Fly();
}