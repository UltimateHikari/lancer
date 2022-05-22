#ifndef LANCER_MODEL_TRADE_HPP
#define LANCER_MODEL_TRADE_HPP

#include <deque>

#include "model/inventory.hpp"

namespace md{

class Trade{
private: 
    std::deque<std::pair<int, std::shared_ptr<Inventory>>> cached_stocks;
    std::shared_ptr<Inventory> generate_stock(const ent::Node& node);
    std::shared_ptr<std::vector<int>> get_weights(
        std::shared_ptr<std::vector<ent::Commodity>> comms,
        ent::CommodityType pref
    );
    static const int STOCK_MEM = 3;
    static const int PREF_WEIGHT = 5;
    static const int WEIGHT = 1;
    static const int LEVEL_AMOUNT = 5;
public: 
    
    Inventory& get_stock_for(const ent::Node& node);
    const int stock_record_deal_comm(const ent::Node& node, const ent::Commodity& comm, int delta, int balance);
    const int stock_record_deal_mod(const ent::Node& node, const ent::Module& mod, int delta, int balance);
    int get_comm_price(const ent::Node& node, const ent::Commodity& comm);
    int get_mod_price(const ent::Node& node, const ent::Module& mod);
};

}

#endif
