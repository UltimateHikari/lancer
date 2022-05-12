#include "model/model.hpp"
#include "db/database.hpp"
#include <ctime> // time, localtime
#include <iomanip> // put_time
#include <algorithm> // copy
#include <random> 

#include "easyloggingpp/easylogging++.h"


// ----- Model ----- //
using namespace md;

Model::Model():
    inventory(std::make_unique<Inventory>()),
    navigation(std::make_unique<Navigation>()),
    trade(std::make_unique<Trade>()),
    teller(std::make_unique<Storyteller>())
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

// std::string Model::get_time(){
//     auto t = std::time(nullptr);
//     auto tm = *std::localtime(&t);

//     std::ostringstream oss;
//     oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

//     return oss.str();
// }

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
    teller->play_random_event(current_time, dest_node_id);
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

// ----- Subinventory ----- //

template<class T>
SubInventory<T>::SubInventory(): 
    inventory_state(0), 
    snapshot_state(0)
{}

template<class T>
void SubInventory<T>::update(const T& t, int delta, int price){
    mutex.lock();
    inventory[t].amount += delta;
    inventory[t].price = price; // non-zero only on init?
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


// ----- Inventory ----- //

void Inventory::update_commodity(const ent::Commodity& comm, int delta, int price){
    commodities.update(comm, delta, price);
}
std::vector<std::pair<ent::Commodity, ent::Meta>>& Inventory::get_commodities(){
    return commodities.get();
}
void Inventory::update_module(const ent::Module& mod, int delta, int price){
    modules.update(mod, delta, price);
}
std::vector<std::pair<ent::Module, ent::Meta>>& Inventory::get_modules(){
    return modules.get();
}

bool Inventory::have_enough_of_comm(const ent::Commodity& t, int delta){
    return commodities.have_enough_of(t,delta);
}
bool Inventory::have_enough_of_mod(const ent::Module& t, int delta){
    return modules.have_enough_of(t,delta);
}

void Inventory::load(int save_id){
    auto commodities = db::Connector::select_saved_commodity(save_id);
    auto modules = db::Connector::select_saved_module(save_id);
    for(auto& i: *(modules.get())){
        update_module(i.first, i.second, 0);
    }
    for(auto& i: *(commodities.get())){
        update_commodity(i.first, i.second, 0);
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

int Navigation::move_with_lane(const ent::Lane& lane){
    LOG(INFO) << "moving from node : " + fmti(current_node_id);
    current_node_id = (current_node_id == lane.end.id ? lane.start.id : lane.end.id);
    LOG(INFO) << "moved to node    : " + fmti(current_node_id);
    return current_node_id;
}

const ent::Node& Navigation::get_current_node(){
    if(cached_node.id != current_node_id){
        cached_node = refresh_node();
    }
    return cached_node;

}
const std::vector<ent::Lane>& Navigation::get_current_lanes(){
    if(current_lanes_id != current_node_id){
        cached_lanes = db::Connector::select_single_lane(current_node_id);
        current_lanes_id = current_node_id;
    }
    return *(cached_lanes.get());
}

float order_mod(int order){
    return 4 - 3*order/5.0;
}

std::shared_ptr<std::vector<int>> Trade::get_weights(
    std::shared_ptr<std::vector<ent::Commodity>> comms,
    ent::CommodityType pref
){
    int pref_weight = Trade::PREF_WEIGHT;
    int usual_weight = Trade::WEIGHT;
    auto res = std::make_shared<std::vector<int>>();
    for(auto& i : *comms){
        if(i.type.id == pref.id){
            res->push_back(pref_weight);
        }else{
            res->push_back(usual_weight);
        }
    }
    return res;
}

std::shared_ptr<Inventory> Trade::generate_stock(const ent::Node& node){
    auto inv = std::make_shared<Inventory>();
    auto dbcomms = db::Connector::select_commodity();
    auto weights = get_weights(dbcomms, node.pref);
    int amount = Trade::LEVEL_AMOUNT*node.tech_level;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::discrete_distribution<> dist(weights->begin(), weights->end());

    for(int i = 0; i < amount; i++){
        const ent::Commodity& rand_comm = (*dbcomms)[dist(mt)];
        inv.get()->update_commodity(rand_comm, 1, (int)(rand_comm.price*order_mod(node.order_level)));
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
    if(cached_stocks.size() > Trade::STOCK_MEM){
        cached_stocks.pop_back();
        LOG(INFO) << "Stock popped";
    }
    return *(it->second.get());
}

int Trade::get_comm_price(const ent::Node& node, const ent::Commodity& comm){
    auto comd = get_stock_for(node).get_commodities();
    return std::find_if(comd.begin(), comd.end(), 
        [&](const auto& p){return p.first.id == comm.id;})->second.price;
}
int Trade::get_mod_price(const ent::Node& node, const ent::Module& mod){
    auto modd = get_stock_for(node).get_modules();
    // iterator is always here
    return std::find_if(modd.begin(), modd.end(), 
        [&](const auto& p){return p.first.id == mod.id;})->second.price;
}

const int Trade::stock_record_deal_comm(const ent::Node& node, const ent::Commodity& comm, int delta, int balance){
    int stock_delta = (-1)*delta;
    int res_delta = 0;

    //TODO extapolate for situation with > 1 buys:
    if(balance < get_comm_price(node, comm) && delta > 0){
        return 0;
    }

    if(get_stock_for(node).have_enough_of_comm(comm, stock_delta)){
        get_stock_for(node).update_commodity(comm, stock_delta, 0);
        res_delta = delta;
    }
    return res_delta;
}
const int Trade::stock_record_deal_mod(const ent::Node& node, const ent::Module& mod, int delta, int balance){
    int stock_delta = (-1)*delta;
    int res_delta = 0;

    
    //TODO extapolate for situation with > 1 buys:
    if(balance < get_mod_price(node, mod) && delta > 0){
        return 0;
    }

    if(get_stock_for(node).have_enough_of_mod(mod, stock_delta)){
        get_stock_for(node).update_module(mod, stock_delta, 0);
        res_delta = delta;
    }
    return res_delta;
}

// ----- Teller ----- //

Storyteller::Storyteller(){
    auto evt = db::Connector::select_encounter();
    auto mods = db::Connector::select_mod();
    for(auto& m : *(mods.get())){
        auto key_ptr = std::find_if(
            evt.get()->begin(), evt.get()->end(),
            [&](const auto& p){return p.id == m.event_id;}
            );
        if(key_ptr != evt.get()->end()){
            events[*key_ptr] = m.id;
            LOG(INFO) << "teller noted event-id: " << key_ptr->id << " with mod-id " << m.id;
        }
    }
    transform(events.begin(), events.end(), std::back_inserter(weights),
         [](const auto& val){return val.first.weight;} 
         );
    LOG(INFO) << "tellers event weights:";
    for(auto& i : weights){
        LOG(INFO) << i;
    }
}

int Storyteller::get_random_modifier(){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    int ind = dist(mt);

    LOG(INFO) << "teller chose " << ind;
    
    // index = id, assuming continioius id in table
    // return events[ind].id;
    // TODO rewrite map to vector, now it works only because event.id = mod.id
    return ind;
}

void Storyteller::log_modifier(int time, int node_id, int mod_id){
    LOG(INFO) << "teller got mod: " << mod_id << " on node: " << node_id;
    ent::ModifierLog log{time, node_id, mod_id};
    db::Connector::push_mod_log(log);
}

void Storyteller::play_random_event(int time, int node_id){
    log_modifier(time, node_id, get_random_modifier());
}
void Storyteller::play_event(int time, int node_id, ent::Event& e){
    //TODO event may not reside in events
    log_modifier(time, node_id, events[e]);
}