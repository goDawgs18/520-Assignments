#ifndef __ROBOT_H
#define __ROBOT_H

#include "elma/elma.h"

 #include <iostream>
 #include <chrono>


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

#endif