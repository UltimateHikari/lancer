#include "model/entities.hpp"
#include "model/oututil.hpp"


namespace ent{

std::string Commodity::out(){
    return fmti(id) + fmt(type.name) + fmt(name);
}

std::string Module::out(){
    return fmti(id) + fmt(type.name) + fmt(name);
}

std::string SavedGame::out(){
    return fmti(id) + fmt(name) + fmt(date);
}

std::string Corporation::out(){
    return fmti(id) + fmt(name);
}

std::string Node::out(){
    return fmti(id) + fmt(name) + fmt(pref.name) + fmt(corp.name) + fmti(order_level) + fmti(tech_level);
}

std::string Lane::out(){
    return fmti(id) + fmt(start.name) + fmt(end.name) + fmti(traverse_time);
}

}