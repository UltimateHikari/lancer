#ifndef LANCER_ENTITY
#define LANCER_ENTITY
#include <string>

class Corporation{
    public:
        int id;
        std::string name;

        static auto get_table();
};

class CommodityType {
    public:
        int id;
        std::string name;

        static auto get_table();
};

class Commodity {
    public:
        int id;
        int type_id;
        int corp_id;
        std::string name;

        static auto get_table();
};

#endif