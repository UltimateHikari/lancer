#ifndef LANCER_ENTITIES_HPP
#define LANCER_ENTITIES_HPP

#include "lancer.hpp"

namespace ent{

class Comparable{
public:
    int id;
    Comparable(int id_): id(id_){}
};

inline bool operator< (const Comparable& lhs, const Comparable& rhs){ return lhs.id < rhs.id; }
inline bool operator== (const Comparable& lhs, const Comparable& rhs){ return rhs == lhs; }
// inline bool operator> (const Comparable& lhs, const Comparable& rhs){ return rhs < lhs; }
// inline bool operator<=(const Comparable& lhs, const Comparable& rhs){ return !(lhs > rhs); }
// inline bool operator>=(const Comparable& lhs, const Comparable& rhs){ return !(lhs < rhs); }

class CommodityType : public Comparable{
public:
    std::string name;
    CommodityType(int id_, std::string& name_):
        Comparable(id_), 
        name(std::move(name_))
    {}
};

class ModuleType : public Comparable{
public:
    std::string name;
    ModuleType(int id_, std::string& name_):
        Comparable(id_), 
        name(std::move(name_))
    {}
};

class Commodity : public Comparable{
public:
    CommodityType type;
    std::string name;
    Commodity(std::tuple<int, int, std::string, std::string>& raw_select):
        Comparable(std::get<0>(raw_select)),
        type{std::get<1>(raw_select), std::get<2>(raw_select)},
        name{std::move(std::get<3>(raw_select))}
        {}
};

class Module : public Comparable{
    ModuleType type;
    std::string name;
    Module(std::tuple<int, int, std::string, std::string>& raw_select):
        Comparable(std::get<0>(raw_select)),
        type{std::get<1>(raw_select), std::get<2>(raw_select)},
        name{std::move(std::get<3>(raw_select))}
        {}
};

}
#endif