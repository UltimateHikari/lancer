#include "settings.hpp"

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "graph.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

namespace sc{

class SettingsBase: public ftxui::ComponentBase{
public:
    static const int DETAIL_WIDTH = 40;
    Game& game;
    state::StateManager& state;
    ftxui::ButtonOption option = ftxui::ButtonOption();
    ftxui::Component buttons = ftxui::Container::Vertical({});
    Graph logo_graph;

    SettingsBase(Game& game_, state::StateManager& state_):
        game(game_), state(state_)
    {
        option.border = false;
        RenderButtons();
        Add(buttons);
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        return hbox({
            vbox({
                text(L" settings "),
                separator(),
                buttons->Render()
            }) | border | size(WIDTH, GREATER_THAN, DETAIL_WIDTH),
            graph(std::ref(logo_graph)) 
            | center | color(Color::BlueLight) | xflex_grow | yflex_grow | bgcolor(Color::White)
        }) | xflex_grow | yflex_grow;
    }
    
    void RenderButtons(){
      for(int i = 0; i < 4; ++i){
        buttons->Add(RenderSetting(i));
      }
    }

    ftxui::Component RenderSetting(int i){
      using namespace ftxui;
      return Container::Horizontal({
          Button("do nothing", []{}),
          Renderer([i]{return text("useless setting " + fmti(i));})
      });
    }

};

ftxui::Component Settings(Game& game, state::StateManager& state) {
  return ftxui::Make<SettingsBase>(game,state);
}

}
