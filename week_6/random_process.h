#ifndef __RANDOM_PROCESS_H
#define __RANDOM_PROCESS_H


#include "elma/elma.h"

class RandomProcess : public elma::Process {
    public:
        RandomProcess(std::string name) : Process(name) {}

        void init() {}
        void start() {}
        void update() {
            channel("link").send((double)std::rand()/RAND_MAX);
        }
        void stop() {}
    private:
        double max = 1.0;
        double min = 0.0;
};

class Filter : public elma::Process {
    public:
        Filter(std::string name) : Process(name) {}

        void init() {}
        void start() {}
        void update() {
            double newVal = 0.0;
            if ( channel("link").nonempty() ) {
                newVal = channel("link").latest();
            }

            if (vals.size() >= 10) {
                for (int i = 1; i < vals.size(); i++) {
                    vals[i-1] = vals[i];
                }
                vals.pop_back();
            }
            vals.push_back(newVal);
        }
        void stop() {}

        double value() {
            double sum = 0.0;
            for (int i = 0; i < vals.size(); i++) {
                sum += vals[i];
            }
            return sum / vals.size();
        }
    
    private:
        vector<double> vals;
};
#endif