#include <string>
#include "database.hpp"
#include <utility>

#include "easyloggingpp/easylogging++.h"


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

template <class T>
void empty_output_check(std::vector<T>& v, std::string func){
    if(v.size() == 0){
        //TODO: exceptions?
        LOG(ERROR) << "empty db error in " + func + ", stopping...\n";
        exit(-1);
    }
}

template<typename T, typename M>
std::shared_ptr<std::vector<T>> parse_to_shared_vector(std::vector<M>& rows){
    auto result_ptr = std::make_shared<std::vector<T>>();
    for(auto& i: rows){
        result_ptr->push_back({i});
    }
    return result_ptr;
}

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

    empty_output_check(rows, "select_commodity");
    return parse_to_shared_vector<ent::Commodity>(rows);
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

    empty_output_check(rows, "select_module");
    return parse_to_shared_vector<ent::Module>(rows);
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

    empty_output_check(rows, "select_node");
    return parse_to_shared_vector<ent::Node>(rows);
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
    empty_output_check(rows, "select_lane");
    return parse_to_shared_vector<ent::Lane>(rows);
}

std::shared_ptr<std::vector<ent::Lane>> Connector::select_single_lane(const int id){
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
    empty_output_check(rows, "select_single_lane");
    return parse_to_shared_vector<ent::Lane>(rows);
}

int Connector::test_select_encounter(){
    auto rows = db::internal::storage.select(columns(&Encounter::id, &Encounter::name));

    return rows.size();
}

std::shared_ptr<std::vector<ent::Event>> Connector::select_encounter(){
    auto rows = db::internal::storage.select(
        columns(&Encounter::id, &Encounter::name, &Encounter::weight)
        );

    empty_output_check(rows, "select_encounter");
    return parse_to_shared_vector<ent::Event>(rows);
}

int Connector::test_select_mod_type(){
    auto rows = db::internal::storage.select(columns(&ModificatorType::id, &ModificatorType::name));

    return rows.size();
}

std::shared_ptr<std::vector<ent::LightModifier>> Connector::select_mod(){
    auto rows = db::internal::storage.select(
        columns(&Modificator::id, &Modificator::event_id)
        );
    empty_output_check(rows, "select_light_modifier");
    return parse_to_shared_vector<ent::LightModifier>(rows);
}

std::shared_ptr<std::vector<ent::Modifier>> Connector::select_mod_per_node(const int node_id){
    auto rows = db::internal::storage.select(
        columns(
            &Modificator::id, 
            &ModificatorType::id, &ModificatorType::name,
            &CommodityType::id, &CommodityType::name,
            &Modificator::order_delta,
            &Modificator::tech_delta),
        from<ModificatorLog>(),
        left_join<Modificator>(on(&ModificatorLog::mod_id) == c(&Modificator::id)),
        left_join<ModificatorType>(on(&Modificator::type_id) == c(&ModificatorType::id)),
        left_join<ModificatorType>(on(&Modificator::pref_id) == c(&CommodityType::id)),
        where(is_equal(&ModificatorLog::node_id, node_id))
        );
    empty_output_check(rows, "select mod per node");
    return parse_to_shared_vector<ent::Modifier>(rows);
}

std::shared_ptr<ent::VModifierLog> Connector::push_mod_log(ent::ModifierLog& log){
    db::internal::storage.insert(
        into<ModificatorLog>(),
        columns(&ModificatorLog::start_time, &ModificatorLog::node_id, &ModificatorLog::mod_id),
        values(std::make_tuple(log.time, log.node_id, log.mod_id))
    );
    auto rows = db::internal::storage.select(
        columns(log.time, &Node::name, &Modificator::name),
        where(is_equal(&Node::id, log.node_id) && is_equal(&Modificator::id, log.mod_id))
    );
    empty_output_check(rows, "select mod log");
    return std::make_shared<ent::VModifierLog>(rows[0]);
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
    LOG(INFO) << "saved as " + std::to_string(save_id[0]);
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