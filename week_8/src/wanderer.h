#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

namespace {

    using namespace enviro;

    class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            oldSensorVal = sensor_value(1);
        }
        void during() { 
            track_velocity(2,0);
            double diff = sensor_value(1) - oldSensorVal;
            if (sensor_value(0) < 30) {
                emit(Event(tick_name));
            } else if (sensor_value(1) > 20){
                emit(Event("other"));
            } 
            oldSensorVal = sensor_value(1);
        }
        double oldSensorVal;
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class RotatingNeg : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            oldSensorVal = sensor_value(0);
            diff = DBL_MAX;
        }
        void during() { 
            track_velocity(-.4,rate); 
            double diff = oldSensorVal - sensor_value(0);
            //could do a difference. Once it starts increasing go forward
            if (diff * diff < 225 ) {
            // if (sensor_value(1) < 50 ) {
                emit(Event(tick_name));
            }
            oldSensorVal = sensor_value(1);
        }
        void exit(const Event& e) {}
        double rate = -1.5;
        double diff;
        double oldSensorVal;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;        
    };

    class RotatingPos : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            oldSensorVal = sensor_value(0);
            diff = DBL_MAX;
        }
        void during() { 
            track_velocity(0,rate); 
            double diff = oldSensorVal - sensor_value(0);
            //could do a difference. Once it starts increasing go forward
            if (diff * diff < 225 ) {//|| sensor_value(1) < 10) {
            // if (sensor_value(1) < 50 ) {
                emit(Event("back"));
            }
            oldSensorVal = sensor_value(0);
        }
        void exit(const Event& e) {}
        double rate = 1;
        double diff;
        double oldSensorVal;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;        
    };

    class WandererController : public StateMachine, public AgentInterface {

        public:
        WandererController() : StateMachine() {

            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand()%1000); // use an agent specific generated 
                                                               // event name in case there are 
                                                               // multiple instances of this class
            add_transition(tick_name, moving_forward, Nrotating);
            add_transition(tick_name, Nrotating, moving_forward);
            add_transition("other", moving_forward, Protating);
            add_transition("back", Protating, moving_forward);
            moving_forward.set_tick_name(tick_name);
            Nrotating.set_tick_name(tick_name);

        }

        MovingForward moving_forward;
        RotatingNeg Nrotating;
        RotatingPos Protating;
        std::string tick_name;

    };

    class Wanderer : public Agent {

        public:
        Wanderer(json spec, World& world) : Agent(spec, world) {
            add_process(wc);
        }

        WandererController wc;

    };

    DECLARE_INTERFACE(Wanderer);

}

#endif