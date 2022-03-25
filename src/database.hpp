#ifndef DATABASE_H
#define DATABASE_H
#include "lancer.hpp"
#include "model/entities.hpp"

namespace db{

    class Connector{
        public:
            static const std::string db_name;
            static void sync();
            //TODO dummy realisations
            static int select_corporation();
            static ent::Commodity select_commodity();
            static int select_commodity_type();
            static int select_commodity_full();
            static int select_frame_class();
            static int select_frame();
            static int select_module_type();
            static int select_element();
            static int select_module();
            static int select_node();
            static int select_lane();
            static int select_encounter();
            static int select_mod_type();
            static int select_mod();
            static int select_mod_log();
    };

}

#endif
