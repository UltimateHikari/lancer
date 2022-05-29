#ifndef LANCER_MODEL_TELLER_HPP
#define LANCER_MODEL_TELLER_HPP

#include "model/entities.hpp"


namespace md{

class Storyteller { //TODO - init with modifs in db, write tests for modifs
private:
    std::vector<int> weights;
    std::map<ent::Event, int> events;

    int get_random_modifier();
    static const int TELLER_MAX_WEIGHT = 10;
    std::shared_ptr<ent::VModifierLog> log_modifier(int time, int node_id, int mod_id);
public: 
    Storyteller();
    std::shared_ptr<ent::VModifierLog> play_random_event(int time, int node_id);
    std::shared_ptr<ent::VModifierLog> play_event(int time, int node_id, ent::Event& e);
};

}

#endif
