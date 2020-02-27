#ifndef __ROBOT_H
#define __ROBOT_H

#include "elma/elma.h"

#include <iostream>
#include <chrono>

#include <json/json.h>

using nlohmann::json;

#include <algorithm>


using namespace std::chrono;
using namespace elma;
 
namespace robot_states {
    class Wander : public elma::State {
        public:
         Wander() : State("Wander") {}
 
         void entry(const Event& e) {}

         void during() {} 
 
         void exit(const Event& e) {}
    };

    class FindRecharge : public elma::State {
        public:
         FindRecharge() : State("Find Recharge") {}
 
         void entry(const Event& e) {}
         
         void during() {} 
 
         void exit(const Event& e) {}
    };

    class MakeNoise : public elma::State {
        public:
         MakeNoise() : State("Make Noise") {}
 
         void entry(const Event& e) {}
         
         void during() {} 
 
         void exit(const Event& e) {}
    };

    class Recharge : public elma::State {
        public:
         Recharge() : State("Recharge") {}
 
         void entry(const Event& e) {}
         
         void during() {} 
 
         void exit(const Event& e) {}
    };

    class Evade : public elma::State {
        public:
         Evade() : elma::State("Evade") {}
 
         void entry(const Event& e) {}
         
         void during() {} 
 
         void exit(const Event& e) {}
    };
}


class Robot : public elma::StateMachine {
    public:

    Robot(std::string name) : elma::StateMachine(name) {

        

        this->elma::StateMachine::set_initial(wander);
        
        //from wander
        this->add_transition("battery low", wander, find_recharge);
        this->add_transition("intruder detected", wander, make_noise);

        //from find_recharge
        this->add_transition("found recharge station", find_recharge, recharge);

        //from recharge
        this->add_transition("battery full", recharge, wander);

        //from make_noise
        this->add_transition("reset", make_noise, wander);
        this->add_transition("proximity warning", make_noise, evade);

        //from evade
        this->add_transition("reset", evade, make_noise);
        this->add_transition("battery low", evade, find_recharge);
    }
    
    // void Robot::start() : StateMachine::start(){
    //     this->elma::StateMachine::set_initial(wander);
    // }

    private:
    robot_states::Wander wander;
    robot_states::FindRecharge find_recharge;
    robot_states::Recharge recharge;
    robot_states::MakeNoise make_noise;
    robot_states::Evade evade;

};

class BetterStateMachine : public elma::StateMachine {
    public:

    BetterStateMachine() : elma::StateMachine() {

    }

    BetterStateMachine(std::string name) : elma::StateMachine(name) {

    }

    json to_json()  { 
        // Cannot make const because name function is not const
        std::string s = "{ \"name\": \"";
        std::string n = elma::Process::name();
        s += n + "\",";
        
        std::vector<string> states = get_states();

        s += "\"states\": [";
        for (int i = 0; i < states.size(); i++) {
            s += "\"" + states[i]+ "\"";
            if (i != states.size() - 1) {
                s += ",";
            }
        }
        s += "],";

        s += "\"transitions\": [";

        for (int i = 0; i < _transitions.size(); i++) {
            s += "{\"from\": \"";
            s += _transitions[i].from().name() + "\",";

            s += "\"to\": \"";
            s += _transitions[i].to().name() + "\",";

            s += "\"when\": \"";
            s += _transitions[i].event_name() + "\"";

            s += "}";
            if (i != _transitions.size() - 1) {
                s += ",";
            }
        }
        s += "]";
        s += "}";
        return json::parse(s);
    }

    private:

    State& get_init() { return *_initial; }
    
    std::string get_name() {
        return elma::Process::name();
    }

    std::vector<string> get_states() {
        std::vector<string> states;
        
        states.push_back(get_init().name());
        // Getting segmentation issues with this line of code when not connected to manager
        // states.push_back(this->current().name());
        for (int i = 0; i < _transitions.size(); i++) {
            if (std::find(states.begin(), states.end(),_transitions[i].from().name()) == states.end()) {
                states.push_back(_transitions[i].from().name());
            }
            if (std::find(states.begin(), states.end(),_transitions[i].to().name()) == states.end()) {
                states.push_back(_transitions[i].to().name());
            }
        }
        return states;
    }

};

#endif