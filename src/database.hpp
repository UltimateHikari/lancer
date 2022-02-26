#ifndef DATABASE_H
#define DATABASE_H
#include "lancer.hpp"


namespace db{

    class Connector{
        public:
            static const std::string db_name;
            static void sync();
            //TODO dummy realisations
            static int select_corporation();
            static int select_commodity();
            static int select_commodity_type();
            static int select_commodity_full();
            static int select_frame_class();
            static int select_frame();
    };

}

#endif
