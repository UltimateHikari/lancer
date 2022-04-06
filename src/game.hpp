#ifndef LANCER_GAME_HPP
#define LANCER_GAME_HPP

#include "model/model.hpp"
#include "model/entities.hpp"
#include "db/database.hpp"
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
            return *(model.get());
        }

        void end(){};

        std::shared_ptr<std::vector<ent::SavedGame>> get_saved_games(){
            return db::Connector::select_saved_game();
        }
};

#endif
