#include <sqlite_orm/sqlite_orm.h>
#include <iostream>

#include "db/lancer.hpp"
#include "db/database.hpp"

#include "screen/main.hpp"

#include "path.hpp"
#include "game.hpp"

#include "easyloggingpp/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace sqlite_orm;

void lancer_visual_test(){
    using std::cerr;
    db::Connector::sync();
    db::Connector::select_corporation();

    auto comm = db::Connector::select_commodity();
    cerr << "Commodities:\n";
    for(auto& i : *(comm.get())){
        cerr << i.out() << std::endl;
    }

    db::Connector::select_commodity_type();
    db::Connector::select_frame_class();
    db::Connector::select_frame();
    db::Connector::select_module_type();
    db::Connector::select_element();
    db::Connector::test_select_module();

    auto mod = db::Connector::select_module();
    std::cerr << "Modules:\n";
    for(auto& i : *(mod.get())){
        cerr << i.out() << std::endl;
    }

    auto gam = db::Connector::select_saved_game();
    std::cerr << "Saved games:\n";
    for(auto& i : *(gam.get())){
        cerr << i.out() << std::endl;
    }

    auto smod = db::Connector::select_saved_module(1);
    std::cerr << "Saved modules:\n";
    for(auto& i : *(smod.get())){
        cerr << i.first.out() << " " << std::to_string(i.second) << std::endl;
    }
    
    auto scom = db::Connector::select_saved_commodity(1);
    std::cerr << "Saved commodities:\n";
    for(auto& i : *(scom.get())){
        cerr << i.first.out() << " " << std::to_string(i.second) << std::endl;
    }

    auto ln = db::Connector::select_lane();
    std::cerr << "Lanes:\n";
    for(auto& i : *(ln.get())){
        cerr << i.out() << std::endl;
    }

    auto md = db::Connector::select_node();
    std::cerr << "Nodes:\n";
    for(auto& i : *(md.get())){
        cerr << i.out() << std::endl;
    }
}

int main(int, char**) {
    LOG(INFO) << "My first info log using default logger";
    sc::Main* screen = new sc::Main();

    Game* game = new Game();


    screen->show(*game);
    return 0;
}