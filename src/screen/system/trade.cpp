#include "trade.hpp"
#include "model/oututil.hpp"


namespace sc {
class TradeBase : public ftxui::ComponentBase{
public:
    Game* game;
    ftxui::Component list;
    ftxui::Component info;
    ftxui::Element panel;

    TradeBase(Game& game_){
        using namespace ftxui;
        list = Container::Vertical({});
        info = Renderer([] {return text("trade item info") | center;});;
        Add(list);
        this->game = &game_;
    }

    ftxui::Element Render() override {
        RenderList();
        return ftxui::hflow({panel, info->Render()}) | ftxui::border;
    }

    void RenderList(){
        list->DetachAllChildren();
        std::vector<std::pair<ent::Commodity, ent::Meta>>& commodities = game->getModel().get_current_stock().get_commodities();
        //auto modules = game->getModel().get_current_stock().get_modules();
        // for(auto& i: modules){
        //     list->Add(RenderModule(i));
        // }
        int a = 0; //TODO remove with true random
        for(auto& i: commodities){
            list->Add(RenderCommodity(i));
            a++;
            if(a==10){
                break;
            }
        }
        if(list->ChildCount() == 0){
            list->Add(ftxui::Renderer([]{return ftxui::text("Inventory empty");}));
        }
        panel = list->Render() | ftxui::borderDouble;
    }

    ftxui::Component RenderCommodity(std::pair<ent::Commodity, ent::Meta>& commodity){
        using namespace ftxui;
        return Container::Horizontal({
            Button("Buy", [&]{game->getModel().trade_commodity(commodity.first, 1);}, ButtonOption()),
            Button("Sell", [&]{game->getModel().trade_commodity(commodity.first, -1);}, ButtonOption()),
            Button("Details", []{}, ButtonOption()), //TODO add details
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(commodity.first.name);
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(fmti(commodity.second.amount));
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(fmti(commodity.second.price) + "cred");
            })
        });
    }
};

ftxui::Component Trade(Game& game) {
  return ftxui::Make<TradeBase>(game);
}

}