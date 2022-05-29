#include "model/oututil.hpp"

std::string fmt(std::string& s){
    return s + " ";
}

std::string fmti(int i){
    return std::to_string(i) + " ";
}

std::string fmtbi(int i){
    return "[" + std::to_string(i) + "]";
}