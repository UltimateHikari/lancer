#include "inventory.hpp"

#include <vector>
#include <memory>

#include "model/entities.hpp"
#include "model/oututil.hpp"
#include "model/model.hpp"

#include <ftxui/component/event.hpp> 



namespace sc{

enum states{NONE, COMM, MOD};

class InventoryBase : public ftxui::ComponentBase{
public:
    static const int DETAIL_WIDTH = 40;
    Game* game;
    ftxui::Component list;
    ftxui::Element iteminfocolumn;
    ftxui::Element iteminfo;
    ftxui::Element panel;
    ftxui::Element detailpanel;
    
    int state = NONE;
    ent::Commodity current_comm;

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
            //case MOD: //TODO
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
        return Container::Horizontal({
            Button("Details", []{}),
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
        return Container::Horizontal({
            Button("Details", [&]{current_comm = commodity.first; state = COMM;}),
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

    ftxui::Element RenderCommDetails(const ent::Commodity& comm){
        using namespace ftxui;
        return vbox({
        text(comm.name + " (" + std::to_string(comm.id) + ")"), //TODO - for debug purpose
        separator(),
        text(comm.type.name),
        text(fmti(comm.price)),
        }) |
        xflex_grow;
    }
};

ftxui::Component Inventory(Game& game) {
  return ftxui::Make<InventoryBase>(game);
  //return ftxui::Renderer([&]{return RenderLines(game);});
}

}