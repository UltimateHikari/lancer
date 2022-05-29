#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "ftxui/component/component.hpp"
#include "game.hpp"
#include "view/state.hpp"

namespace sc{
    ftxui::Component System(Game& game, state::StateManager& state);
}

#endif