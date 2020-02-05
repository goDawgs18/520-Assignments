#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : rl(x), img(y) {}
    Complex(double a) : rl(a), img(0) {};

    double magnitude() const;

    double re() const;

    double im() const;
    
    private:
    double rl, img;
}; 

bool operator<(const Complex& a, const Complex& b);

#endif