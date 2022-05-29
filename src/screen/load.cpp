#include "load.hpp"

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "graph.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
namespace sc{

class LoadBase: public ftxui::ComponentBase{
public:
    static const int DETAIL_WIDTH = 40;
    Game& game;
    state::StateManager& state;
    ftxui::ButtonOption option = ftxui::ButtonOption();
    ftxui::Component buttons = ftxui::Container::Vertical({});
    Graph logo_graph;

    LoadBase(Game& game_, state::StateManager& state_):
        game(game_), state(state_)
    {
        option.border = false;
        Add(buttons);
    };

    void RenderList(){
      buttons->DetachAllChildren();
      auto saved_games = game.get_saved_games();
      for(auto& i: *saved_games){
          buttons->Add(RenderSave(i));
      }
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        RenderList();
        return hbox({
            vbox({
                text(L" load game "),
                separator(),
                buttons->Render()
            }) | border | size(WIDTH, GREATER_THAN, DETAIL_WIDTH),
            graph(std::ref(logo_graph)) 
            | center | color(Color::BlueLight) | xflex_grow | yflex_grow | bgcolor(Color::White)
        }) | xflex_grow | yflex_grow;
    }

    ftxui::Component RenderSave(ent::SavedGame& save){
      using namespace ftxui;
      return Container::Horizontal({
          Button("Load", [&]{game.getModel().load_game(save.id); state.onStateChange(state::System);}),
          Renderer([&]{return text(save.name);}),
          Renderer([&]{return text(save.date) | frame;})
      });
    }
    
};

ftxui::Component Load(Game& game, state::StateManager& state) {
  return ftxui::Make<LoadBase>(game, state);
}

}
