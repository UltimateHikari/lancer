#include "inventory.hpp"

#include <vector>
#include <memory>

#include "model/entities.hpp"
#include "model/oututil.hpp"
#include "model/model.hpp"

#include <ftxui/component/event.hpp> 

#include "easyloggingpp/easylogging++.h"

namespace sc{

class InventoryBase : public ftxui::ComponentBase{
public:
    enum states{NONE, COMM, MOD};
    static const int DETAIL_WIDTH = 40;
    Game* game;
    ftxui::Component list;
    ftxui::Element iteminfocolumn;
    ftxui::Element iteminfo;
    ftxui::Element panel;
    ftxui::Element detailpanel;
    
    int state = NONE;
    ent::Commodity current_comm;
    ent::Module current_mod;

    InventoryBase(Game& game_): game(&game_){
        using namespace ftxui;
        list = Container::Vertical({});
        Add(list);
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        RenderList();
        switch(state){
            case COMM:
                iteminfocolumn = RenderCommDetailsColumn();
                iteminfo = RenderCommDetails(current_comm);
                break;
            case MOD:
                iteminfocolumn = RenderModDetailsColumn();
                iteminfo = RenderModDetails(current_mod);
                break;
            default:
                iteminfocolumn = text("");
                iteminfo = text("");
                break;
        }
        RenderDetails();
        return hbox({panel, detailpanel } ) | border;
    }

    void RenderList(){

        list->DetachAllChildren();
        auto& model = game->getModel();
        auto modules = model.get_modules();
        auto commodities = model.get_commodities();

        for(auto& i: modules){
            if(i.second.amount > 0){
                list->Add(RenderModule(i));
            }
        }
        for(auto& i: commodities){
            if(i.second.amount > 0){
                list->Add(RenderCommodity(i));
            }
        }
        if(list->ChildCount() == 0){
            list->Add(ftxui::Renderer([]{return ftxui::text("Inventory empty");}));
        }
        panel = list->Render() | ftxui::border | ftxui::xflex_grow;
    }

    void RenderDetails(){
        using namespace ftxui;
        detailpanel = hbox({iteminfocolumn, iteminfo}) | size(WIDTH, GREATER_THAN, DETAIL_WIDTH) | border;
    }

    ftxui::Component RenderModule(std::pair<ent::Module, ent::Meta>& module){
        using namespace ftxui;
        ent::Module m = module.first;
        return Container::Horizontal({
            Button("Details", [m, this]{current_mod = m; state = MOD;}),
            Renderer([&]{return filler();}),
            Button("Equip", [&]{game->getModel().equip_module(module.first);}),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(module.first.name);
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(fmti(module.second.amount));
            })
        });
    }

    ftxui::Component RenderCommodity(std::pair<ent::Commodity, ent::Meta>& commodity){
        using namespace ftxui;
        ent::Commodity c = commodity.first;
        return Container::Horizontal({
            Button("Details", [c, this]{current_comm = c; state = COMM;}),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(commodity.first.name);
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(fmti(commodity.second.amount));
            })
        });
    }

    ftxui::Element RenderCommDetailsColumn(){
        using namespace ftxui;
        return vbox({
            text("Commodity:"),
            separator(),
            text("Commodity type:"),
            text("Average price:"),
            text("Description:"),
        }) |
        yflex;
    }

    ftxui::Element RenderCommDetails(ent::Commodity& comm){
        using namespace ftxui;
        return vbox({
        text(fmt(comm.name) + fmtbi(comm.id)),
        separator(),
        text(comm.type.name),
        text(fmti(comm.price)),
        }) |
        xflex_grow;
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

    ftxui::Element RenderModDetails(ent::Module& mod){
        using namespace ftxui;
        return vbox({
        text(fmt(mod.name) + fmtbi(mod.id)),
        separator(),
        text(mod.type.name),
        text(fmti(mod.price)),
        }) |
        xflex_grow;
    }
};

ftxui::Component Inventory(Game& game) {
  return ftxui::Make<InventoryBase>(game);
}

}