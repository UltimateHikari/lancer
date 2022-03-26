#include <gtest/gtest.h>
#include <database.hpp>
#include "model/model.hpp"

using namespace sqlite_orm;

TEST(SelectTest, Corporation)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_corporation(), 1);
}

TEST(SelectTest, Commodity)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_commodity().get()->size(), 3);
}

TEST(SelectTest, Commodity_type)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_commodity_type(), 5);
}

TEST(SelectTest, FrameClass)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_frame_class(), 6);
}

TEST(SelectTest, Frame)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_frame(), 1);
}

TEST(SelectTest, ModuleType)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_module_type(), 3);
}

TEST(SelectTest, Element)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_element(), 3);
}

TEST(SelectTest, ModuleTest)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::test_select_module(), 3);
}

TEST(SelectTest, Module)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_module().get()->size(), 3);
}

TEST(SelectTest, Node)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_node(), 3);
}

TEST(SelectTest, Lane)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_lane(), 1);
}

TEST(SelectTest, Encounter)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_encounter(), 6);
}

TEST(SelectTest, ModificatorType)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_mod_type(), 3);
}

TEST(SelectTest, Modificator)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_mod(), 1);
}

TEST(SelectTest, ModificatorLog)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_mod_log(), 0);
}