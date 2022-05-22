#ifndef LANCER_ENTITY
#define LANCER_ENTITY
#include <string>
#include <sqlite_orm/sqlite_orm.h>

class Corporation{
    public:
        int id;
        std::string name;

        static auto get_table(){
            using namespace sqlite_orm;
            return make_table(
                "corporation",
                make_column("id", &Corporation::id, primary_key()),
                make_column("name", &Corporation::name)
            );
        }
};

class CommodityType {
    public:
        int id;
        std::string name;

        static auto get_table(){
            using namespace sqlite_orm;
            return make_table(
                "commodity_type",
                make_column("id", &CommodityType::id, primary_key()),
                make_column("name", &CommodityType::name)
            );
        }
};

class Commodity {
    public:
        int id;
        int type_id;
        int corp_id;
        int initial_cost;
        std::string name;

        static auto get_table(){
            using namespace sqlite_orm;
            return make_table(
                "commodity",
                make_column("id", &Commodity::id, primary_key()),
                make_column("type_id", &Commodity::type_id),
                make_column("manufacturer_id", &Commodity::corp_id),
                make_column("initial_cost", &Commodity::initial_cost),
                make_column("name", &Commodity::name)
            );
        }
};

class FrameClass {
    public:
        int id;
        std::string name;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "frame_class",
            make_column("id", &FrameClass::id, primary_key()),
            make_column("name", &FrameClass::name)
        );
    }
};

class Frame {
    public:
        int id;
        int class_id;
        int corp_id;

        int weap_slots;
        int armr_slots;
        int supp_slots;

        int energy;
        int inventory;

        int structure;
        int speed;
        int evasion;

        std::string name;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "frame",
            make_column("id", &Frame::id, primary_key()),
            make_column("class_id", &Frame::class_id),
            make_column("manufacturer_id", &Frame::corp_id),
            make_column("weap_slots", &Frame::weap_slots),
            make_column("armr_slots", &Frame::armr_slots),
            make_column("supp_slots", &Frame::supp_slots),

            make_column("energy", &Frame::energy),
            make_column("inventory_size", &Frame::inventory),

            make_column("structure_points", &Frame::structure),
            make_column("speed", &Frame::speed),
            make_column("evasion", &Frame::evasion),
            make_column("name", &Frame::name)
        );
    }
};

class ModuleType {
    public:
        int id;
        std::string name;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "module_type",
            make_column("id", &ModuleType::id, primary_key()),
            make_column("name", &ModuleType::name)
        );
    }
};

class Element {
    public:
        int id;
        std::string name;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "element",
            make_column("id", &Element::id, primary_key()),
            make_column("name", &Element::name)
        );
    }
};

class Module {
    public:
        int id;
        int type_id;
        int corp_id;

        int element_id;
        int energy_cost;
        int initial_cost;

        int damage;
        int accuracy;
        int cooldown;

        int structure;
        int speed;
        int evasion;
        int energy;
        int inventory;
        int drill_profit;

        std::string name;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "module",
            make_column("id", &Module::id, primary_key()),
            make_column("name", &Module::name),
            make_column("type_id", &Module::type_id),
            make_column("manufacturer_id", &Module::corp_id),
            make_column("element_id", &Module::element_id),
            make_column("energy_cost", &Module::energy_cost),
            make_column("initial_cost", &Module::initial_cost),

            make_column("damage", &Module::damage),
            make_column("accuracy", &Module::accuracy),
            make_column("cooldown", &Module::cooldown),

            make_column("structure_points", &Module::structure),
            make_column("speed_modifier", &Module::speed),
            make_column("evasion_modifier", &Module::evasion),
            make_column("energy_modifier", &Module::energy),
            make_column("inventory_modifier", &Module::inventory),
            make_column("drill_profit_modifier", &Module::drill_profit)
        );
    }

};


class Node {
    public:
        int id;
        std::string name;

        int pref_id;
        int corp_affinity;
        int order_level;
        int tech_level;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "node",
            make_column("id", &Node::id, primary_key()),
            make_column("name", &Node::name),
            make_column("pref_id", &Node::pref_id),
            make_column("corp_affinity", &Node::corp_affinity),
            make_column("order_level", &Node::order_level),
            make_column("tech_level", &Node::tech_level)
        );
    }
};

class Lane {
    public:
        int id;
        int start;
        int end;
        int traverse_time;
        bool initial_stability;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "lane",
            make_column("id", &Lane::id, primary_key()),
            make_column("start_node_id", &Lane::start),
            make_column("end_node_id", &Lane::end),
            make_column("traverse_time", &Lane::traverse_time),
            make_column("initial_stability", &Lane::initial_stability)
        );
    }
};

class Encounter {
    public:
        int id;
        int weight;
        std::string name;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "encounter",
            make_column("id", &Encounter::id, primary_key()),
            make_column("name", &Encounter::name),
            make_column("weight", &Encounter::weight)
        );
    }
};

class ModificatorType {
    public:
        int id;
        std::string name;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "modificator_type",
            make_column("id", &ModificatorType::id, primary_key()),
            make_column("name", &ModificatorType::name)
        );
    }
};

class Modificator {
    public:
        int id;
        int type_id;
        int event_id;
        std::string name;
        int pref_id;
        int order_delta;
        int tech_delta;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "modificator",
            make_column("id", &Modificator::id, primary_key()),
            make_column("name", &Modificator::name),
            make_column("type_id", &Modificator::type_id),
            make_column("pref_id", &Modificator::pref_id),
            make_column("encounter_id", &Modificator::event_id),
            make_column("order_delta", &Modificator::order_delta),
            make_column("tech_delta", &Modificator::tech_delta)
        );
    }
};

class ModificatorLog {
    public:
        int start_time;
        int node_id;
        int mod_id;

    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "modificator_log",
            make_column("start_time", &ModificatorLog::start_time),
            make_column("node_id", &ModificatorLog::node_id),
            make_column("mod_id", &ModificatorLog::mod_id)
        );
    }
};

class SavedGame{
    public:
        int id;
        std::string name;
        std::string date;
    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "saved_game",
            make_column("id", &SavedGame::id, primary_key()),
            make_column("name", &SavedGame::name),
            make_column("date", &SavedGame::date)
        );
    }
};

class SavedCommodity{
    public:
        int save_id;
        int comm_id;
        int amount;
    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "saved_commodities",
            make_column("save_id", &SavedCommodity::save_id),
            make_column("comm_id", &SavedCommodity::comm_id),
            make_column("amount", &SavedCommodity::amount),
            primary_key(&SavedCommodity::save_id, &SavedCommodity::comm_id)
        );
    }
};

class SavedModule{
    public:
        int save_id;
        int mod_id;
        int amount;
    static auto get_table(){
        using namespace sqlite_orm;
        return make_table(
            "saved_modules",
            make_column("save_id", &SavedModule::save_id),
            make_column("mod_id", &SavedModule::mod_id),
            make_column("amount", &SavedModule::amount),
            primary_key(&SavedModule::save_id, &SavedModule::mod_id)
        );
    }
};


#endif