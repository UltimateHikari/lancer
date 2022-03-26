#include <string>
#include "database.hpp"
#include <iostream>

namespace db{
    namespace internal{
        auto storage = sqlite_orm::make_storage("lancer.db",
            Corporation::get_table(),
            Commodity::get_table(),
            CommodityType::get_table(),
            FrameClass::get_table(),
            Frame::get_table(),
            ModuleType::get_table(),
            Element::get_table(),
            Module::get_table(),
            Node::get_table(),
            Lane::get_table(),
            Encounter::get_table(),
            ModificatorType::get_table(),
            Modificator::get_table(),
            ModificatorLog::get_table());
    }
}

using namespace db;
using namespace sqlite_orm;

using std::get;
using std::cerr;
using std::endl;

const std::string Connector::db_name = "lancer.db";

void Connector::sync(){
    db::internal::storage.sync_schema();
}

int Connector::select_corporation(){
    auto rows = db::internal::storage.select(columns(&Corporation::id, &Corporation::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

std::shared_ptr<std::vector<ent::Commodity>> Connector::select_commodity(){
    auto rows = db::internal::storage.select(
        columns(&Commodity::id, &CommodityType::id, &CommodityType::name, &Commodity::name),
        join<CommodityType>(on(c(&Commodity::type_id) == &CommodityType::id)));

    if(rows.size() == 0){
        //TODO: exceptions?
        cerr << "empty db error in select_commodity, stopping...\n";
        exit(-1);
    }

    auto result_ptr = std::make_shared<std::vector<ent::Commodity>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
        cerr << get<0>(i) << " " << get<2>(i) << " " << get<3>(i) << endl;
    }
    return result_ptr;
}

int Connector::select_commodity_type(){
    auto rows = db::internal::storage.select(columns(&CommodityType::id, &CommodityType::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_frame_class(){
    auto rows = db::internal::storage.select(columns(&FrameClass::id, &FrameClass::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_frame(){
    auto rows = db::internal::storage.select(columns(&Frame::id, &Frame::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_module_type(){
    auto rows = db::internal::storage.select(columns(&ModuleType::id, &ModuleType::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_element(){
    auto rows = db::internal::storage.select(columns(&Element::id, &Element::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::test_select_module(){
    auto rows = db::internal::storage.select(columns(&Module::id, &Module::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

std::shared_ptr<std::vector<ent::Module>> Connector::select_module(){
    auto rows = db::internal::storage.select(
        columns(&Module::id, &ModuleType::id, &ModuleType::name, &Module::name),
        join<ModuleType>(on(c(&Module::type_id) == &ModuleType::id)));

    if(rows.size() == 0){
        //TODO: exceptions?
        cerr << "empty db error in select_module, stopping...\n";
        exit(-1);
    }

    auto result_ptr = std::make_shared<std::vector<ent::Module>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
        cerr << get<0>(i) << " " << get<2>(i) << " " << get<3>(i) << endl;
    }
    return result_ptr;
}


int Connector::select_node(){
    auto rows = db::internal::storage.select(columns(&Node::id, &Node::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_lane(){
    auto rows = db::internal::storage.select(columns(&Lane::id, &Lane::traverse_time));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_encounter(){
    auto rows = db::internal::storage.select(columns(&Encounter::id, &Encounter::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_mod_type(){
    auto rows = db::internal::storage.select(columns(&ModificatorType::id, &ModificatorType::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_mod(){
    auto rows = db::internal::storage.select(columns(&Modificator::id, &Modificator::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_mod_log(){
    auto rows = db::internal::storage.select(columns(&ModificatorLog::node_id, &ModificatorLog::mod_id));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}