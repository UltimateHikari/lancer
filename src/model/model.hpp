#ifndef LANCER_MODEL_HPP
#define LANCER_MODEL_HPP

#include <string>
#include "model/entities.hpp"
#include <map>
#include <vector>
#include <utility>
#include <mutex>

template<class T>
class SubInventory{
private:
    std::mutex mutex;
    int inventory_state;
    int snapshot_state;
    std::map<T, int> inventory;
    std::vector<std::pair<T, int>> snapshot;
    void repopulate_snapshot();
public: 
    SubInventory();
    void update(const T& t, int delta);
    const std::vector<std::pair<T, int>>& get();
};

class Inventory{
private:
    SubInventory<ent::Commodity> commodities;
    SubInventory<ent::Module> modules;
public:
    void update_commodity(const ent::Commodity& comm, int delta);
    const std::vector<std::pair<ent::Commodity, int>>& get_commodities();
    void update_module(const ent::Module& comm, int delta);
    const std::vector<std::pair<ent::Module, int>>& get_modules();
};


class Model{
private:
    int sense_of_life = 42;
    bool game_active_flag = false;
    Inventory * inventory;
public:
    std::string get_time();

    Model();
    ~Model();
    int get_sense();
    bool is_game_active();
    void set_game_active(bool activity);
    Inventory& get_inventory();
};

#endif
