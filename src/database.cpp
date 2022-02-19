#include <string>
#include <database.hpp>
#include <lancer.hpp>

namespace db{
    const auto storage = sqlite_orm::make_storage("lancer.db",
        Corporation::get_table(),
        Commodity::get_table(),
        CommodityType::get_table());
}

const std::string db::Connector::db_name = "lancer.db";

