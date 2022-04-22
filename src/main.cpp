#include <sqlite_orm/sqlite_orm.h>
#include <iostream>

#include "db/lancer.hpp"
#include "db/database.hpp"

#include "screen/main.hpp"

#include "path.hpp"
#include "game.hpp"

using namespace sqlite_orm;

void lancer_test(){
    db::Connector::sync();
    db::Connector::select_corporation();
    auto comm = db::Connector::select_commodity();
    db::Connector::select_commodity_type();
    db::Connector::select_frame_class();
    db::Connector::select_frame();
    db::Connector::select_module_type();
    db::Connector::select_element();
    db::Connector::test_select_module();
    std::cerr << "Modules:\n";
    auto mod = db::Connector::select_module();
    std::cerr << "Saved games:\n";
    auto gam = db::Connector::select_saved_game();
    std::cerr << "Saved modules:\n";
    auto smod = db::Connector::select_saved_module(1);
    std::cerr << "Saved commodities:\n";
    auto scom = db::Connector::select_saved_commodity(1);
    std::cerr << "Lanes:\n";
    auto ln = db::Connector::select_lane();
    std::cerr << "Nodes:\n";
    auto md = db::Connector::select_node();
}

int main(int, char**) {
    lancer_test();
    // sc::Main* screen = new sc::Main();

    // Game* game = new Game();

    // screen->show(*game);
    return 0;
}