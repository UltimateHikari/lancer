#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "ftxui/component/component.hpp"
#include "game.hpp"
#include "view/state.hpp"

namespace sc{
    ftxui::Component Pause(Game& game, state::StateManager& state);
}

#endif
