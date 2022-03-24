#include "model/model.hpp"
#include <ctime>
#include <iomanip>

int Model::get_sense(){
    return sense_of_life;
}
bool Model::is_game_active(){
    return game_active_flag;
}
void Model::set_game_active(bool activity){
    game_active_flag = activity;
}

std::string Model::get_time(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

    return oss.str();
}