#ifndef LOAD_HPP
#define LOAD_HPP

#include "ftxui/component/component.hpp"
#include "game.hpp"
#include "view/state.hpp"

namespace sc{
    ftxui::Component Load(Game& game, state::StateManager& state);
}

#endif
