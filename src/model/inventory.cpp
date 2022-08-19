#include "db/database.hpp"

#include "model/entities.hpp"

#include "model/inventory.hpp"

using namespace md;


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

int Inventory::get_size(){
    return modules.get_size() + commodities.get_size();
}

int Inventory::get_amount_of_commodity(const ent::Commodity& comm){
    return commodities.get_amount_of(comm);
}
int Inventory::get_amount_of_module(const ent::Module& mod){
    return modules.get_amount_of(mod);
}