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
        int manufacturer_id;

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
            make_column("manufacturer_id", &Frame::manufacturer_id),
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

#endif