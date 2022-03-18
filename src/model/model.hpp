#ifndef LANCER_MODEL_HPP
#define LANCER_MODEL_HPP

class Model{
private:
    int sense_of_life = 42;
    bool game_active_flag = false;
public:
    int get_sense(){
        return sense_of_life;
    }
    bool is_game_active(){
        return game_active_flag;
    }
    void set_game_active(bool activity){
        game_active_flag = activity;
    }
};

#endif
