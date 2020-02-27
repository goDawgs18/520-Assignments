#include "gtest/gtest.h"
#include "robot.h"

#include "elma/elma.h"

#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace elma;

#include <json/json.h>

using nlohmann::json;

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



    TEST(BetterStateMachine, Easy) {

        BetterStateMachine bsm("machinist");

        robot_states::Wander wander;
        robot_states::FindRecharge find_recharge;
        robot_states::Recharge recharge;
        robot_states::MakeNoise make_noise;
        robot_states::Evade evade; 

        bsm.set_initial(wander)
            .add_transition("battery low", make_noise, find_recharge)
            .add_transition("intruder detected", find_recharge, make_noise)
            .add_transition("found recharge station", find_recharge, recharge)
            .add_transition("battery full", recharge, find_recharge)
            .add_transition("reset", make_noise, recharge);

        Manager m;
        // m.schedule(bsm, 10_ms)
        // .init()
        // .start();

        // m.emit(Event("intruder detected"));
        auto jVals = bsm.to_json();
        EXPECT_EQ(jVals["name"], "machinist");
        EXPECT_EQ(jVals["transitions"][0]["from"], "Make Noise");
        EXPECT_EQ(jVals["states"][0], "Wander");
        std::cout << bsm.to_json().dump();
        

    }

}