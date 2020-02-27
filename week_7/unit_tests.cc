#include "gtest/gtest.h"
#include "robot.h"

#include "elma/elma.h"

#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace elma;

namespace {

    TEST(Robot, Easy) {
        Robot robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 20_ms)
        .init()
        .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Evade");

        m.emit(Event("battery low"));
        EXPECT_EQ(robot.current().name(), "Find Recharge");

        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Find Recharge");


        m.emit(Event("found recharge station"));
        EXPECT_EQ(robot.current().name(), "Recharge");

        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Wander");

        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");

        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");

        m.emit(Event("reset"));
        EXPECT_EQ(robot.current().name(), "Make Noise");

        m.emit(Event("reset"));
        EXPECT_EQ(robot.current().name(), "Wander");
    }

}