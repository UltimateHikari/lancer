#include "pause.hpp"

#include <memory>

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "graph.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

namespace sc {

class PauseBase: public ftxui::ComponentBase{
public:
    static const int DETAIL_WIDTH = 40;
    Game& game;
    state::StateManager& state;
    ftxui::ButtonOption option = ftxui::ButtonOption();
    ftxui::Component buttons;
    Graph logo_graph;

    PauseBase(Game& game_, state::StateManager& state_):
        game(game_), state(state_)
    {
        //logo_graph.shift = game.getTicker().registerCounter();
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
        return hbox({
            vbox({
                text(L" lancer "),
                separator(),
                buttons->Render()
            }) | border | size(WIDTH,GREATER_THAN, DETAIL_WIDTH),
            graph(std::ref(logo_graph)) 
            | center | color(Color::BlueLight) | xflex_grow | bgcolor(Color::White)
        }) | xflex_grow | yflex_grow;
    }

    ftxui::Component startButton() {
        return ftxui::Button("Continue", [&]{game.start(); state.onStateChange(state::Back);}, &option);
    }
    ftxui::Component loadButton() {
        return ftxui::Button("Save game", [&]{game.start(); state.onStateChange(state::Save);}, &option);
    }
    ftxui::Component credButton() {
        return ftxui::Button("Credits", [&]{state.onStateChange(state::Credits);}, &option);
    }
    ftxui::Component settingsButton() {
        return ftxui::Button("Settings", [&]{state.onStateChange(state::Settings);}, &option);
    }
    ftxui::Component exitButton() {
        return ftxui::Button("Exit to menu", [&]{state.onStateChange(state::Menu);}, &option);
    }
    
};


ftxui::Component Pause(Game& game, state::StateManager& state) {
  return ftxui::Make<PauseBase>(game, state);
}

}
