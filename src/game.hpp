#ifndef LANCER_GAME_HPP
#define LANCER_GAME_HPP

#include "lancer.hpp"
#include <vector>

// Controller

class Game{
    public:
        void start(){
            exit(-1);
        }
        Node& get_system_info();
        //Lanes get_lanes_info();
        void end(){};
};

#endif
