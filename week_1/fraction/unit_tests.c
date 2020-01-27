#include "fraction.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, Basics) {
        Fraction a = (Fraction) { 2, 3 },
                 b = (Fraction) { 4, 5 };
        EXPECT_EQ(add(a,b).num,22);
        EXPECT_EQ(add(a,b).den,15);
        EXPECT_EQ(multiply(a,b).num,8);
        EXPECT_EQ(multiply(a,b).den,15);
    }

    TEST(Fractions, basic_example) {
        Fraction a = (Fraction) { 21, 33 };
        EXPECT_EQ(reduce(a).num,7);
        EXPECT_EQ(reduce(a).den,11);
    }

    TEST(Fractions, zero_num_and_den) {
        Fraction a = (Fraction) { 0, 0};
        EXPECT_EQ(reduce(a).num, 0);
        EXPECT_EQ(reduce(a).den, 0);
    }

    TEST(Fractions, zero_den) {
        Fraction a = (Fraction) { 1, 0};
        EXPECT_EQ(reduce(a).num, 1);
        EXPECT_EQ(reduce(a).den, 0);
    }

    TEST(Fractions, one_den) {
        Fraction a = (Fraction) { 3, 1};
        EXPECT_EQ(reduce(a).num, 3);
        EXPECT_EQ(reduce(a).den, 1);
    }

    TEST(Fractions, same_num) {
        Fraction a = (Fraction) { 11, 11};
        EXPECT_EQ(reduce(a).num, 1);
        EXPECT_EQ(reduce(a).den, 1);
    }
}
