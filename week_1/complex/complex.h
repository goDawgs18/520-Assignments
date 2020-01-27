#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Complex number object and method definitions
 *
 *  A Complex number object is a struct with a real, denoted real, and
 *  a image, denoted im. Varions Methods that take complex numbers and return 
 *  complex numbers do arithmetical operations on them.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex numbers together
 *  \param a The first term
 *  \param b The second term
 */
Complex add ( Complex a, Complex b );

/*! Negates the complex number passed
 *  \param a The complex number being reduced
 */
Complex negate ( Complex a );

/*! Multiply two complex numbers together (does not reduce)
 *  \param a The first term
 *  \param b The second term
 */
Complex multiply ( Complex a, Complex b );

/*! Calculates the magnitude of the complex number passed
 *  \param a The complex number being evaluated
 */
double magnitude ( Complex a );

#endif