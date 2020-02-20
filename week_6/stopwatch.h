#ifndef __STOPWATCH_H
#define __STOPWATCH_H

#include "elma/elma.h"

#include <chrono>
#include <exception>



class Stopwatch {//: public elma::Process {
    public:
        // Stopwatch(std::string name) : Process(name) {}
        Stopwatch() {}
        // void init() {}
        

        void start();            // starts the timer

        void stop();               // stops the timer
            
        void reset();             // sets stopwatch to zero
        

        double get_minutes();      // number of minutes counted, as a double
        double get_seconds();      // number of seconds counted, as a double
        double get_milliseconds(); // number of milliseconds counted, as a double
        double get_nanoseconds();  // number of nanoseconds counted, as a double

    private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        bool running = false;
        bool started = false;
};

#endif