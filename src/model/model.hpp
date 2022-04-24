#ifndef LANCER_MODEL_HPP
#define LANCER_MODEL_HPP

#include <string>
#include "model/entities.hpp"
#include <map>
#include <vector>
#include <utility>
#include <mutex>
#include <deque>

#include "model/oututil.hpp"
#include "easyloggingpp/easylogging++.h"

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
    std::vector<std::pair<T, int>>& get();
    bool have_enough_of(const T& t, int delta);
};

class Inventory{
private:
    SubInventory<ent::Commodity> commodities;
    SubInventory<ent::Module> modules;
public:
    void update_commodity(const ent::Commodity& comm, int delta);
    std::vector<std::pair<ent::Commodity, int>>& get_commodities();
    void update_module(const ent::Module& comm, int delta);
    std::vector<std::pair<ent::Module, int>>& get_modules();
    bool have_enough_of_comm(const ent::Commodity& t, int delta);
    bool have_enough_of_mod(const ent::Module& t, int delta);
    void load(int save_id);
    void save(std::string& save_name);
};

class Navigation{
private:
    ent::Node cached_node;
    int current_node_id = 1;
    std::shared_ptr<std::vector<ent::Lane>> cached_lanes;
    int current_lanes_id = 0;
    ent::Node refresh_node();
public:
    Navigation(){
        this->cached_node = refresh_node();
    };
    void move_with_lane(const ent::Lane& lane);
    const ent::Node& get_current_node();
    const std::vector<ent::Lane>& get_current_lanes();
};

class Trade{
private: 
    std::deque<std::pair<int, std::shared_ptr<Inventory>>> cached_stocks;
    std::shared_ptr<Inventory> generate_stock(const ent::Node& node);
public: 
    Inventory& get_stock_for(const ent::Node& node);
    const int stock_record_deal_comm(const ent::Node& node, const ent::Commodity& comm, int delta);
    const int stock_record_deal_mod(const ent::Node& node, const ent::Module& mod, int delta);
};

};

class Model{
private:
    int sense_of_life = 42;
    bool game_active_flag = false;
    std::unique_ptr<md::Inventory> inventory;
    std::unique_ptr<md::Navigation> navigation;
    std::unique_ptr<md::Trade> trade;
    int current_time;
    int current_balance;
public:
    std::string get_time();

    Model();
    int get_sense();
    bool is_game_active();
    void set_game_active(bool activity);

    void update_commodity(const ent::Commodity& comm, int delta){
        inventory->update_commodity(comm, delta);
    }
    const std::vector<std::pair<ent::Commodity, int>>& get_commodities(){
        return inventory->get_commodities();
    }
    void update_module(const ent::Module& comm, int delta){
        inventory->update_module(comm, delta);
    }
    const std::vector<std::pair<ent::Module, int>>& get_modules(){
        return inventory->get_modules();
    }

    void move_with_lane(const ent::Lane& lane){
        current_time += lane.traverse_time;
        navigation->move_with_lane(lane);
    }
    const ent::Node& get_current_node(){
        return navigation->get_current_node();
    }
    const std::vector<ent::Lane>& get_current_lanes(){
        return navigation->get_current_lanes();
    }

    void trade_module(const ent::Module& mod, int delta){
        // delta > 0 => buy from stock, sell otherwise
        if(inventory->have_enough_of_mod(mod, delta)){
            auto res = trade->stock_record_deal_mod(get_current_node(), mod, delta);
            LOG(INFO) << "Traded: got" + fmti(res) + "of " + fmti(mod.id);
            update_module(mod, res);
        }
    }

    void trade_commodity(const ent::Commodity& comm, int delta){
        if(inventory->have_enough_of_comm(comm, delta)){
            auto res = trade->stock_record_deal_comm(get_current_node(), comm, delta);
            LOG(INFO) << "Traded: got" + fmti(res) + "of " + fmti(comm.id);
            update_commodity(comm, res);
        }
    }

    md::Inventory& get_current_stock(){
        return trade->get_stock_for(get_current_node());
    }

    void load_game(int save_id);
    void save_game(std::string save_name);
};

#endif
