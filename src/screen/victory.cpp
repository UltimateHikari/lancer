#include "victory.hpp"

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "graph.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

namespace sc{

class VictoryBase: public ftxui::ComponentBase{
public:
    static const int DETAIL_WIDTH = 50;
    Game& game;
    state::StateManager& state;
    ftxui::ButtonOption option = ftxui::ButtonOption();
    ftxui::Component buttons = ftxui::Container::Vertical({});
    std::vector<std::string> radiobox_list;
    std::vector<int> max_slots;
    int selected = 0;
    int w_slots = 0;
    int a_slots = 0;
    int s_slots = 0;
    int energy = 0;
    int inventory = 0;

    int structure = 0;
    int speed = 0;
    int evasion = 0;
    std::string name;
    std::shared_ptr<std::vector<ent::ShipFrameClass>> class_list;
    Graph logo_graph;

    VictoryBase(Game& game_, state::StateManager& state_):
        game(game_), state(state_)
    {
        option.border = false;
        RenderButtons();
        class_list = db::Connector::select_frame_class();
        for(auto& i: *class_list){
          radiobox_list.push_back(i.name);
          max_slots.push_back(i.max_slots);
        }
        Add(buttons);
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        return hbox({
            vbox({
                text(L" victory screen "),
                separator(),
                buttons->Render()
            }) | border | size(WIDTH, GREATER_THAN, DETAIL_WIDTH),
            graph(std::ref(logo_graph)) 
            | center | color(Color::BlueLight) | xflex_grow | yflex_grow | bgcolor(Color::White)
        }) | xflex_grow | yflex_grow;
    }
    
    void RenderButtons(){
      buttons->Add(RenderNameField());
      buttons->Add(RenderType());
      buttons->Add(RenderWeaponSlotsSlider());
      buttons->Add(RenderArmorSlotsSlider());
      buttons->Add(RenderSupportSlotsSlider());
      buttons->Add(RenderEnergySlider());
      buttons->Add(RenderInventorySlider());
      buttons->Add(RenderStructureSlider());
      buttons->Add(RenderSpeedSlider());
      buttons->Add(RenderEvasionSlider());
      buttons->Add(RenderAllowed());
      buttons->Add(RenderSubmit());
    }

    ftxui::Component RenderNameField(){
      using namespace ftxui;
      return Input(&name, "frame name");
    }

    ftxui::Component RenderType(){
      using namespace ftxui;
      return Radiobox(&radiobox_list, &selected);
    }

    ftxui::Component RenderWeaponSlotsSlider(){
      using namespace ftxui;
      return Slider("Weapon slots:  ", &w_slots, 0, 20, 1);
    }

    ftxui::Component RenderArmorSlotsSlider(){
      using namespace ftxui;
      return Slider("Armor slots:   ", &a_slots, 0, 20, 1);
    }

    ftxui::Component RenderSupportSlotsSlider(){
      using namespace ftxui;
      return Slider("Support slots: ", &s_slots, 0, 20, 1);
    }

    ftxui::Component RenderEnergySlider(){
      using namespace ftxui;
      return Slider("Energy:    ", &energy, 0, 100, 1);
    }

    ftxui::Component RenderInventorySlider(){
      using namespace ftxui;
      return Slider("Inventory: ", &inventory, 0, 1200, 1);
    }

    ftxui::Component RenderStructureSlider(){
      using namespace ftxui;
      return Slider("Structure: ", &structure, 0, 1000, 1);
    }

    ftxui::Component RenderSpeedSlider(){
      using namespace ftxui;
      return Slider("Speed:     ", &speed, 0, 100, 1);
    }

    ftxui::Component RenderEvasionSlider(){
      using namespace ftxui;
      return Slider("Evasion:   ", &evasion, 0, 50, 1);
    }

    ftxui::Component RenderAllowed(){
      using namespace ftxui;
      return Renderer([&]{
        return vbox({
          text("max slots allowed:   " + fmti(getCurrentMaxSlots())),
          text("now slots allocated: " + fmti(w_slots + a_slots + s_slots))
        });
      });
    }

    ftxui::Component RenderSubmit(){
      using namespace ftxui;
      return Button("submit", [&]{
        ent::ShipFrame frame{
          name,
          (*class_list)[selected],
          ent::ShipFrameSlots{w_slots,a_slots,s_slots},
          ent::ShipFrameParams{energy, inventory, structure, speed, evasion}
        };
        if(getCurrentMaxSlots() == w_slots + a_slots + s_slots){
          //external connector :: push_frame()
        }
      });
    }

    int getCurrentMaxSlots(){
      return (*class_list)[selected].max_slots;
    }

};

ftxui::Component Victory(Game& game, state::StateManager& state) {
  return ftxui::Make<VictoryBase>(game,state);
}

}
