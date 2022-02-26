#include <sqlite_orm/sqlite_orm.h>

#include <string>
#include <iostream>
#include <cassert>
#include "lancer.hpp"
#include "path.hpp"
#include "database.hpp"
#include <type_traits>

using namespace sqlite_orm;

using std::cout;
using std::cerr;
using std::endl;

struct RapArtist {
    int id;
    std::string name;
};

void orm_test(){
    auto storage = make_storage(":memory:",
                                make_table("rap_artists",
                                           make_column("id", &RapArtist::id, primary_key()),
                                           make_column("name", &RapArtist::name)));
    cout << "in memory db opened" << endl;
    storage.sync_schema();

    assert(!storage.count<RapArtist>());

    storage.insert(RapArtist{-1, "The Weeknd"});

    storage.transaction([&] {
        storage.insert(RapArtist{-1, "Drake"});
        return true;
    });

    cout << "rap artists count = " << storage.count<RapArtist>() << endl;

    //  transaction also work in memory..
    storage.transaction([&] {
        storage.insert(RapArtist{-1, "Kanye West"});
        return false;
    });

    cout << "rap artists count = " << storage.count<RapArtist>() << " (no Kanye)" << endl;
}

void lancer_test(){
    db::Connector::sync();
    db::Connector::select_corporation();
    db::Connector::select_commodity();
    db::Connector::select_commodity_type();
    db::Connector::select_commodity_full();
    db::Connector::select_frame_class();
    db::Connector::select_frame();
    db::Connector::select_module_type();
    db::Connector::select_element();
    db::Connector::select_module();
}

int main(int, char**) {
    orm_test();
    lancer_test();
    return 0;
}