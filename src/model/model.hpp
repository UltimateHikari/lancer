#ifndef LANCER_MODEL_HPP
#define LANCER_MODEL_HPP

#include <string>
#include <vector>

#include "model/entities.hpp"

#include "model/inventory.hpp"
#include "model/navigation.hpp"
#include "model/trade.hpp"
#include "model/teller.hpp"
#include "model/ship.hpp"
#include "model/battles.hpp"

#include "easyloggingpp/easylogging++.h"

class Model{
private:
    int sense_of_life = 42;
    bool game_active_flag = false;
    std::unique_ptr<md::Inventory> inventory;
    std::unique_ptr<md::Navigation> navigation;
    std::unique_ptr<md::Trade> trade;
    std::unique_ptr<md::Storyteller> teller;
    std::unique_ptr<md::Ship> ship;
    int current_time = 0;
    int current_balance = 500;
    int battles_won = 0;
    static const int MINE_CREDITS = 10;
    static const int MINE_DAYS = 10;
    static const int MINE_LEFT = 5;
    static const int VICTORY_CREDITS = 100000;
    static const int VICTORY_BATTLES = 20;
    int mines_left = MINE_LEFT;
public:
    ent::VModifierLog last_log = {};
    int get_time(){
        return current_time;
    };

    int get_balance(){
        return current_balance;
    };

    int get_battles_won(){
        return battles_won;
    };

    Model();
    int get_sense();
    bool is_game_active();
    bool is_victory_achieved();
    void cheat_victory();
    void set_game_active(bool activity);

    void update_commodity(const ent::Commodity& comm, int delta);
    const std::vector<std::pair<ent::Commodity, ent::Meta>>& get_commodities();
    void update_module(const ent::Module& comm, int delta);
    const std::vector<std::pair<ent::Module, ent::Meta>>& get_modules();

    md::BattleResult move_with_lane(const ent::Lane& lane);
    const ent::Node& get_current_node();
    const std::vector<ent::Lane>& get_current_lanes();
    void do_mine();

    void trade_module(const ent::Module& mod, int delta);
    void trade_commodity(const ent::Commodity& comm, int delta);
    md::Inventory& get_current_stock();

    std::vector<ent::Module>& get_equipped_modules();
    void equip_module(ent::Module& mod);
    void unequip_module(ent::Module& mod);
    ent::ShipFrame& get_frame();
    bool ship_inventory_full();

    void load_game(int save_id);
    void save_game(std::string save_name);
};

#endif
