#include "inventory.hpp"

#include <vector>
#include <memory>
#include "model/entities.hpp"
#include "model/model.hpp"

#include <ftxui/component/event.hpp> 



namespace sc{

class InventoryBase : public ftxui::ComponentBase{
public:
    Game* game;
    ftxui::Component list;
    ftxui::Component info;
    ftxui::Element panel;

    InventoryBase(Game& game_){
        using namespace ftxui;
        list = Container::Vertical({});
        info = Renderer([] {return text("item info") | center;});;
        Add(list);
        this->game = &game_;
    }

    ftxui::Element Render() override {
        RenderList();
        return ftxui::hflow({panel, info->Render()}) | ftxui::border;
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
        panel = list->Render() | ftxui::borderDouble;
    }

    ftxui::Component RenderModule(std::pair<ent::Module, ent::Meta>& module){
        using namespace ftxui;
        return Container::Horizontal({
            Button("Details", []{}),
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
            Button("Details", []{}),
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
};

ftxui::Component Inventory(Game& game) {
  return ftxui::Make<InventoryBase>(game);
  //return ftxui::Renderer([&]{return RenderLines(game);});
}

}