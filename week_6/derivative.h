#ifndef __DERIVATIVE_H
#define __DERIVATIVE_H

#include "elma/elma.h"

class Derviative : public elma::Process {
    public:
        Derviative(std::string name) : Process(name) {}

        void init() {}
        void start() {}
        void update() {
            double newVal = 0.0;
            if ( channel("link").nonempty() ) {
                newVal = channel("link").latest();
            }

            if (vals.size() >= 2) {
                for (int i = 1; i < vals.size(); i++) {
                    vals[i-1] = vals[i];
                }
                vals.pop_back();
            }
            vals.push_back(newVal);
        }

        void stop() {}

        double value() {
            if (vals.size() <= 1) {
                return 0;
            } else {
                return vals[1] - vals[0] / delta();
            }
        }
    
    private:
        vector<double> vals;
};
#endif