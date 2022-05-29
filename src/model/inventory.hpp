#ifndef LANCER_MODEL_INVENTORY_HPP
#define LANCER_MODEL_INVENTORY_HPP

#include <map>
#include <mutex>
#include <numeric>

#include "model/entities.hpp"

namespace md {

template<class T>
class SubInventory{
private:
    std::mutex mutex;
    int inventory_state;
    int snapshot_state;
    std::map<T, ent::Meta> inventory;
    std::vector<std::pair<T, ent::Meta>> snapshot;
    void repopulate_snapshot();
public: 
    SubInventory();
    void update(const T& t, int delta, int price);
    std::vector<std::pair<T, ent::Meta>>& get();
    bool have_enough_of(const T& t, int delta);
    int get_size();
};

class Inventory{
private:
    SubInventory<ent::Commodity> commodities;
    SubInventory<ent::Module> modules;
public:
    void update_commodity(const ent::Commodity& comm, int delta, int price);
    std::vector<std::pair<ent::Commodity, ent::Meta>>& get_commodities();
    void update_module(const ent::Module& comm, int delta, int price);
    std::vector<std::pair<ent::Module, ent::Meta>>& get_modules();
    bool have_enough_of_comm(const ent::Commodity& t, int delta);
    bool have_enough_of_mod(const ent::Module& t, int delta);
    void load(int save_id);
    void save(std::string& save_name);
    int get_size();
};

// ----- Subinventory impl ----- //

template<class T>
SubInventory<T>::SubInventory(): 
    inventory_state(0), 
    snapshot_state(0)
{}

template<class T>
void SubInventory<T>::update(const T& t, int delta, int price){
    mutex.lock();
    inventory[t].amount += delta;
    if(price > 0){
        //NOTE: it's ambigious that non-zeroness of price matters
        inventory[t].price = price; 
    }
    inventory_state++;
    mutex.unlock();
}

template<class T>
std::vector<std::pair<T, ent::Meta>>& SubInventory<T>::get(){
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

template<class T>
bool SubInventory<T>::have_enough_of(const T& t, int delta){
    auto inv = get();
    auto it = std::find_if(inv.begin(), inv.end(), 
                        [&](const auto& p){return p.first.id == t.id;});
    if(it != inv.end() && it->second.amount + delta > -1){
        return true;
    }
    if(delta >= 0){
        return true;
    }
    return false;
}

template<class T>
int SubInventory<T>::get_size(){
    return std::accumulate(
        inventory.begin(), inventory.end(), 0,
        [](const std::size_t previous, const auto& element)
        { return previous + element.second.amount; }
        );
}

}

#endif
