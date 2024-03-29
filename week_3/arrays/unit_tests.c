#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, min) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_min(da), 1.0);
        DynamicArray_push(da, -1.0);
        ASSERT_EQ(DynamicArray_min(da), -1.0);
    }

    TEST(DynamicArray, max) {
        DynamicArray * da = DynamicArray_new();
        double x = -5.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_max(da), 5.0);
    }

    TEST(DynamicArray, mean) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_mean(da), 3.0);
    }

    TEST(DynamicArray, median) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_median(da), 3.0);
    }

    TEST(DynamicArray, median_even) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 4 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_median(da), 2.5);
    }

    TEST(DynamicArray, sum) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_sum(da), 15.0);
    }

    TEST(DynamicArray,Range_pos) {
        DynamicArray * da = DynamicArray_range(1.0, 5.0, 1.0);
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray,Range_neg) {
        DynamicArray * da = DynamicArray_range(5.0, 1.0, -1.0);
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[5.00000,4.00000,3.00000,2.00000,1.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray,concat) {
        DynamicArray * d = DynamicArray_range(5.0, 4.0, -1.0);
        DynamicArray * a = DynamicArray_range(3.0, 1.0, -1.0);
        DynamicArray * da = DynamicArray_concat(d, a);
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[5.00000,4.00000,3.00000,2.00000,1.00000]"
        );
        DynamicArray_destroy(a);
        DynamicArray_destroy(d);
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray,take_short) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * d = DynamicArray_take(a, 2);
        char * str = DynamicArray_to_string(d);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000]"
        );
        DynamicArray_destroy(a);
        DynamicArray_destroy(d);
        free(str);
    }

    TEST(DynamicArray,take_zero) {
        DynamicArray * a = DynamicArray_range(1, 2, 1);
        DynamicArray * d = DynamicArray_take(a, 5);
        char * str = DynamicArray_to_string(d);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,0,0,0]"
        );
        DynamicArray_destroy(a);
        DynamicArray_destroy(d);
        free(str);
    }

    TEST(DynamicArray,take_negzero) {
        DynamicArray * a = DynamicArray_range(1, 2, 1);
        DynamicArray * d = DynamicArray_take(a, -5);
        char * str = DynamicArray_to_string(d);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,0,0,0]"
        );
        DynamicArray_destroy(a);
        DynamicArray_destroy(d);
        free(str);
    }

//////////////////////////////
    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         

}