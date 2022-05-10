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
    std::map<T, ent::Meta> inventory;
    std::vector<std::pair<T, ent::Meta>> snapshot;
    void repopulate_snapshot();
public: 
    SubInventory();
    void update(const T& t, int delta, int price);
    std::vector<std::pair<T, ent::Meta>>& get();
    bool have_enough_of(const T& t, int delta);
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
    int move_with_lane(const ent::Lane& lane);
    const ent::Node& get_current_node();
    const std::vector<ent::Lane>& get_current_lanes();
};

class Trade{
private: 
    std::deque<std::pair<int, std::shared_ptr<Inventory>>> cached_stocks;
    std::shared_ptr<Inventory> generate_stock(const ent::Node& node);
public: 
    Inventory& get_stock_for(const ent::Node& node);
    const int stock_record_deal_comm(const ent::Node& node, const ent::Commodity& comm, int delta, int balance);
    const int stock_record_deal_mod(const ent::Node& node, const ent::Module& mod, int delta, int balance);
    int get_comm_price(const ent::Node& node, const ent::Commodity& comm);
    int get_mod_price(const ent::Node& node, const ent::Module& mod);
};

class Storyteller { //TODO - init with modifs in db, write tests for modifs
private:
    std::map<ent::Event, int> events;
    int get_random_modifier();
    static const int TELLER_MAX_WEIGHT = 10;
    void log_modifier(int time, int node_id, int mod_id);
public: 
    void put_event(ent::Event& e, int mod_id);
    void play_random_event(int time, int node_id);
    void play_event(int time, int node_id, ent::Event& e);
};

};

class Model{
private:
    int sense_of_life = 42;
    bool game_active_flag = false;
    std::unique_ptr<md::Inventory> inventory;
    std::unique_ptr<md::Navigation> navigation;
    std::unique_ptr<md::Trade> trade;
    std::unique_ptr<md::Storyteller> teller;
    int current_time = 0;
    int current_balance = 500;
public:
    int get_time(){
        return current_time;
    };

    int get_balance(){
        return current_balance;
    };

    Model();
    int get_sense();
    bool is_game_active();
    void set_game_active(bool activity);

    void update_commodity(const ent::Commodity& comm, int delta);
    const std::vector<std::pair<ent::Commodity, ent::Meta>>& get_commodities();
    void update_module(const ent::Module& comm, int delta);
    const std::vector<std::pair<ent::Module, ent::Meta>>& get_modules();

    void move_with_lane(const ent::Lane& lane);
    const ent::Node& get_current_node();
    const std::vector<ent::Lane>& get_current_lanes();

    void trade_module(const ent::Module& mod, int delta);
    void trade_commodity(const ent::Commodity& comm, int delta);
    md::Inventory& get_current_stock();

    void load_game(int save_id);
    void save_game(std::string save_name);
};

#endif
