#include <gtest/gtest.h>
#include <database.hpp>

using namespace sqlite_orm;


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(SelectTest, Corporation)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_corporation(), 1);
}

TEST(SelectTest, Commodity)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_commodity(), 3);
}

TEST(SelectTest, Commodity_type)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_commodity_type(), 5);
}

TEST(SelectTest, Commodity_full)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_commodity_full(), 3);
}
