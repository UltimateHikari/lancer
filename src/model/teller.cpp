#include <random>

#include "db/database.hpp"

#include "model/teller.hpp"

#include "easyloggingpp/easylogging++.h"

using namespace md;

// ----- Teller ----- //

Storyteller::Storyteller(){
    auto evt = db::Connector::select_encounter();
    auto mods = db::Connector::select_mod();
    for(auto& m : *(mods.get())){
        auto key_ptr = std::find_if(
            evt.get()->begin(), evt.get()->end(),
            [&](const auto& p){return p.id == m.event_id;}
            );
        if(key_ptr != evt.get()->end()){
            events[*key_ptr] = m.id;
            LOG(INFO) << "teller noted event-id: " << key_ptr->id << " with mod-id " << m.id;
        }
    }
    transform(events.begin(), events.end(), std::back_inserter(weights),
         [](const auto& val){return val.first.weight;} 
         );
    LOG(INFO) << "tellers event weights:";
    for(auto& i : weights){
        LOG(INFO) << i;
    }
}

int Storyteller::get_random_modifier(){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    int ind = dist(mt);

    LOG(INFO) << "teller chose " << ind;
    
    // index = id, assuming continioius id in table
    // return events[ind].id;
    // TODO rewrite map to vector, now it works only because event.id = mod.id
    return ind + 1;
}

std::shared_ptr<ent::VModifierLog> Storyteller::log_modifier(int time, int node_id, int mod_id){
    LOG(INFO) << "teller got mod: " << mod_id << " on node: " << node_id;
    ent::ModifierLog log{time, node_id, mod_id};
    auto res_vmodlog = db::Connector::push_mod_log(log);
    LOG(INFO) << res_vmodlog->out();
    return res_vmodlog;
}

std::shared_ptr<ent::VModifierLog> Storyteller::play_random_event(int time, int node_id){
    return log_modifier(time, node_id, get_random_modifier());
}
std::shared_ptr<ent::VModifierLog> Storyteller::play_event(int time, int node_id, ent::Event& e){
    //TODO event may not reside in events
    return log_modifier(time, node_id, events[e]);
}
