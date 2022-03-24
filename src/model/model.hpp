#ifndef LANCER_MODEL_HPP
#define LANCER_MODEL_HPP

#include <string>

class Model{
private:
    int sense_of_life = 42;
    bool game_active_flag = false;
public:
    int get_sense();
    bool is_game_active();
    void set_game_active(bool activity);
    std::string get_time();
};

#endif
