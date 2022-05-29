#include "model/model.hpp"

#include "db/database.hpp"
#include "model/oututil.hpp"

#include "easyloggingpp/easylogging++.h"


// ----- Model ----- //
using namespace md;

Model::Model():
    inventory(std::make_unique<Inventory>()),
    navigation(std::make_unique<Navigation>()),
    trade(std::make_unique<Trade>()),
    teller(std::make_unique<Storyteller>()),
    ship(std::make_unique<Ship>())
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

void Model::load_game(int save_id){
    inventory->load(save_id);
}
void Model::save_game(std::string save_name){
    inventory->save(save_name);
}

void Model::update_commodity(const ent::Commodity& comm, int delta){
    inventory->update_commodity(comm, delta, 0);
}
const std::vector<std::pair<ent::Commodity, ent::Meta>>& Model::get_commodities(){
    return inventory->get_commodities();
}
void Model::update_module(const ent::Module& comm, int delta){
    inventory->update_module(comm, delta, 0);
}
const std::vector<std::pair<ent::Module, ent::Meta>>& Model::get_modules(){
    return inventory->get_modules();
}

void Model::move_with_lane(const ent::Lane& lane){
    current_time += lane.traverse_time;
    auto dest_node_id =  navigation->move_with_lane(lane);
    last_log = *(teller->play_random_event(current_time, dest_node_id));
    // stock trim happens on get_current_stock
}

const ent::Node& Model::get_current_node(){
    return navigation->get_current_node();
}
const std::vector<ent::Lane>& Model::get_current_lanes(){
    return navigation->get_current_lanes();
}

void Model::trade_module(const ent::Module& mod, int delta){
    // delta > 0 => buy from stock, sell otherwise
    if(inventory->have_enough_of_mod(mod, delta)){
        auto res = trade->stock_record_deal_mod(get_current_node(), mod, delta, current_balance);
        LOG(INFO) << "Traded: got" + fmti(res) + "of " + fmti(mod.id);
        update_module(mod, res);
        current_balance -= res*trade->get_mod_price(get_current_node(), mod);
    }
}

void Model::trade_commodity(const ent::Commodity& comm, int delta){
    if(inventory->have_enough_of_comm(comm, delta)){
        auto res = trade->stock_record_deal_comm(get_current_node(), comm, delta, current_balance);
        LOG(INFO) << "Traded: got" + fmti(res) + "of " + fmti(comm.id);
        update_commodity(comm, res);
        current_balance -= res*trade->get_comm_price(get_current_node(), comm);
    }
}

md::Inventory& Model::get_current_stock(){
    return trade->get_stock_for(get_current_node());
}

std::vector<ent::Module>& Model::get_equipped_modules(){
    return ship->equipped;
}
void Model::equip_module(ent::Module& mod){
    if(ship->can_equip_another(mod) && inventory->have_enough_of_mod(mod, 1)){
        ship->equip(mod);
        inventory->update_module(mod, -1, mod.price);
    }
}
void Model::unequip_module(ent::Module& mod){
    if(!ship_inventory_full()){
        auto uneq_mod = ship->unequip(mod);
        inventory->update_module(uneq_mod, 1, mod.price);
    }
}
ent::ShipFrame& Model::get_frame(){
    return *(ship->frame);
}

bool Model::ship_inventory_full(){
    return ship->frame->params.inventory <= inventory->get_size();
}
