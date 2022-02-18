#include <gtest/gtest.h>
#include <lancer.hpp>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(SelectTest, BasicSelects)  {
    auto storage = make_storage("lancer.db",
        Corporation::get_table(),
        Commodity::get_table(),
        CommodityType::get_table());
    cerr << "lancer opened" << endl;
    storage.sync_schema();

    auto rows = storage.select(columns(&Corporation::id, &Corporation::name));
    EXPECT_EQ(rows.size(),1);

    auto rows1 = storage.select(columns(&Commodity::id, &Commodity::name));
    EXPECT_EQ(rows1.size(),3);

    auto rows2 = storage.select(columns(&CommodityType::id, &CommodityType::name));
    EXPECT_EQ(rows2.size(),5);

    auto comrows = storage.select(
        columns(&Commodity::name, &CommodityType::name, &Corporation::name),
        join<Corporation>(on(c(&Commodity::corp_id) == &Corporation::id)),
        join<CommodityType>(on(c(&Commodity::type_id) == &CommodityType::id))
        );
    EXPECT_EQ(rows2.size(),5);
}
