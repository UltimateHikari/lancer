#ifndef SCREENFACTORY_HPP
#define SCREENFACTORY_HPP

#include "ftxui/component/component.hpp"

#include "view/state.hpp"
#include "game.hpp"

#include "screen/menu.hpp"
#include "screen/system.hpp"
#include "screen/load.hpp"
// #include "screen/save.hpp"
#include "screen/pause.hpp"
// #include "screen/victory.hpp"
// #include "screen/credits.hpp"
// #include "screen/settings.hpp"


class ScreenFactory{
public:
    ScreenFactory() = delete;
    static ftxui::Component getScreenForState(Game& game, state::StateManager& state){
        switch (state.getCurrent())
        {
        case state::Menu:
            return sc::Menu(game, state);
        case state::System:
            return sc::System(game, state);
        case state::Load:
            return sc::Load(game, state);
        // case state::Save:
        //     return sc::Save();
        case state::Pause:
            return sc::Pause(game, state);
        // case state::Victory:
        //     return sc::Victory();
        // case state::Credits:
        //     return sc::Credits();
        // case state::Victory:
        //     return sc::Victory();
        default:
            return sc::Menu(game, state);
        }
    }
};

#endif
