#ifndef LANCER_OUTUTIL_HPP
#define LANCER_OUTUTIL_HPP

#include <string>

namespace ent{

std::string fmt(std::string& s){
    return s + " ";
}

std::string fmti(int i){
    return std::to_string(i) + " ";
}
}

#endif
