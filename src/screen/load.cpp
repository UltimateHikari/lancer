#include "load.hpp"

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "graph.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
namespace sc{

//TODO onevent handler for q
class LoadBase: public ftxui::ComponentBase{
public:
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
      for(auto& i: (*saved_games.get())){
          buttons->Add(RenderSave(i));
      }
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        RenderList();
        return hflow({
            vbox({
                text(L" load game "),
                separator(),
                buttons->Render()
            }) | border,
            graph(std::ref(logo_graph)) 
            | center | color(Color::BlueLight) | xflex_grow | yflex_grow | bgcolor(Color::White)
        });
    }

    ftxui::Component RenderSave(ent::SavedGame& save){
      using namespace ftxui;
      return Container::Horizontal({
          Button(save.name, [&]{game.getModel().load_game(save.id); state.onStateChange(state::System);}),
          Renderer([&]{return text(save.date);})
      });
    }
    
};

ftxui::Component Load(Game& game, state::StateManager& state) {
  return ftxui::Make<LoadBase>(game, state);
}

}
