#include "trade.hpp"
#include "model/oututil.hpp"


namespace sc {
class TradeBase : public ftxui::ComponentBase{
public:
    static const int DETAIL_WIDTH = 40;
    Game* game;
    ftxui::Component list;
    ftxui::Element iteminfocolumn;
    ftxui::Element iteminfo;
    ftxui::Element panel;
    ftxui::Element detailpanel;

    TradeBase(Game& game_){
        using namespace ftxui;
        list = Container::Vertical({});
        iteminfocolumn = text("");
        iteminfo = text("");
        Add(list);
        this->game = &game_;
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        RenderList();
        RenderDetails();
        return hbox({panel | xflex_grow, detailpanel} ) | border;
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
        panel = list->Render() | ftxui::border;
    }
    
    void RenderDetails(){
        using namespace ftxui;
        detailpanel = hbox({iteminfocolumn, iteminfo}) | size(WIDTH, GREATER_THAN, DETAIL_WIDTH) | border;
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