#ifndef LANCER_GAME_HPP
#define LANCER_GAME_HPP

#include "model/model.hpp"
#include <vector>
#include <memory>

// Controller

class Game{
    private:
        std::unique_ptr<Model> model;
    public:
        void start(){
            model->set_game_active(true);
        }
        Game(){
            model = std::make_unique<Model>();
        }
        Model& getModel(){
            return *model;
        }
        void end(){};
};

#endif
