#include "gtest/gtest.h"
#include "rpn.h"
#include <climits>
#include <cfloat>


namespace {

    TEST(HW2,RunningTotal) {
        ASSERT_EQ(running_total(1),  1);
        ASSERT_EQ(running_total(1),  2);
        ASSERT_EQ(running_total(5),  7);
        ASSERT_EQ(running_total(-3), 4);
        reset_total();
    }

    TEST(HW2,RunningTotal_negative_limit) {
        ASSERT_EQ(running_total(INT_MIN),  INT_MIN);
        ASSERT_EQ(running_total(-1),  INT_MIN);
        reset_total();
    }

    TEST(HW2,RunningTotal_max_value) {
        ASSERT_EQ(running_total(INT_MAX),  INT_MAX);
        ASSERT_EQ(running_total(INT_MAX),  INT_MAX);
        ASSERT_EQ(running_total(-1),  INT_MAX - 1);
        reset_total();
    }

    TEST(HW2,Reverse) {
        int x[] = {10,20,30};
        int * y = reverse(x,3);
        ASSERT_EQ(y[0],30);
        ASSERT_EQ(y[1],20);       
        ASSERT_EQ(y[2],10);   
        // ASSERT_EQ(y[3],20);   
        // ASSERT_EQ(y[4],10);  
        free(y);
    }

    TEST(HW2,NumInstances) {
        int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
        ASSERT_EQ(num_instances(a,10,1), 3);
    }
 
    TEST(HW2,ReverseInPlace) {
        int x[] = {10,20,30,40,50};
        reverse_in_place(x,5);
        ASSERT_EQ(x[0],50);
        ASSERT_EQ(x[1],40);       
        ASSERT_EQ(x[2],30);   
        ASSERT_EQ(x[3],20);   
        ASSERT_EQ(x[4],10);                            
    }

    TEST(HW2,ReverseInPlace_EvenLength) {
        int x[] = {10,20,30,40};
        reverse_in_place(x,4);
        ASSERT_EQ(x[0],40);       
        ASSERT_EQ(x[1],30);   
        ASSERT_EQ(x[2],20);   
        ASSERT_EQ(x[3],10);                            
    }

    TEST(HW2, RPN_Resize) {
        rpn_init();
        int currSize = rpn_size();
        for (int i = 0; i < 110; i++) {
            rpn_push(i);
        }
        for (int i = 0; i < 110; i++) {
            ASSERT_EQ(rpn_pop(), 110 -1 -i);
        }
        int finalSize = rpn_size();
    } 

    TEST(HW2,RPN_Divide) {
        rpn_init();
        rpn_push(6);
        rpn_push(2);
        rpn_divide();
        ASSERT_EQ(rpn_pop(),3);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_Divide_Error) {
        rpn_init();
        rpn_push(6);
        rpn_push(0);
        rpn_divide();
        ASSERT_EQ(rpn_error(), DIVIDE_BY_ZERO_ERROR);
        rpn_free();
    }

    TEST(HW2,RPN_Divide_pos_overflow) {
        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(0.1);
        rpn_divide();
        ASSERT_EQ(rpn_pop(), DBL_MAX);
        rpn_free();
    }

    TEST(HW2,RPN_Divide_neg_overflow) {
        rpn_init();
        rpn_push(-DBL_MAX);
        rpn_push(0.1);
        rpn_divide();
        ASSERT_EQ(rpn_pop(), -DBL_MAX);
        rpn_free();
    }



    TEST(HW2,RPN_BASICS) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_push(1.0);
        rpn_add();
        rpn_multiply();
        rpn_negate();
        ASSERT_EQ(rpn_pop(),-1.5);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_ERRORS) {
        
        rpn_push(0.5);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_pop();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_add();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_multiply();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_negate();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);                                
        rpn_free();

        rpn_init();
        rpn_pop();
        ASSERT_EQ(rpn_error(), POP_ERROR);
        rpn_free();

        rpn_init();
        rpn_negate();
        ASSERT_EQ(rpn_error(), UNARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_add();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_multiply();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);  
        rpn_free();

        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(DBL_MAX);
        rpn_add();
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(DBL_MAX);
        rpn_negate();
        rpn_multiply();
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_free();        

    }    

}
