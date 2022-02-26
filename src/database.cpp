#include <string>
#include <database.hpp>
#include <lancer.hpp>
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
            Lane::get_table());
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

int Connector::select_commodity(){
    auto rows = db::internal::storage.select(columns(&Commodity::id, &Commodity::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_commodity_type(){
    auto rows = db::internal::storage.select(columns(&CommodityType::id, &CommodityType::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
}

int Connector::select_commodity_full(){
    auto comrows = db::internal::storage.select(
        columns(&Commodity::name, &CommodityType::name, &Corporation::name),
        join<Corporation>(on(c(&Commodity::corp_id) == &Corporation::id)),
        join<CommodityType>(on(c(&Commodity::type_id) == &CommodityType::id))
        );
    for(auto& i: comrows){
        cerr << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
    }
    return comrows.size();
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

int Connector::select_module(){
    auto rows = db::internal::storage.select(columns(&Module::id, &Module::name));
    for(auto& i: rows){
        cerr << get<0>(i) << " " << get<1>(i) << endl;
    }
    return rows.size();
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