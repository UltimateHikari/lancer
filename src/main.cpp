#include <sqlite_orm/sqlite_orm.h>


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
    auto mod = db::Connector::select_module();
    auto gam = db::Connector::select_saved_game();
    auto smod = db::Connector::select_saved_module(1);
    auto scom = db::Connector::select_saved_commodity(1);
    auto ln = db::Connector::select_lane();
    auto md = db::Connector::select_node();
}

int main(int, char**) {
    lancer_test();
    sc::Main* screen = new sc::Main();

    Game* game = new Game();

    screen->show(*game);
    return 0;
}