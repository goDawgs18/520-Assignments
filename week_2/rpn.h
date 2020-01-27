#ifndef RPN_H
#define RPN_H

#include <stdlib.h>

typedef enum {
    OK, 
    NOT_INITIALIZED_ERROR, 
    POP_ERROR, 
    UNARY_ERROR, 
    BINARY_ERROR, 
    OVERFLOW_ERROR,
    DIVIDE_BY_ZERO_ERROR
} RPN_ERROR;

void rpn_init();
void rpn_push(double x);
void rpn_add();
void rpn_negate();
void rpn_multiply();
double rpn_pop();
RPN_ERROR rpn_error();
void rpn_free();

/*! Calculates the summation of every integer value given
 *  \param x The integer that will be added to the sum
 */
int running_total(int x);

/*! Reverses the order of the values in integer array x
 *  \param a The array that will be reveresed
 *  \param l The length of array a
 */
void reverse_in_place(int * a, int l);

/*! Returns an array with the integer values in array x reversed
 *  \param a The array that will be reveresed
 *  \param l The length of array a
 */
int * reverse(int * a, int l);

/*! Sets the running total value back to zero 
 */
void reset_total();

/*! Returns the number of instances of the integer in an array of integers 
 * \param a The array that will be searched
 * \param l The length of the array
 * \param v The value I would be searching for
 */
int num_instances(int * a, int l, int v);

/*! \breif Point number object and method definitions
 *
 *  A Point object is a struct with three doubles characterizing x, y, and z positions
 */
 typedef struct {
   double x;
   double y;
   double z;
 } Point;


/*! Returns a new array with all of the contents of original but with the function
 *  applied to them.
 * \param a The array that will be searched
 * \param l The length of the array
 * \param fxn The function that will be applied to the points
 */
Point * map(Point* a, int l, Point (*fxn) (Point));

/*! Returns the negative version of the point
 *  
 * \param p The Point being negated
 */
Point negate(Point p);

void rpn_divide();

#endif