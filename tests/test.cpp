#include <gtest/gtest.h>
#include <lancer.hpp>

using namespace sqlite_orm;


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(SelectTest, Corporation)  {
    auto storage = make_storage("lancer.db",
        Corporation::get_table(),
        Commodity::get_table(),
        CommodityType::get_table());
    storage.sync_schema();

    auto rows = storage.select(columns(&Corporation::id, &Corporation::name));
    EXPECT_EQ(rows.size(),1);
}

TEST(SelectTest, Commodity)  {
    auto storage = make_storage("lancer.db",
        Corporation::get_table(),
        Commodity::get_table(),
        CommodityType::get_table());
    storage.sync_schema();

    auto rows1 = storage.select(columns(&Commodity::id, &Commodity::name));
    EXPECT_EQ(rows1.size(),3);
}

TEST(SelectTest, Commodity_type)  {
    auto storage = make_storage("lancer.db",
        Corporation::get_table(),
        Commodity::get_table(),
        CommodityType::get_table());
    storage.sync_schema();

    auto rows2 = storage.select(columns(&CommodityType::id, &CommodityType::name));
    EXPECT_EQ(rows2.size(),5);
}

TEST(SelectTest, Commodity_full)  {
    auto storage = make_storage("lancer.db",
        Corporation::get_table(),
        Commodity::get_table(),
        CommodityType::get_table());
    storage.sync_schema();

    auto comrows = storage.select(
        columns(&Commodity::name, &CommodityType::name, &Corporation::name),
        join<Corporation>(on(c(&Commodity::corp_id) == &Corporation::id)),
        join<CommodityType>(on(c(&Commodity::type_id) == &CommodityType::id))
        );
    EXPECT_EQ(comrows.size(),5);
}
