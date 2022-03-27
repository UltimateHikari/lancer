#include "model/model.hpp"
#include "database.hpp"
#include <ctime> // time, localtime
#include <iomanip> // put_time
#include <algorithm> // copy

// ----- Model ----- //

Model::Model():
    inventory(new Inventory())
{}
Model::~Model(){
    delete inventory;
}

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

Inventory& Model::get_inventory(){
    return *inventory;
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
const std::vector<std::pair<T, int>>& SubInventory<T>::get(){
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
const std::vector<std::pair<ent::Commodity, int>>& Inventory::get_commodities(){
    return commodities.get();
}
void Inventory::update_module(const ent::Module& mod, int delta){
    modules.update(mod, delta);
}
const std::vector<std::pair<ent::Module, int>>& Inventory::get_modules(){
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