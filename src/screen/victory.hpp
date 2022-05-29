#ifndef VICTORY_HPP
#define VICTORY_HPP

#include "ftxui/component/component.hpp"
#include "game.hpp"
#include "view/state.hpp"

namespace sc{
    ftxui::Component Victory(Game& game, state::StateManager& state);
}

#endif
