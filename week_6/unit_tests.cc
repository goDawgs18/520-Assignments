#include "stopwatch.h"
#include "gtest/gtest.h"

namespace {

    void waste_time() {
        std::this_thread::sleep_for(10ms);
    }

    TEST(Stopwatch,NiceUsage) {
        Stopwatch s;
        s.start();
        waste_time();
        s.stop();
        EXPECT_EQ(s.get_seconds(), s.get_seconds());
        EXPECT_EQ(s.get_seconds(), .01);
        EXPECT_EQ(s.get_milliseconds(), 10);
        EXPECT_EQ(s.get_nanoseconds(), 10000000);
    }
}