#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, add_basic) {
        Complex a = (Complex) { 2, -3 },
                 b = (Complex) { 4, 5 };
        EXPECT_EQ(add(a,b).real,6);
        EXPECT_EQ(add(a,b).im,2);
    }
    
    // TEST(Complex, add_null) {
    //     Complex a = (Complex) { 0, 0},
    //              b = (Complex) { 4, 5 };
    //     EXPECT_EQ(add(a,b).real,6);
    //     EXPECT_EQ(add(a,b).im,2);
    // }

    TEST(Complex, multiply_basic) {
        Complex a = (Complex) { 1, 1 },
                 b = (Complex) { 1, 1 };
        EXPECT_EQ(multiply(a,b).real,0);
        EXPECT_EQ(multiply(a,b).im,2);
    }

    TEST(Complex, multiply_zero) {
        Complex a = (Complex) { 0, 0 },
                 b = (Complex) { 1, 1 };
        EXPECT_EQ(multiply(a,b).real,0);
        EXPECT_EQ(multiply(a,b).im,0);
    }

    TEST(Complex, negate_basic) {
        Complex a = (Complex) { 1, 1 };
        EXPECT_EQ(negate(a).real,-1);
        EXPECT_EQ(negate(a).im,-1);
    }

    TEST(Complex, negate_zero) {
        Complex a = (Complex) { 0, 0 };
        EXPECT_EQ(negate(a).real,0);
        EXPECT_EQ(negate(a).im,0);
    }

    TEST(Complex, magnitude) {
        Complex a = (Complex) { 3, 4 };
        EXPECT_EQ(magnitude(a),5);
    }
        
    TEST(Complex, magnitude_real_zero) {
        Complex a = (Complex) { 0, 4 };
        EXPECT_EQ(magnitude(a),4);
    }

    TEST(Complex, magnitude_im_zero) {
        Complex a = (Complex) { 4, 0 };
        EXPECT_EQ(magnitude(a),4);
    }
}