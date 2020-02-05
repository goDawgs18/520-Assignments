#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(rl*rl + img*img);

}
double Complex::re() const {
    return this->rl;
}

double Complex::im() const {
    return this->img;
}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}