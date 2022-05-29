#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "ftxui/component/component.hpp"
#include "game.hpp"
#include "view/state.hpp"

namespace sc{
    ftxui::Component Settings(Game& game, state::StateManager& state);
}

#endif
