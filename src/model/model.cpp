#include "model/model.hpp"
#include "db/database.hpp"
#include <ctime> // time, localtime
#include <iomanip> // put_time
#include <algorithm> // copy


#include "easyloggingpp/easylogging++.h"


// ----- Model ----- //
using namespace md;

Model::Model():
    inventory(std::make_unique<Inventory>()),
    navigation(std::make_unique<Navigation>()),
    trade(std::make_unique<Trade>())
{}


int Model::get_sense(){
    return sense_of_life;
}
bool Model::is_game_active(){
    return game_active_flag;
}
void Model::set_game_active(bool activity){
    game_active_flag = activity;
}

std::string Model::get_time(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

    return oss.str();
}

void Model::load_game(int save_id){
    inventory->load(save_id);
}
void Model::save_game(std::string save_name){
    inventory->save(save_name);
}

// ----- Subinventory ----- //

template<class T>
SubInventory<T>::SubInventory(): 
    inventory_state(0), 
    snapshot_state(0)
{}

template<class T>
void SubInventory<T>::update(const T& t, int delta){
    mutex.lock();
    inventory[t] += delta;
    inventory_state++;
    mutex.unlock();
}

template<class T>
std::vector<std::pair<T, int>>& SubInventory<T>::get(){
    if(mutex.try_lock()){
        if(snapshot_state != inventory_state){
            repopulate_snapshot();
            snapshot_state = inventory_state;
        }
        mutex.unlock();
    }
    return snapshot;
}

template<class T>
void SubInventory<T>::repopulate_snapshot(){
    snapshot.assign(inventory.begin(), inventory.end());
}


// ----- Inventory ----- //

void Inventory::update_commodity(const ent::Commodity& comm, int delta){
    commodities.update(comm, delta);
}
std::vector<std::pair<ent::Commodity, int>>& Inventory::get_commodities(){
    return commodities.get();
}
void Inventory::update_module(const ent::Module& mod, int delta){
    modules.update(mod, delta);
}
std::vector<std::pair<ent::Module, int>>& Inventory::get_modules(){
    return modules.get();
}

void Inventory::load(int save_id){
    auto commodities = db::Connector::select_saved_commodity(save_id);
    auto modules = db::Connector::select_saved_module(save_id);
    for(auto& i: *(modules.get())){
        update_module(i.first, i.second);
    }
    for(auto& i: *(commodities.get())){
        update_commodity(i.first, i.second);
    }
}
void Inventory::save(std::string& save_name){
    auto modules = get_modules();
    auto commodities = get_commodities();
    db::Connector::insert_save(save_name, modules, commodities);
}

// ----- Navigation ----- //

ent::Node Navigation::refresh_node(){
    auto nodes = db::Connector::select_node();
    LOG(INFO) << "refreshing current node: ";
    if(nodes.get()->size() < current_node_id){
        LOG(ERROR) << "your ship was eaten by current_lane_id dragon\n";
        exit(-1);
    }
    return (*(nodes.get()))[current_node_id - 1]; // in res from 0, in db ftom 1. may break, better use find?
}

void Navigation::move_with_lane(const ent::Lane& lane){
    LOG(INFO) << "moving from node : " + fmti(current_node_id);
    current_node_id = (current_node_id == lane.end.id ? lane.start.id : lane.end.id);
    LOG(INFO) << "moved to node    : " + fmti(current_node_id);
    //TODO drop extra stocks;
}

const ent::Node& Navigation::get_current_node(){
    if(cached_node.id != current_node_id){
        cached_node = refresh_node();
    }
    return cached_node;

}
const std::vector<ent::Lane>& Navigation::get_current_lanes(){
    if(current_lanes_id != current_node_id){
        cached_lanes = db::Connector::select_lane(current_node_id);
        current_lanes_id = current_node_id;
    }
    return *(cached_lanes.get());
}

std::shared_ptr<Inventory> Trade::generate_stock(const ent::Node& node){
    auto inv = std::make_shared<Inventory>();
    auto dbcomms = db::Connector::select_commodity();
    //TODO algo for random
    for(auto& i : *(dbcomms.get())){
        inv.get()->update_commodity(i, 10);
    }
    return inv;
}
Inventory& Trade::get_stock_for(const ent::Node& node){
    auto it = std::find_if(cached_stocks.begin(), cached_stocks.end(), 
                        [&](std::pair<int, std::shared_ptr<Inventory>> p){ return p.first == node.id; });
    if(!(it != cached_stocks.end())){
        cached_stocks.push_front(std::make_pair(node.id, generate_stock(node)));
        it = cached_stocks.begin();
        LOG(INFO) << "Stock for " + fmti(node.id) + " placed";
    } 
    return *(it->second.get());
}
const int Trade::stock_record_deal_comm(const ent::Node& node, const ent::Commodity& comm, int delta){
    int stock_delta = (-1)*delta;
    auto commodities = get_stock_for(node).get_commodities();
    auto it = std::find_if(commodities.begin(), commodities.end(), 
                        [&](std::pair<ent::Commodity, int> p){return p.first.id == comm.id;});
    if(!(it != commodities.end()) && delta > 0){
        LOG(INFO) << "cannot buy commodity, not enough in stock: " + fmti(comm.id);
        return 0;
    }
    get_stock_for(node).update_commodity(comm, stock_delta);
    return delta;
}
const int Trade::stock_record_deal_mod(const ent::Node& node, const ent::Module& mod, int delta){
    int stock_delta = (-1)*delta;
    auto modules = get_stock_for(node).get_modules();
    auto it = std::find_if(modules.begin(), modules.end(), 
                        [&](std::pair<ent::Module, int> p){return p.first.id == mod.id;});
    if(!(it != modules.end()) && delta > 0){
        LOG(INFO) << "cannot buy module, not enough in stock: " + fmti(mod.id);
        return 0;
    }
    get_stock_for(node).update_module(mod, stock_delta);
    return delta;
}
