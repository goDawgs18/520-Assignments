#ifndef __INTEGRATOR_H
#define __INTEGRATOR_H

#include "elma/elma.h"

class Integrator : public elma::Process {
    Integrator(std::string name) : Process(name) {}

    void init() {}
    void start() {}
    void update() {
        double newVal = 0.0;
        if ( channel("link").nonempty() ) {
            newVal = channel("link").latest();
        }
        double integrateVal = newVal * delta();
        total += integrateVal;
    }

    void stop() {}
    
    double value() {
        return total;
    }
    private:
    double total = 0;
};
#endif