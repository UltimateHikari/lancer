#ifndef LANCER_MODEL_HPP
#define LANCER_MODEL_HPP

#include <string>
#include <lancer.hpp> //TODO - temponary measure, without adapters
#include <map>
#include <vector>
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
    SubInventory<Commodity> commodities;
    SubInventory<Module> modules;
public:
    void update_commodity(const Commodity& comm, int delta);
    const std::vector<std::pair<Commodity, int>>& get_commodities();
    void update_module(const Module& comm, int delta);
    const std::vector<std::pair<Module, int>>& get_module();
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
