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
    bool is_deprecated = true;
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
        case Load: case Credits: case Settings:
            if(isFromMenues(state)){
                state = newState;
                stateChangeEvent();
                return true;
            }
            break;
        case Save:
            if(state == Pause){
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
            switch (state)
            {
            case Pause: case Save:
                state = System;
                stateChangeEvent();
                break;
            case System:
                state = Pause;
                stateChangeEvent();
                break;
            default:
                state = Menu;
                stateChangeEvent();
                break;
            }
            return true;
        case Victory:
            if(state = System){
                state = newState;
                stateChangeEvent();
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
    void deprecate(){
        is_deprecated = true;
    }
    void commit(){
        is_deprecated = false;
    }
    bool isDeprecated(){
        return is_deprecated;
    }
};

}

#endif
