#ifndef DATABASE_H
#define DATABASE_H
#include "lancer.hpp"
#include "model/entities.hpp"
#include <memory>
#include <vector>

namespace db{

    class Connector{
        public:
            static const std::string db_name;
            static void sync();
            //TODO dummy realisations
            static int select_corporation();
            static std::shared_ptr<std::vector<ent::Commodity>> select_commodity();
            static int select_commodity_type();
            static int select_frame_class();
            static int select_frame();
            static int select_module_type();
            static int select_element();
            static int test_select_module();
            static std::shared_ptr<std::vector<ent::Module>> select_module();
            static int test_select_node();
            static std::shared_ptr<std::vector<ent::Node>> select_node();
            static int test_select_lane();
            static std::shared_ptr<std::vector<ent::Lane>> select_lane();
            static std::shared_ptr<std::vector<ent::Lane>> select_lane(const int id);
            static int test_select_encounter();
            static std::shared_ptr<std::vector<ent::Event>> select_encounter();
            static int select_mod_type();
            static int select_mod();
            static int select_mod_log();
            static std::shared_ptr<std::vector<ent::SavedGame>> select_saved_game();
            static std::shared_ptr<std::vector<std::pair<ent::Module, int>>> select_saved_module(const int id);
            static std::shared_ptr<std::vector<std::pair<ent::Commodity, int>>> select_saved_commodity(const int id);
            static void insert_save(
                std::string& save_name,
                const std::vector<std::pair<ent::Module, ent::Meta>>& modules,
                const std::vector<std::pair<ent::Commodity, ent::Meta>>& commodities
            );
            static void push_mod_log(ent::ModifierLog& log);
    };

}

#endif
