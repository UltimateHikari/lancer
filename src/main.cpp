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

void lancer_log_test(){
    using std::cerr;
    db::Connector::sync();
    db::Connector::select_corporation();

    auto comm = db::Connector::select_commodity();
    LOG(INFO) << "Commodities:";
    for(auto& i : *(comm.get())){
        LOG(INFO) << i.out();
    }

    db::Connector::select_commodity_type();
    db::Connector::select_frame_class();
    db::Connector::select_frame();
    db::Connector::select_module_type();
    db::Connector::select_element();
    db::Connector::test_select_module();

    auto mod = db::Connector::select_module();
    LOG(INFO) << "Modules:";
    for(auto& i : *(mod.get())){
        LOG(INFO) << i.out();
    }

    auto gam = db::Connector::select_saved_game();
    LOG(INFO) << "Saved games:";
    for(auto& i : *(gam.get())){
        LOG(INFO) << i.out();
    }

    auto smod = db::Connector::select_saved_module(1);
    LOG(INFO) << "Saved modules:";
    for(auto& i : *(smod.get())){
        LOG(INFO) << i.first.out() << " " << std::to_string(i.second);
    }
    
    auto scom = db::Connector::select_saved_commodity(1);
    LOG(INFO) << "Saved commodities:";
    for(auto& i : *(scom.get())){
        LOG(INFO) << i.first.out() << " " << std::to_string(i.second);
    }

    // auto ln = db::Connector::select_lane();
    // LOG(INFO) << "Lanes:";
    // for(auto& i : *(ln.get())){
    //     LOG(INFO) << i.out();
    // }

    auto lns = db::Connector::select_single_lane(1);
    LOG(INFO) << "Lanes-selected:";
    for(auto& i : *(lns.get())){
        LOG(INFO) << i.out();
    }

    auto md = db::Connector::select_node();
    LOG(INFO) << "Nodes:";
    LOG(INFO) << (*(md.get()))[0].name;
    for(auto& i : *(md.get())){
        LOG(INFO) << i.out();
    }
}

int main(int, char**) {
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "false");
    el::Loggers::reconfigureLogger("default", defaultConf);

    LOG(INFO) << "My first info log using default logger";
    //lancer_log_test();
    sc::Main* screen = new sc::Main();

    Game* game = new Game();

    auto commodities = game->getModel().get_current_stock().get_commodities();
    LOG(INFO) << "Got " << commodities.size() << " commodities";

    screen->show(*game);
    return 0;
}