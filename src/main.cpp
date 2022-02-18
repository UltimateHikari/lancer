#include <sqlite_orm/sqlite_orm.h>

#include <string>
#include <iostream>
#include <cassert>

using namespace sqlite_orm;

using std::cout;
using std::cerr;
using std::endl;

struct RapArtist {
    int id;
    std::string name;
};

class Corporation{
    public:
        int id;
        std::string name;

        static auto get_table(){
            return make_table("corporation",
            make_column("id", &Corporation::id, primary_key()),
            make_column("name", &Corporation::name));
        }
};

class CommodityType {
    public:
        int id;
        std::string name;
};

class Commodity {
    public:
        int id;
        int type_id;
        int corp_id;
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
    auto storage = make_storage("lancer.db",
        Corporation::get_table());
    cerr << "lancer opened" << endl;
    storage.sync_schema();

    auto rows = storage.select(columns(&Corporation::id, &Corporation::name));
    cerr << rows.size() << endl;
    for(auto& i: rows){
        cerr << std::get<0>(i) << " " << std::get<1>(i) << endl;
    }
}

int main(int, char**) {
    orm_test();
    lancer_test();
    return 0;
}