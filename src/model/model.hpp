#ifndef LANCER_MODEL_HPP
#define LANCER_MODEL_HPP

#include <string>
#include "model/entities.hpp"
#include <map>
#include <vector>
#include <utility>
#include <mutex>

namespace md{

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
    void load(int save_id);
    void save(std::string& save_name);
};

class Navigation{
private:
    ent::Node current_node;
    std::shared_ptr<std::vector<ent::Lane>> current_lanes;
public:
    void move_with_lane(ent::Lane& lane);
    const ent::Node& get_current_node();
    const std::vector<ent::Lane>& get_current_lanes();
};

};

class Model{
private:
    int sense_of_life = 42;
    bool game_active_flag = false;
    md::Inventory * inventory;
    md::Navigation * navigation;
public:
    std::string get_time();

    Model();
    ~Model();
    int get_sense();
    bool is_game_active();
    void set_game_active(bool activity);
    md::Inventory& get_inventory();
    md::Navigation& get_navigation();
    void load_game(int save_id);
    void save_game(std::string save_name);
};

#endif
