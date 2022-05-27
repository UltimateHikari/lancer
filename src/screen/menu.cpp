#include "menu.hpp"

#include <vector>
#include <memory>
#include <cmath>

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

namespace sc {

class Graph {
 public:
  std::vector<int> operator()(int width, int height) const {
    std::vector<int> output(width);
    for (int i = 0; i < width; ++i) {
      float v = 0;
      v += 0.1f * std::sin((i + shift) * 0.1f);        // NOLINT
      v += 0.2f * std::sin((i + shift + 10) * 0.15f);  // NOLINT
      v += 0.1f * std::sin((i + shift) * 0.03f);       // NOLINT
      v *= height;                                // NOLINT
      v += 0.5f * height;                         // NOLINT
      output[i] = static_cast<int>(v);
    }
    return output;
  }
  int shift = 0;
};

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


// enum states{NONE, FRM, MOD};

// class ShipBase : public ftxui::ComponentBase{
// public: 
//     Game * game;
//     ftxui::Component mod_list;
//     ftxui::Element iteminfocolumn;
//     ftxui::Element iteminfo;
//     ftxui::Element panel;
//     ftxui::Element logo = ftxui::text("logo") 
//         | ftxui::border | color(ftxui::Color::BlueLight);

//     int state = NONE;
//     ent::ShipFrame current_frame = {};
//     ent::Module current_mod;

//     ShipBase(Game& game_): game(&game_){
//         using namespace ftxui;
//         mod_list = Container::Vertical({});
//         Add(mod_list);
//     }

//     ftxui::Element Render() override {
//         RenderList();
//         switch(state){
//             case MOD:
//                 iteminfocolumn = RenderModDetailsColumn();
//                 iteminfo = RenderModDetails(current_mod);
//                 break;
//             case FRM:
//                 iteminfocolumn = RenderFrameDetailsColumn();
//                 iteminfo = RenderFrameDetails(current_frame);
//                 break;
//             default:
//                 iteminfocolumn = ftxui::text("");
//                 iteminfo = ftxui::text("");
//                 break;
//         }
//         return ftxui::hflow({panel, logo, ftxui::hbox({iteminfocolumn, iteminfo})}) | ftxui::border;
//     }

//     void RenderList(){

//         mod_list->DetachAllChildren();
//         auto& model = game->getModel();
//         current_frame = model.get_frame();
//         auto& modules = model.get_equipped_modules();

//         mod_list->Add(RenderFrame(current_frame));
//         for(auto& i: modules){
//             mod_list->Add(RenderModule(i));
//         }
//         panel = mod_list->Render() | ftxui::borderDouble;
//     }

//     ftxui::Component RenderFrame(ent::ShipFrame& frame){
//         using namespace ftxui;
//         return Container::Horizontal({
//             Button("Details", [&]{ state = FRM;}),
//             Renderer([&]{return filler();}),
//             Renderer([&]{
//                 return text(frame.fclass.name);
//             }),
//             Renderer([&]{return filler();}),
//             Renderer([&]{
//                 return text(frame.name);
//             }),
//             Renderer([&]{return filler();}),
//             Renderer([&]{
//                 return text(fmti(frame.params.inventory));
//             })
//         });
//     }

//     ftxui::Component RenderModule(ent::Module& module){
//         using namespace ftxui;
//         return Container::Horizontal({ //TODO : fix bug here, add rquip/uneqips
//             Button("Details", [&]{current_mod = module; state = MOD;}),
//             Renderer([&]{return filler();}),
//             Button("Unequip", [&]{game->getModel().unequip_module(module);}),
//             Renderer([&]{return filler();}),
//             Renderer([&]{
//                 return text(module.name);
//             }),
//             Renderer([&]{return filler();}),
//             Renderer([&]{
//                 return text(module.type.name);
//             })
//         });
//     }

//     ftxui::Element RenderModDetailsColumn(){
//         using namespace ftxui;
//         return vbox({
//             text("Module:"),
//             separator(),
//             text("Module type:"),
//             text("Average price:"),
//             text("Description:"),
//         }) |
//         yflex;
//     }

//     ftxui::Element RenderModDetails(const ent::Module& mod){
//         using namespace ftxui;
//         return vbox({
//             text(mod.name + " (" + std::to_string(mod.id) + ")"),//, //TODO - for debug purpose
//             separator(),
//             text(mod.type.name),
//             text(fmti(mod.price)),
//         }) | //TODO add stats
//         yflex;
//     }

//     ftxui::Element RenderFrameDetailsColumn(){
//         using namespace ftxui;
//         return vbox({
//             text("Frame:"),
//             separator(),
//             text("Frame class:"),
//             text("Average price:"),
//             text("Description:"),
//         }) |
//         yflex;
//     }

//     ftxui::Element RenderFrameDetails(const ent::ShipFrame& frm){
//         using namespace ftxui;
//         return vbox({
//         text(frm.name + " (" + std::to_string(frm.id) + ")"), //TODO - for debug purpose
//         separator(),
//         text(frm.fclass.name),
//         text(fmti(0)),
//         }) | //TODO add stats
//         yflex;
//     }
// };
