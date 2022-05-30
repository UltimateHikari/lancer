#ifndef LANCER_UI_NAVIGATION_HPP
#define LANCER_UI_NAVIGATION_HPP

#include <ftxui/component/component.hpp>
#include "ftxui/component/component_base.hpp"
#include "game.hpp"
#include "view/state.hpp"
#include <functional>

namespace sc{
ftxui::Component Navigation(Game& game, std::function<void(md::BattleResult)> onEncounter, state::StateManager& state);
}

#endif
