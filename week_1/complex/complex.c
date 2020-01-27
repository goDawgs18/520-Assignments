#include "complex.h"
#include <math.h>


Complex add ( Complex a, Complex b ){
    return (Complex) { a.real + b.real, a.im + b.im };
}

Complex negate ( Complex a ) {
    return (Complex) { -1.0 * a.real, -1.0 * a.im };
}

Complex multiply ( Complex a, Complex b ) {
    return (Complex) { a.real * b.real - a.im * b.im, a.real * b.im + a.im * b.real };
}

double magnitude ( Complex a ) {
    return sqrt(a.real * a.real + a.im * a.im);
}