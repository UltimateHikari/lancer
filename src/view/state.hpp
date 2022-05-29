#ifndef STATE_HPP
#define STATE_HPP

#include <functional>

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
    Back, 
};

class StateManager{
private:
    State state = state::Menu;
    inline bool isFromMenues(state::State state){
        return (state == Menu || state == Pause);
    }
public:
    std::function<void()> stateChangeEvent = []{LOG(INFO) << "stateChangeEvent not set";};
    bool onStateChange(state::State newState){
        switch (newState)
        {
        case Menu:
            if(state != System){
                state = Menu;
                stateChangeEvent();
                return true;
            }
            break;
        case System:
            if(isFromMenues(state) || state == Load){
                state = System;
                stateChangeEvent();
                return true;
            }
            break;
        case Load: case Save:
            if(isFromMenues(state)){
                state = newState;
                stateChangeEvent();
                return true;
            }
            break;
        case Pause:
            if(state == System){
                state = newState;
                stateChangeEvent();
                return true;
            }
            break;
        case Back:
            if(state == Pause || state == Save){
                state = System;
            }else{
                state = Menu;
            }
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
