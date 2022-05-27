#ifndef MENU_HPP
#define MENU_HPP

#include "ftxui/component/component.hpp"
#include "game.hpp"
#include "view/state.hpp"

namespace sc{
    ftxui::Component Menu(Game& game, state::StateManager& state);
}

#endif
