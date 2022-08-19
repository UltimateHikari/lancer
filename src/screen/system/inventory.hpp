#ifndef LANCER_UI_INVENTORY_HPP
#define LANCER_UI_INVENTORY_HPP

#include <ftxui/component/component.hpp>
#include "ftxui/component/component_base.hpp"
#include "game.hpp"
#include "view/state.hpp"


namespace sc{
ftxui::Component Inventory(Game& game, state::StateManager& state);
}

#endif
