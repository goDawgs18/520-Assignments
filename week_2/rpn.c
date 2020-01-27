#include <stdio.h>
#include <math.h>

#include <climits>
#include <cfloat>

#include "rpn.h"

#define INITIAL_STACK_SIZE 100

static double * stack;
static int initialized = 0;
static int top = 0;
static RPN_ERROR error = OK;

static int running_total_value = 0;

int running_total(int x) {
    if (x > 0 && running_total_value >= INT_MAX - x) {
        running_total_value = INT_MAX;
    } else if (x < 0 && running_total_value < INT_MIN - x) {
        running_total_value = INT_MIN;
    } else {
        running_total_value += x;
    }
    return running_total_value;
}

void reset_total() {
    running_total_value = 0;
}

void reverse_in_place(int * a, int l) {
    int * tmp = 0;
    for (int i = 0; i < (l - 1) /2; i++) {
        *tmp = a[i];
        a[i] = a[l-1-i];
        a[l-1-i] = *tmp;
    }
}

int * reverse(int * a, int l) {
    int * new_a = (int *) calloc(l,sizeof(int));
    for (int i = 0; i < l; i++) {
        printf("a[%d] = %d\n", l-i-1, a[l-i-1]);
        new_a[i] = a[l-i-1];
    }
    return new_a;
}

int num_instances(int * a, int l, int v){
    int count = 0;
    for (int i = 0; i < l; i++) {
        if (a[i] == v) {
            count++;
        }
    }
    return count;
}

Point negate(Point p) {
    return Point { -p.x, -p.y, -p.z };
}

Point * map(Point * a, int l, Point (*fxn) (Point)) {
  Point * new_a = (Point*) calloc(l,sizeof(Point));
  
  for (int i = 0; i < l; i++) {
      new_a[i] = fxn(a[i]);
  }
  
  return new_a;
}

void rpn_divide() {
    if (!initialized) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else if (stack[top] == 0) {
        error = DIVIDE_BY_ZERO_ERROR;
    } else {
        double check = stack[top - 1] / stack[top];
        //check for overflow error
        if (check * stack[top] != stack[top - 1]) {
            //overflow routine
            if ( stack[top - 1] > 0 && stack[top] > 0 ||
                stack[top - 1] < 0 && stack[top] < 0) {
                check = DBL_MAX;
            } else {
                check = DBL_MIN;
            }
        } 
        top--;
        stack[top-1] = check;
    }
}

void rpn_show() {
    printf("--->\n");
    for ( int i=0; i<top; i++ ) {
        printf("  %lf\n", stack[i]);
    }
    printf("<---\n");
}

void rpn_init() {
  if ( ! initialized ) {
      stack = (double *) calloc(INITIAL_STACK_SIZE, sizeof(double));
      initialized = 1;
      top = 0;
      error = OK;
  }
}

void rpn_push(double x) {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else {
        stack[top] = x;
        top++;
    }
}

void rpn_add() {  
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else {    
        double x = stack[top-1]+stack[top-2];
        if ( x == INFINITY ) {
            error = OVERFLOW_ERROR;
        } 
        top--;
        stack[top-1] = x;
    }
}

void rpn_negate() {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 1 ) {
        error = UNARY_ERROR;
    } else {    
      stack[top-1] = -stack[top-1];
    }
}

void rpn_multiply() {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else {    
        double x = stack[top-1]*stack[top-2];
        if ( x == INFINITY || x == -INFINITY ) {
            error = OVERFLOW_ERROR;
        } 
        top--;
        stack[top-1] = x;
    }
}

double rpn_pop() { 
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
        return 0;
    } else if ( top == 0 ) {
        error = POP_ERROR;
        return 0;        
    } else {
        double result = stack[top-1];
        top--;
        return result;
    }
 }

RPN_ERROR rpn_error() { return error; }

void rpn_free() {
    if ( initialized ) {
        free(stack);
        initialized = 0;
    }
    error = OK;
}