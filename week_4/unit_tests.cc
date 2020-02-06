#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "complex.h"
#include "point.h"
#include "gtest/gtest.h"

namespace {

//**********************************************************************//
//           These are  tests for the TypedArray data type              // 
//**********************************************************************//

    TEST(TypedArray, reverse_odd) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        std::cout << b << "\n"; 
        b.reverse();
        std::cout << b << "\n"; 
        EXPECT_EQ(b.pop().x, 1);
        EXPECT_EQ(b.pop().x, 2);
        EXPECT_EQ(b.pop().x, 3);
        std::cout << b << "\n"; 
    }

    TEST(TypedArray, reverse_even) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        b.push(Point(4,4,5));
        std::cout << b << "\n"; 
        b.reverse();
        std::cout << b << "\n"; 
        EXPECT_EQ(b.pop().x, 1);
        EXPECT_EQ(b.pop().x, 2);
        EXPECT_EQ(b.pop().x, 3);
        EXPECT_EQ(b.pop().x, 4);
        std::cout << b << "\n"; 
    }

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }
    
    TEST(TypedArray, PushAndPop_Normal) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        std::cout << b << "\n"; 
        EXPECT_EQ(b.pop().x, 3);
        EXPECT_EQ(b.pop().x, 2);
        EXPECT_EQ(b.pop().x, 1);
        std::cout << b << "\n"; 
    }

    TEST(TypedArray, PushFrontAndPopFront_Normal) {
        TypedArray<Point> b;
        b.push_front(Point(1,2,3));
        b.push_front(Point(2,3,4));
        b.push_front(Point(3,4,5));
        std::cout << b << "\n"; 
        EXPECT_EQ(b.pop_front().x, 3);
        EXPECT_EQ(b.pop_front().x, 2);
        EXPECT_EQ(b.pop_front().x, 1);
    }

    TEST(TypedArray, MixedMethods_Normal) {
        TypedArray<Point> b;
        b.push_front(Point(1,2,3));
        b.push_front(Point(2,3,4));
        b.push(Point(3,4,5));
        std::cout << b << "\n"; 
        EXPECT_EQ(b.pop_front().x, 2);
        EXPECT_EQ(b.pop().x, 3);
        EXPECT_EQ(b.pop_front().x, 1);
        std::cout << b << "\n"; 
    }

    TEST(TypedArray, Pop_Empty) {
        TypedArray<Point> b;
        try{
            b.pop();
        } catch (std::range_error e ){
            ASSERT_STREQ(e.what(), "Empty array");
        }
    }

    TEST(TypedArray, Pop_front_Empty) {
        TypedArray<Point> b;
        try{
            b.pop_front();
        } catch (std::range_error e ){
            ASSERT_STREQ(e.what(), "Empty array");
        }
    }

    TEST(TypedArray, concat) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a.concat(a).concat(a);
        std::cout << "b = "<< b << "\n"; 
        EXPECT_EQ(b.pop_front(), 0);
        EXPECT_EQ(b.pop_front(), 1);
        EXPECT_EQ(b.pop_front(), 0);
        EXPECT_EQ(b.pop_front(), 1);
        EXPECT_EQ(b.pop_front(), 0);
        EXPECT_EQ(b.pop_front(), 1);
        std::cout << "a = "<< a << "\n"; 
        EXPECT_EQ(a.pop_front(), 0);
        EXPECT_EQ(a.pop_front(), 1);
    }

    TEST(TypedArray, addingOn) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a + a + a;
        std::cout << "b = "<< b << "\n"; 
        EXPECT_EQ(b.pop_front(), 0);
        EXPECT_EQ(b.pop_front(), 1);
        EXPECT_EQ(b.pop_front(), 0);
        EXPECT_EQ(b.pop_front(), 1);
        EXPECT_EQ(b.pop_front(), 0);
        EXPECT_EQ(b.pop_front(), 1);
        std::cout << "a = "<< a << "\n"; 
        EXPECT_EQ(a.pop_front(), 0);
        EXPECT_EQ(a.pop_front(), 1);
    }

    TEST(TypedArray, concat_empty) {
        TypedArray<int> a;
        TypedArray<int> b = a.concat(a).concat(a);
    }

    // TEST(TypedArray, pop) {
    //     TypedArray<Point> b;
    //     b.push(Point(1,2, 0));
    //     b.push(Point(2,3, 0));
    //     b.push(Point(3,4, 0));
    //     EXPECT_EQ(b.pop().x, 3);
    //     EXPECT_EQ(b.pop().x, 2);
    //     EXPECT_EQ(b.pop().x, 1);
    // }


    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }

//**********************************************************************//
//           These are  tests for the Complex data type                 // 
//**********************************************************************//
    
    TEST(Complex,re_im) {
        Complex x(1,2);
        EXPECT_EQ(x.re(), 1);
        EXPECT_EQ(x.im(), 2);
    }

    TEST(Complex,add) {
        Complex x(1,2), y(3);
        Complex c = x + y;
        EXPECT_EQ(c.re(), 4);
        EXPECT_EQ(c.im(), 2);
    }

    TEST(Complex,mult) {
        Complex x(1,2), y(3);
        Complex c = x * y;
        EXPECT_EQ(c.re(), 3);
        EXPECT_EQ(c.im(), 6);
    }

    TEST(Complex,conjugate) {
        Complex x(1,2), y(3);
        Complex a = x.conjugate();
        Complex b = y.conjugate();
        EXPECT_EQ(a.re(), 1);
        EXPECT_EQ(a.im(), -2);
        EXPECT_EQ(b.re(), 3);
        EXPECT_EQ(b.im(), 0);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

}