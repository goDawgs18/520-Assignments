#include "fraction.h"
#include <cstdio>

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce ( Fraction a ) {
  if ( a.den == 0 ) {
      return (Fraction) { a.num, a.den};
  }
  // Euclidean algorithm for finding GCD
  // https://en.wikipedia.org/wiki/Euclidean_algorithm
  int remainder = a.num % a.den;
  int gcd = a.den;
  while (remainder != 0) {
    int new_gcd = remainder;
    remainder = gcd % new_gcd;
    gcd = new_gcd;
  }
  return (Fraction) { a.num / gcd, a.den / gcd };
}