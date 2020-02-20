#include "gtest/gtest.h"
#include "stopwatch.h"
#include "random_process.h"
#include "integrator.h"
#include "derivative.h"


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

    TEST(RandomProcess,NiceUsage) {
        elma::Manager m;

        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(r, 1ms)
        .schedule(f, 1ms)
        .add_channel(link)
        .init()
        .run(1000ms);

        std::cout << f.value() << "\n";
    }
}