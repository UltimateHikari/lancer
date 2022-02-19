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
        std::string name;

        static auto get_table(){
            using namespace sqlite_orm;
            return make_table(
                "commodity",
                make_column("id", &Commodity::id, primary_key()),
                make_column("type_id", &Commodity::type_id),
                make_column("manufacturer_id", &Commodity::corp_id),
                make_column("name", &Commodity::name)
            );
        }
};

#endif