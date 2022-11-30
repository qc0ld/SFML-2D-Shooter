#include "test.h"
#include "map.h"

TEST(Unit, constructor){
    Unit unit;
    EXPECT_EQ(unit.dead, 0);
    EXPECT_EQ(unit.hp, 100);
    EXPECT_EQ(unit.position.x, 0);
    EXPECT_EQ(unit.position.y, 0);
    EXPECT_DOUBLE_EQ(unit.speed, 0.2);
}

TEST(Unit, moving){
    Unit unit;
    unit.set_position(40,50);
    EXPECT_EQ(unit.position.x, 40);
    EXPECT_EQ(unit.position.y, 50);
    unit.move_x(30);
    unit.move_y(50);
    EXPECT_DOUBLE_EQ(unit.position.x, 70);
    EXPECT_DOUBLE_EQ(unit.position.y, 100);
    unit.move_x(-23.123);
    unit.move_y(-40.31);
    EXPECT_DOUBLE_EQ(unit.position.x, 46.876998901367188);
    EXPECT_DOUBLE_EQ(unit.position.y, 59.689998626708984);
}

TEST(Unit, get_damage){
    Unit unit;
    unit.get_damage(33);
    EXPECT_EQ(unit.hp, 67);
}

int gtest_main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}