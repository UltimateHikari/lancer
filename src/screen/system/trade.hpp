#ifndef LANCER_UI_TRADE_HPP
#define LANCER_UI_TRADE_HPP

#include <ftxui/component/component.hpp>
#include "ftxui/component/component_base.hpp"
#include "game.hpp"
#include "view/state.hpp"

namespace sc{
ftxui::Component Trade(Game& game, state::StateManager& state);
}

#endif
