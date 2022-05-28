#ifndef STATE_HPP
#define STATE_HPP

namespace state{

enum State {
    Menu,
    System,
    Load,
    Save,
    Pause,
    Victory,
    Credits,
    Settings, 
};

class StateManager{
private:
    State state = state::Menu;
    inline bool isFromMenues(state::State state){
        return (state == Menu || state == Pause);
    }
public:
    bool onStateChange(state::State newState){
        //TODO all pages that left
        switch (newState)
        {
        case Menu:
            if(state != System){
                state = Menu;
                return true;
            }
            break;
        case System:
            if(isFromMenues(state) || state == Load){
                state = System;
                return true;
            }
            break;
        case Load: case Save:
            if(isFromMenues(state)){
                state = newState;
                return true;
            }
            break;
        case Pause:
            if(state == System){
                state = newState;
                return true;
            }
            break;
        default:
            return false;
        }
        return false;
    }
    state::State getCurrent() {
        return state;
    }
};

}

#endif
