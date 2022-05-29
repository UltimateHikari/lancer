#include "db/database.hpp"
#include "model/oututil.hpp"

#include "model/entities.hpp"
#include "model/navigation.hpp"

#include "easyloggingpp/easylogging++.h"


using namespace md;

// ----- Navigation ----- //

const int MIN_ORDER_LEVEL = 1;
const int MAX_ORDER_LEVEL = 5;
const int MIN_TECH_LEVEL = 1;
const int MAX_TECH_LEVEL = 10;

void apply_mod_to_node(ent::Node* node, ent::Modifier& mod){
    if(mod.type.name == "LEVELS"){
        node->order_level += mod.order_level;
        node->order_level = (node->order_level < MIN_ORDER_LEVEL ? MIN_ORDER_LEVEL : node->order_level);
        node->order_level = (node->order_level > MAX_ORDER_LEVEL ? MAX_ORDER_LEVEL : node->order_level);

        node->tech_level += mod.tech_level;
        node->tech_level = (node->tech_level < MIN_TECH_LEVEL ? MIN_TECH_LEVEL : node->tech_level);
        node->tech_level = (node->tech_level > MAX_TECH_LEVEL ? MAX_TECH_LEVEL : node->tech_level);
        LOG(INFO) << "applied type " << mod.type.name << " on node " << node->name;

    }
    if(mod.type.name == "PREFS"){
        node->pref = mod.pref;
        LOG(INFO) << "applied type " << mod.type.name << " on node " << node->name;
    }
    LOG(INFO) << "applied";
}

ent::Node Navigation::refresh_node(){
    auto nodes = db::Connector::select_node();
    LOG(INFO) << "refreshing current node: ";
    if(nodes.get()->size() < current_node_id){
        LOG(ERROR) << "your ship was eaten by current_lane_id dragon\n";
        exit(-1);
    }
    // in res from 0, in db ftom 1. may break, better use find?
    ent::Node node = (*(nodes.get()))[current_node_id - 1];
    auto mods = db::Connector::select_mod_per_node(node.id);
    for(auto& i : *mods){
        apply_mod_to_node(&node, i);
    }
    return node; 
}

int Navigation::move_with_lane(const ent::Lane& lane){
    LOG(INFO) << "moving from node : " + fmti(current_node_id);
    current_node_id = (current_node_id == lane.end.id ? lane.start.id : lane.end.id);
    LOG(INFO) << "moved to node    : " + fmti(current_node_id);
    return current_node_id;
}

const ent::Node& Navigation::get_current_node(){
    if(cached_node.id != current_node_id){
        cached_node = refresh_node();
    }
    return cached_node;

}
const std::vector<ent::Lane>& Navigation::get_current_lanes(){
    if(current_lanes_id != current_node_id){
        cached_lanes = db::Connector::select_single_node_lanes(current_node_id);
        current_lanes_id = current_node_id;
    }
    return *(cached_lanes.get());
}