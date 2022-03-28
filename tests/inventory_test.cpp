#include <gtest/gtest.h>
#include <database.hpp>
#include "model/model.hpp"

using namespace sqlite_orm;

TEST(InventoryTest, Construct){
    Model* model = new Model();
    EXPECT_EQ(model->get_inventory().get_commodities().size(),0);
    EXPECT_EQ(model->get_inventory().get_modules().size(),0);
    delete model;
}

// TEST(InventoryTest, Init){
//     Model* model = new Model();
//     int save_id = 1;
//     model->load_saved_model();
//     EXPECT_EQ(model->get_inventory().get_commodities().size(), 1);
//     EXPECT_EQ(model->get_inventory().get_modules().size(), 1);
//     delete model;
// }

TEST(InventoryTest, PutCommodity){
    Model* model = new Model();
    auto all_commodities = db::Connector::select_commodity();
    EXPECT_EQ(model->get_inventory().get_commodities().size(), 0);
    model->get_inventory().update_commodity((*all_commodities.get())[0], 2);
    EXPECT_EQ(model->get_inventory().get_commodities()[0].second, 2);
    delete model;
}

TEST(InventoryTest, PutCommodityTwice){
    Model* model = new Model();
    auto all_commodities = db::Connector::select_commodity();
    EXPECT_EQ(model->get_inventory().get_commodities().size(), 0);
    model->get_inventory().update_commodity((*all_commodities.get())[0], 2);
    EXPECT_EQ(model->get_inventory().get_commodities()[0].second, 2);
    model->get_inventory().update_commodity((*all_commodities.get())[0], 3);
    EXPECT_EQ(model->get_inventory().get_commodities()[0].second, 5);
    delete model;
}

TEST(InventoryTest, PutTwoCommodity){
    Model* model = new Model();
    auto all_commodities = db::Connector::select_commodity();
    EXPECT_EQ(model->get_inventory().get_commodities().size(), 0);
    model->get_inventory().update_commodity((*all_commodities.get())[0], 2);
    model->get_inventory().update_commodity((*all_commodities.get())[1], 2);
    EXPECT_EQ(model->get_inventory().get_commodities().size(), 2);
    delete model;
}

TEST(InventoryTest, PutModule){
    Model* model = new Model();
    auto all_modules = db::Connector::select_module();
    EXPECT_EQ(model->get_inventory().get_modules().size(), 0);
    model->get_inventory().update_module((*all_modules.get())[0], 2);
    EXPECT_EQ(model->get_inventory().get_modules()[0].second, 2);
    delete model;
}

TEST(InventoryTest, PutModuleTwice){
    Model* model = new Model();
    auto all_modules = db::Connector::select_module();
    EXPECT_EQ(model->get_inventory().get_modules().size(), 0);
    model->get_inventory().update_module((*all_modules.get())[0], 2);
    EXPECT_EQ(model->get_inventory().get_modules()[0].second, 2);
    model->get_inventory().update_module((*all_modules.get())[0], 3);
    EXPECT_EQ(model->get_inventory().get_modules()[0].second, 5);
    delete model;
}

TEST(InventoryTest, PutTwoModule){
    Model* model = new Model();
    auto all_modules = db::Connector::select_module();
    EXPECT_EQ(model->get_inventory().get_modules().size(), 0);
    model->get_inventory().update_module((*all_modules.get())[0], 2);
    model->get_inventory().update_module((*all_modules.get())[1], 2);
    EXPECT_EQ(model->get_inventory().get_modules().size(), 2);
    delete model;
}