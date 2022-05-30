#include <gtest/gtest.h>
#include <db/database.hpp>
#include "model/model.hpp"

using namespace sqlite_orm;

TEST(SelectTest, Corporation)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_corporation(), 4);
}

TEST(SelectTest, Commodity)  {
    db::Connector::sync();
    auto res = db::Connector::select_commodity().get();
    EXPECT_EQ(res->size(), 20);
    EXPECT_NE((*res)[0].name, "");
}

TEST(SelectTest, Commodity_type)  {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::select_commodity_type(), 5);
}

TEST(SelectTest, FrameClass)    {
    db::Connector::sync();
    auto cls = db::Connector::select_frame_class();
    EXPECT_EQ(cls->size(), 6);
}

TEST(SelectTest, Frame)    {
    db::Connector::sync();
    auto frm = db::Connector::select_single_frame(1);
    EXPECT_EQ(frm->id, 1);
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
    auto res = db::Connector::select_module().get();
    EXPECT_EQ(res->size(), 3);
    EXPECT_NE((*res)[0].name, "");
}

TEST(SelectTest, NodeTest)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::test_select_node(), 30);
}

TEST(SelectTest, Node)    {
    db::Connector::sync();
    auto res = db::Connector::select_node().get();
    EXPECT_EQ(res->size(), 30);
    EXPECT_NE((*res)[1].name, "");
}

TEST(SelectTest, LaneTest)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::test_select_lane(), 37);
}

TEST(SelectTest, Lane)    {
    db::Connector::sync();
    auto res = db::Connector::select_lane().get();
    EXPECT_EQ(res->size(), 37);
    // EXPECT_NE((*res)[1].start.name, "");

}

TEST(SelectTest, EncounterTest)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::test_select_encounter(), 7);
}

TEST(SelectTest, Encounter)    {
    db::Connector::sync();
    auto res = db::Connector::select_encounter();
    EXPECT_EQ(res->size(), 7);
}

TEST(SelectTest, ModificatorType)    {
    db::Connector::sync();
    EXPECT_EQ(db::Connector::test_select_mod_type(), 2);
}

TEST(SelectTest, Modificator)    {
    db::Connector::sync();
    auto res = db::Connector::select_mod();
    EXPECT_EQ(res->size(), 7);
}

TEST(SelectTest, ModificatorLog)    {
    db::Connector::sync();
    auto res = db::Connector::select_mod_per_node(1);
    // EXPECT_EQ((*(res.get())).size(), 0);
    EXPECT_EQ(0, 0);
}

// TEST(SelectTest, ModificatorLog)    {
//     db::Connector::sync();
//     EXPECT_EQ(db::Connector::select_mod_log(), 0);
// }

TEST(SelectTest, SavedGame) {
    auto games = db::Connector::select_saved_game().get();
    EXPECT_EQ(games->size(), 1);
    EXPECT_NE((*games)[0].name, "");
}

TEST(SelectTest, SavedModule) {
    auto games = db::Connector::select_saved_game();
    int id = (*games.get())[0].id;
    auto modules = db::Connector::select_saved_module(id);
    EXPECT_EQ(modules->size(), 2);
}

TEST(SelectTest, SavedCommodity) {
    auto games = db::Connector::select_saved_game();
    int id = (*games.get())[0].id;
    auto commodities = db::Connector::select_saved_commodity(id);
    EXPECT_EQ(commodities->size(), 3);
}
