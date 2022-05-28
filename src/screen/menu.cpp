#include "menu.hpp"

#include <memory>

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "graph.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

namespace sc {

class MenuBase: public ftxui::ComponentBase{
public:
    Game& game;
    state::StateManager& state;
    ftxui::ButtonOption option = ftxui::ButtonOption();
    ftxui::Component buttons;
    Graph logo_graph;

    MenuBase(Game& game_, state::StateManager& state_):
        game(game_), state(state_)
    {
        option.border = false;
        buttons = ftxui::Container::Vertical({
            startButton(),
            loadButton(),
            credButton(),
            settingsButton(),
            exitButton()
        });
        Add(buttons);
    };

    ftxui::Element Render() override {
        using namespace ftxui;
        return hflow({
            vbox({
                text(L" lancer "),
                separator(),
                buttons->Render()
            }) | border,
            graph(std::ref(logo_graph)) 
            | center | color(Color::BlueLight) | xflex_grow | yflex_grow | bgcolor(Color::White)
        });
    }

    ftxui::Component startButton() {
        return ftxui::Button("New game", [&]{game.start(); state.onStateChange(state::System);}, &option);
    }
    ftxui::Component loadButton() {
        return ftxui::Button("Load game", [&]{game.start(); state.onStateChange(state::Load);}, &option);
    }
    ftxui::Component credButton() {
        return ftxui::Button("Credits", [&]{state.onStateChange(state::Credits);}, &option);
    }
    ftxui::Component settingsButton() {
        return ftxui::Button("Settings", [&]{state.onStateChange(state::Settings);}, &option);
    }
    ftxui::Component exitButton() {
        return ftxui::Button("Exit game", [&]{game.onEnd();}, &option);
    }
    
};


ftxui::Component Menu(Game& game, state::StateManager& state) {
  return ftxui::Make<MenuBase>(game, state);
}

}
