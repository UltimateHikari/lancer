#include <string>
#include "database.hpp"
#include <iostream>
#include <utility>

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
            ModificatorLog::get_table(),
            SavedGame::get_table(),
            SavedCommodity::get_table(),
            SavedModule::get_table()
            );
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
    }
    return result_ptr;
}

int Connector::select_commodity_type(){
    auto rows = db::internal::storage.select(columns(&CommodityType::id, &CommodityType::name));

    return rows.size();
}

int Connector::select_frame_class(){
    auto rows = db::internal::storage.select(columns(&FrameClass::id, &FrameClass::name));

    return rows.size();
}

int Connector::select_frame(){
    auto rows = db::internal::storage.select(columns(&Frame::id, &Frame::name));

    return rows.size();
}

int Connector::select_module_type(){
    auto rows = db::internal::storage.select(columns(&ModuleType::id, &ModuleType::name));

    return rows.size();
}

int Connector::select_element(){
    auto rows = db::internal::storage.select(columns(&Element::id, &Element::name));

    return rows.size();
}

int Connector::test_select_module(){
    auto rows = db::internal::storage.select(columns(&Module::id, &Module::name));

    return rows.size();
}

std::shared_ptr<std::vector<ent::Module>> Connector::select_module(){
    auto rows = db::internal::storage.select(
        columns(&Module::id, &Module::type_id, &ModuleType::name, &Module::name),
        join<ModuleType>(on(c(&Module::type_id) == &ModuleType::id)));

    if(rows.size() == 0){
        //TODO: exceptions?
        cerr << "empty db error in select_module, stopping...\n";
        exit(-1);
    }

    auto result_ptr = std::make_shared<std::vector<ent::Module>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
    }
    return result_ptr;
}


int Connector::test_select_node(){
    auto rows = db::internal::storage.select(columns(&Node::id, &Node::name));

    return rows.size();
}

std::shared_ptr<std::vector<ent::Node>> Connector::select_node(){
    auto rows = db::internal::storage.select(
        columns(
            &Node::id, &Node::name, 
            &Node::pref_id, &CommodityType::name,
            &Node::corp_affinity, &Corporation::name,
            &Node::order_level, &Node::tech_level
            ),
        join<CommodityType>(on(c(&Node::pref_id) == &CommodityType::id)),
        join<Corporation>(on(c(&Node::corp_affinity) == &Corporation::id))
        );

    if(rows.size() == 0){
        //TODO: exceptions?
        cerr << "empty db error in select_node, stopping...\n";
        exit(-1);
    }

    auto result_ptr = std::make_shared<std::vector<ent::Node>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
    }
    return result_ptr;
}

int Connector::test_select_lane(){
    auto rows = db::internal::storage.select(columns(&Lane::id, &Lane::traverse_time));

    return rows.size();
}

std::shared_ptr<std::vector<ent::Lane>> Connector::select_lane(){
    using stt = alias_a<Node>;
    using end = alias_b<Node>;
    auto rows = db::internal::storage.select(
        columns(
            &Lane::id,
            &Lane::start, alias_column<stt>(&Node::name),
            &Lane::end, alias_column<end>(&Node::name),
            &Lane::traverse_time, &Lane::initial_stability
            ),
        left_join<stt>(on(alias_column<stt>(&Node::id) == c(&Lane::start))),
        left_join<end>(on(alias_column<end>(&Node::id) == c(&Lane::end)))
        );

    if(rows.size() == 0){
        //TODO: exceptions?
        cerr << "empty db error in select_lane, stopping...\n";
        exit(-1);
    }

    auto result_ptr = std::make_shared<std::vector<ent::Lane>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
    }
    return result_ptr;
}

std::shared_ptr<std::vector<ent::Lane>> Connector::select_lane(const int id){
    using stt = alias_a<Node>;
    using end = alias_b<Node>;
    auto rows = db::internal::storage.select(
        columns(
            &Lane::id,
            &Lane::start, alias_column<stt>(&Node::name),
            &Lane::end, alias_column<end>(&Node::name),
            &Lane::traverse_time, &Lane::initial_stability
            ),
        left_join<stt>(on(alias_column<stt>(&Node::id) == c(&Lane::start))),
        left_join<end>(on(alias_column<end>(&Node::id) == c(&Lane::end))),
        where(is_equal(&Lane::start, id) || is_equal(&Lane::end, id))
        );

    if(rows.size() == 0){
        //TODO: exceptions?
        cerr << "empty db error in select_lane, stopping...\n";
        exit(-1);
    }

    auto result_ptr = std::make_shared<std::vector<ent::Lane>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
    }
    return result_ptr;
}

int Connector::test_select_encounter(){
    auto rows = db::internal::storage.select(columns(&Encounter::id, &Encounter::name));

    return rows.size();
}

std::shared_ptr<std::vector<ent::Event>> Connector::select_encounter(){
    auto rows = db::internal::storage.select(
        columns(&Encounter::id, &Encounter::name, &Encounter::weight)
        );

    if(rows.size() == 0){
        //TODO: exceptions?
        cerr << "empty db error in select_enc, stopping...\n";
        exit(-1);
    }

    auto result_ptr = std::make_shared<std::vector<ent::Event>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
    }
    return result_ptr;
}

int Connector::select_mod_type(){
    auto rows = db::internal::storage.select(columns(&ModificatorType::id, &ModificatorType::name));

    return rows.size();
}

int Connector::select_mod(){
    auto rows = db::internal::storage.select(columns(&Modificator::id, &Modificator::name));

    return rows.size();
}

int Connector::select_mod_log(){
    auto rows = db::internal::storage.select(columns(&ModificatorLog::node_id, &ModificatorLog::mod_id));

    return rows.size();
}

std::shared_ptr<std::vector<ent::SavedGame>> Connector::select_saved_game(){
    auto rows = db::internal::storage.select(
        columns(&SavedGame::id, &SavedGame::name, &SavedGame::date));

    auto result_ptr = std::make_shared<std::vector<ent::SavedGame>>();
    for(auto& i: rows){
        result_ptr.get()->push_back({i});
    }
    return result_ptr;
}


std::shared_ptr<std::vector<std::pair<ent::Module,int>>> Connector::select_saved_module(const int id){
    auto rows = db::internal::storage.select(
        columns(&SavedModule::mod_id, &ModuleType::id, &ModuleType::name, &Module::name, &SavedModule::amount),
        join<Module>(on(c(&SavedModule::mod_id) == &Module::id)),
        join<ModuleType>(on(c(&Module::type_id) == &ModuleType::id)),
        where(c(&SavedModule::save_id) == id));
    auto result_ptr = std::make_shared<std::vector<std::pair<ent::Module,int>>>();
    for(auto& i: rows){
        ent::Module mod{i};
        result_ptr.get()->push_back(std::make_pair(mod, get<4>(i)));
    }
    return result_ptr;
}

std::shared_ptr<std::vector<std::pair<ent::Commodity,int>>> Connector::select_saved_commodity(const int id){
    auto rows = db::internal::storage.select(
        columns(&SavedCommodity::comm_id, &CommodityType::id, &CommodityType::name, &Commodity::name, &SavedCommodity::amount),
        join<Commodity>(on(c(&SavedCommodity::comm_id) == &Commodity::id)),
        join<CommodityType>(on(c(&Commodity::type_id) == &CommodityType::id)),
        where(c(&SavedCommodity::save_id) == id));

    auto result_ptr = std::make_shared<std::vector<std::pair<ent::Commodity,int>>>();
    for(auto& i: rows){
        ent::Commodity com{i};
        result_ptr.get()->push_back(std::make_pair(com, get<4>(i)));
    }
    return result_ptr;
}

void Connector::insert_save(
                std::string& save_name,
                const std::vector<std::pair<ent::Module, ent::Meta>>& modules,
                const std::vector<std::pair<ent::Commodity, ent::Meta>>& commodities
            )
{
    db::internal::storage.insert(
        into<SavedGame>(),
        columns(&SavedGame::name, &SavedGame::date),
        values(std::make_tuple(save_name, db::internal::storage.select(datetime("now", "localtime")).front()))
    );
    auto save_id = db::internal::storage.select(last_insert_rowid());
    cerr << "saved as " << save_id[0] << endl;
    for(auto& i : commodities){
        db::internal::storage.insert(
            into<SavedCommodity>(),
            columns(&SavedCommodity::save_id, &SavedCommodity::comm_id, &SavedCommodity::amount),
            values(std::make_tuple(save_id[0], i.first.id, i.second.amount))
        );
    }
    for(auto& i : modules){
        db::internal::storage.insert(
            into<SavedModule>(),
            columns(&SavedModule::save_id, &SavedModule::mod_id, &SavedModule::amount),
            values(std::make_tuple(save_id[0], i.first.id, i.second.amount))
        );
    }
}