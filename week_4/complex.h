#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : rl(x), img(y) {}
    Complex(double a) : rl(a), img(0) {};
    Complex() : rl(0), img(0) {};

    double magnitude() const;

    double re() const;

    double im() const;

    Complex conjugate() const;
    
    private:
    double rl, img;
}; 

//Operations
Complex operator*(const Complex& a, const Complex& b);
Complex operator+(const Complex& a, const Complex& b);

//Logical
bool operator<(const Complex& a, const Complex& b);

#endif