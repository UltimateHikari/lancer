#ifndef LANCER_ENTITIES_HPP
#define LANCER_ENTITIES_HPP

#include "db/lancer.hpp"

template<std::size_t... Is, class... Ts>
auto extract_subtuple(const std::tuple<Ts...>& tuple) {
    return std::make_tuple(std::get<Is>(tuple)...);
}

namespace ent{

struct Meta{
    int amount;
    int price;
};


class Comparable{
public:
    int id;
    Comparable(){};
    Comparable(int id_): id(id_){}
};

class Printable{
public:
    virtual std::string out() = 0;
};

inline bool operator< (const Comparable& lhs, const Comparable& rhs){ return lhs.id < rhs.id; }
inline bool operator== (const Comparable& lhs, const Comparable& rhs){ return rhs == lhs; }
// inline bool operator> (const Comparable& lhs, const Comparable& rhs){ return rhs < lhs; }
// inline bool operator<=(const Comparable& lhs, const Comparable& rhs){ return !(lhs > rhs); }
// inline bool operator>=(const Comparable& lhs, const Comparable& rhs){ return !(lhs < rhs); }


class CommodityType : public Comparable{
public:
    std::string name;
    CommodityType(){};
    CommodityType(int id_, std::string& name_):
        Comparable(id_), 
        name(std::move(name_))
    {}
};

class ModuleType : public Comparable{
public:
    std::string name;
    ModuleType(){};
    ModuleType(int id_, std::string& name_):
        Comparable(id_), 
        name(std::move(name_))
    {}
};

class Commodity : public Comparable, Printable{
public:
    CommodityType type;
    std::string name;
    int price = 100;
    Commodity(){};
    Commodity(std::tuple<int, int, std::string, std::string, int>& raw_select):
        Comparable(std::get<0>(raw_select)),
        type{std::get<1>(raw_select), std::get<2>(raw_select)},
        name{std::move(std::get<3>(raw_select))},
        price{std::get<4>(raw_select)}
        {}
    Commodity(std::tuple<int, int, std::string, std::string, int, int>& raw_select):
        Comparable(std::get<0>(raw_select)),
        type{std::get<1>(raw_select), std::get<2>(raw_select)},
        name{std::move(std::get<3>(raw_select))},
        price{std::get<4>(raw_select)}
        {}
    std::string out() override;
};

class Module : public Comparable, Printable{
public:
    ModuleType type;
    std::string name;
    int price;
    Module(){};
    Module(std::tuple<int, int, std::string, std::string, int>& raw_select):
        Comparable(std::get<0>(raw_select)),
        type{std::get<1>(raw_select), std::get<2>(raw_select)},
        name{std::move(std::get<3>(raw_select))},
        price{std::get<4>(raw_select)}
        {}
    Module(std::tuple<int, int, std::string, std::string, int, int>& raw_select):
        Comparable(std::get<0>(raw_select)),
        type{std::get<1>(raw_select), std::get<2>(raw_select)},
        name{std::move(std::get<3>(raw_select))},
        price{std::get<4>(raw_select)}
        {}
    std::string out() override;
};

class SavedGame : public Comparable, Printable{
public:
    std::string name;
    std::string date;
    SavedGame(std::tuple<int, std::string, std::string>& raw_select):
        Comparable(std::get<0>(raw_select)),
        name{std::get<1>(raw_select)},
        date{std::move(std::get<2>(raw_select))}
        {}
    std::string out() override;
};

class Corporation : public Comparable, public Printable{
public:
    std::string name;
    Corporation(){};
    Corporation(int id_, std::string& name_):
        Comparable(id_), 
        name(std::move(name_))
    {}
    std::string out() override;
};

class LightNode{
public:
    int id;
    std::string name;

    LightNode(int id_, std::string& name_):
        id(id_),
        name(std::move(name_))
    {}
};

class Node : public Printable{
public:
    int id;
    std::string name;

    ent::CommodityType pref;
    ent::Corporation corp;
    int order_level;
    int tech_level;

    Node(){};

    Node(std::tuple<
        int, 
        std::string, 
        int, std::string, 
        int, std::string, 
        int, 
        int>& raw_select):
        id(std::get<0>(raw_select)),
        name{std::get<1>(raw_select)},
        pref{std::get<2>(raw_select), std::get<3>(raw_select)},
        corp{std::get<4>(raw_select), std::get<5>(raw_select)},
        order_level{std::get<6>(raw_select)},
        tech_level{std::get<7>(raw_select)}
        {}
    std::string out() override;
};

class Lane : public Printable{
public:
    int id;
    LightNode start;
    LightNode end;
    int traverse_time;
    bool stability;

    Lane(std::tuple<
        int,
        int,std::string,
        int,std::string,
        int,
        bool>& raw_select):
        id{std::get<0>(raw_select)},
        start{std::get<1>(raw_select), std::get<2>(raw_select)},
        end{std::get<3>(raw_select),std::get<4>(raw_select)},
        traverse_time{std::get<5>(raw_select)},
        stability{std::get<6>(raw_select)}
        {}
    std::string out() override;
    std::string getContextedText(const ent::Node& node) const;
};

class Event : public Printable, public Comparable{
public:
    std::string name;
    int weight;
    Event(std::tuple<
        int,
        std::string,
        int>& raw_select):
        Comparable(std::get<0>(raw_select)),
        name{std::get<1>(raw_select)},
        weight{std::get<2>(raw_select)}
        {}
    std::string out() override;
    
};

class ModifierType : public Comparable{
public:
    std::string name;
    ModifierType(){};
    ModifierType(int id_, std::string& name_):
        Comparable(id_), 
        name(std::move(name_))
    {}
};

class LightModifier : public Comparable{
public:
    int event_id;
    LightModifier(std::tuple<int,int>& raw_select):
        Comparable(std::get<0>(raw_select)),
        event_id(std::get<1>(raw_select))
    {}
};

// purpose is updating details for node
class Modifier /*: public Printable*/{
public:
    int id;
    ent::ModifierType type;

    ent::CommodityType pref;
    //ent::Corporation corp;
    int order_level;
    int tech_level;

    Modifier(std::tuple<
        int,
        int,std::string,
        int,std::string,
        int,int
        >& raw_select):
        id{std::get<0>(raw_select)},
        type{std::get<1>(raw_select), std::get<2>(raw_select)},
        pref{std::get<3>(raw_select), std::get<4>(raw_select)},
        order_level{std::get<5>(raw_select)},
        tech_level{std::get<6>(raw_select)}
        {}
};

class ModifierLog{
public:
    int time;
    int node_id;
    int mod_id;
};

class VModifierLog : public Printable{
public:
    int time = 0;
    std::string node_name = "nowhere";
    std::string mod_name = "nothing";
    VModifierLog(){};
    VModifierLog(std::tuple<int,std::string,std::string>& raw_select):
        time(std::get<0>(raw_select)),
        node_name(std::get<1>(raw_select)),
        mod_name(std::get<2>(raw_select))
    {}
    std::string out() override;
};

class ShipFrameSlots {
public:
    int weap_slots = 0;
    int armr_slots = 0;
    int supp_slots = 0;

    ShipFrameSlots(){};

    ShipFrameSlots(std::tuple<int,int,int> raw_select):
        weap_slots(std::get<0>(raw_select)),
        armr_slots(std::get<1>(raw_select)),
        supp_slots(std::get<2>(raw_select))
    {}
};

class ShipFrameParams{
public:
    int energy = 0;
    int inventory = 0;

    int structure = 0;
    int speed = 0;
    int evasion = 0;

    ShipFrameParams(){};

    ShipFrameParams(const std::tuple<int,int,int,int,int>& raw_select):
        energy(std::get<0>(raw_select)),
        inventory(std::get<1>(raw_select)),
        structure(std::get<2>(raw_select)),
        speed(std::get<3>(raw_select)),
        evasion(std::get<4>(raw_select))
    {}
};


class ShipFrameClass : public Comparable{
public:
    std::string name;
    ShipFrameClass(){};
    ShipFrameClass(int id_, std::string& name_):
        Comparable(id_), 
        name(std::move(name_))
    {}
};

class ShipFrame : public Comparable, public Printable{
public:
    std::string name;
    ShipFrameClass fclass;
    Corporation corp;

    ShipFrameSlots slots;
    ShipFrameParams params;

    ShipFrame(){};

    ShipFrame(std::tuple<
        int,
        std::string,
        int, std::string,
        int, std::string,
        int,int,int,
        int,int,int,int,int
        >& raw_select):
            Comparable{std::get<0>(raw_select)},
            name(std::get<1>(raw_select)),
            fclass{std::get<2>(raw_select), std::get<3>(raw_select)},
            corp(std::get<4>(raw_select), std::get<5>(raw_select)),
            slots{extract_subtuple<6,7,8>(raw_select)},
            params{extract_subtuple<9,10,11,12,13>(raw_select)}
        {}
    std::string out() override;
};



}
#endif