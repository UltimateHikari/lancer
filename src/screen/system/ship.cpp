#include "ship.hpp"

#include <vector>
#include <memory>
#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "screen/graph.hpp"

#include <ftxui/component/event.hpp> 

namespace sc {

enum states{NONE, FRM, MOD};

class ShipBase : public ftxui::ComponentBase{
public: 
    static const int DETAIL_WIDTH = 40;
    Game * game;
    ftxui::Component mod_list;
    ftxui::Element iteminfocolumn;
    ftxui::Element iteminfo;
    ftxui::Element panel;
    ftxui::Element detailpanel;
    Graph logo_graph;

    int state = NONE;
    ent::ShipFrame current_frame = {};
    ent::Module current_mod;

    ShipBase(Game& game_): game(&game_){
        using namespace ftxui;
        mod_list = Container::Vertical({});
        Add(mod_list);
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        RenderList();
        switch(state){
            case MOD:
                iteminfocolumn = RenderModDetailsColumn();
                iteminfo = RenderModDetails(current_mod);
                break;
            case FRM:
                iteminfocolumn = RenderFrameDetailsColumn();
                iteminfo = RenderFrameDetails(current_frame);
                break;
            default:
                iteminfocolumn = ftxui::text("");
                iteminfo = ftxui::text("");
                break;
        }
        auto logo = graph(std::ref(logo_graph)) 
            | center | color(Color::Wheat1) | xflex_grow ;
        RenderDetails();
        return hbox({panel | xflex_grow, logo, detailpanel}) | border;
    }

    void RenderList(){

        mod_list->DetachAllChildren();
        auto& model = game->getModel();
        current_frame = model.get_frame();
        auto& modules = model.get_equipped_modules();

        mod_list->Add(RenderFrame(current_frame));
        for(auto& i: modules){
            mod_list->Add(RenderModule(i));
        }
        panel = mod_list->Render() | ftxui::border;
    }

    void RenderDetails(){
        using namespace ftxui;
        detailpanel = hbox({iteminfocolumn, iteminfo}) | size(WIDTH, GREATER_THAN, DETAIL_WIDTH) | border;
    }

    ftxui::Component RenderFrame(ent::ShipFrame& frame){
        using namespace ftxui;
        return Container::Horizontal({
            Button("Details", [&]{ state = FRM;}),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(frame.fclass.name);
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(frame.name);
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(fmti(frame.params.inventory));
            })
        });
    }

    ftxui::Component RenderModule(ent::Module& module){
        using namespace ftxui;
        return Container::Horizontal({
            Button("Details", [&]{current_mod = module; state = MOD;}),
            Renderer([&]{return filler();}),
            Button("Unequip", [&]{game->getModel().unequip_module(module);}),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(module.name);
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(module.type.name);
            })
        });
    }

    ftxui::Element RenderModDetailsColumn(){
        using namespace ftxui;
        return vbox({
            text("Module:"),
            separator(),
            text("Module type:"),
            text("Average price:"),
            text("Description:"),
        }) |
        yflex;
    }

    ftxui::Element RenderModDetails(const ent::Module& mod){
        using namespace ftxui;
        return vbox({
            text(mod.name + " (" + std::to_string(mod.id) + ")"),
            separator(),
            text(mod.type.name),
            text(fmti(mod.price)),
        }) |
        xflex_grow;
    }

    ftxui::Element RenderFrameDetailsColumn(){
        using namespace ftxui;
        return vbox({
            text("Frame:"),
            separator(),
            text("Frame class:"),
            text("Average price:"),
            text("Description:"),
        }) |
        xflex_grow;
    }

    ftxui::Element RenderFrameDetails(const ent::ShipFrame& frm){
        using namespace ftxui;
        return vbox({
        text(frm.name + " (" + std::to_string(frm.id) + ")"),
        separator(),
        text(frm.fclass.name),
        text(fmti(0)),
        }) | 
        xflex_grow;
    }
};

ftxui::Component Ship(Game& game) {
  return ftxui::Make<ShipBase>(game);
}

}
