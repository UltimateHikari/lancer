#include <random> 

#include "db/database.hpp"
#include "model/oututil.hpp"

#include "model/trade.hpp"

#include "easyloggingpp/easylogging++.h"

using namespace md;

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
