#include "stopwatch.h"
#include <exception>
// #include <cstdlib>


using namespace std::chrono;

void Stopwatch::reset() {
    start_time = end_time;
}

void Stopwatch::start() {
    start_time = high_resolution_clock::now();
    end_time = start_time;
    this->running = true;
    this->started = true;
}

void Stopwatch::stop() {
    if (!this->started) {
        throw std::runtime_error("Have not started timer");
    }
    end_time = high_resolution_clock::now();
    running = false;
}

double Stopwatch::get_minutes() {
    return this->get_seconds() / 60;
}

double Stopwatch::get_seconds() {
    if (!this->started) {
        throw std::runtime_error("Timer needs to be started");
    } else if (this->running) {
        throw std::runtime_error("Timer is still running");
    }
    duration<double> time_span = duration_cast<duration<double>>(this->end_time - this->start_time);
    return time_span.count();
}

double Stopwatch::get_milliseconds() {
    return this->get_seconds() * 1000;
}

double Stopwatch::get_nanoseconds() {
    return this->get_seconds() * 1000000000;
}