#include <math.h>
#include "complex.h"
#include <iostream>


double Complex::magnitude() const {

    return sqrt(rl*rl + img*img);

}
double Complex::re() const {
    return this->rl;
}

double Complex::im() const {
    return this->img;
}

// Conjugate operator: i.e Conjugate of a = b + c*i returns d = b - c*i
Complex Complex::conjugate() const {
    return Complex(this->re(), -1.0 * this->im());
}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

// Assignment operator: i.e Complex a = b * c 
Complex operator*(const Complex& a, const Complex& b) {
    return Complex(a.re() * b.re() - a.im() * b.im(), a.im() * b.re() + a.re() * b.im());
}

// Assignment operator: i.e Complex a = b + c 
Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.re() + b.re(), a.im() + b.im());
}