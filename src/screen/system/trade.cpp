#include "trade.hpp"
#include "model/oututil.hpp"


namespace sc {
class TradeBase : public ftxui::ComponentBase{
public:
    enum states{NONE, COMM, MOD};
    static const int DETAIL_WIDTH = 40;
    Game* game;
    state::StateManager& state;
    ftxui::Component list = ftxui::Container::Vertical({});
    ftxui::Element iteminfocolumn = ftxui::text("");;
    ftxui::Element iteminfo = ftxui::text("");;
    ftxui::Element panel;
    ftxui::Element detailpanel;

    int details_render_state = NONE;
    ent::Commodity current_comm;
    ent::Module current_mod;

    TradeBase(Game& game_, state::StateManager& state_):
        game(&game_), state(state_)
    {
        Add(list);
    }

    ftxui::Element Render() override {
        using namespace ftxui;
        RenderList();
        switch(details_render_state){
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
        return hbox({panel | xflex_grow, detailpanel} ) | border;
    }

    void RenderList(){
        if(state.isDeprecated()){
            list->DetachAllChildren();
            std::vector<std::pair<ent::Commodity, ent::Meta>>& commodities = game->getModel().get_current_stock().get_commodities();
            //auto modules = game->getModel().get_current_stock().get_modules();
            // for(auto& i: modules){
            //     list->Add(RenderModule(i));
            // }
            for(auto& i: commodities){
                list->Add(RenderCommodity(i));
            }
            if(list->ChildCount() == 0){
                list->Add(ftxui::Renderer([]{return ftxui::text("Inventory empty");}));
            }
            state.commit();
        }
        panel = list->Render() | ftxui::border | ftxui::frame | ftxui::vscroll_indicator;
    }
    
    void RenderDetails(){
        using namespace ftxui;
        detailpanel = hbox({iteminfocolumn, iteminfo}) | size(WIDTH, GREATER_THAN, DETAIL_WIDTH) | border;
    }

    ftxui::Component RenderCommodity(std::pair<ent::Commodity, ent::Meta>& commodity){
        using namespace ftxui;
        ent::Commodity c = commodity.first;
        return Container::Horizontal({
            Button("Buy", [&]{game->getModel().trade_commodity(commodity.first, 1); state.deprecate();}, ButtonOption()),
            Button("Sell", [&]{game->getModel().trade_commodity(commodity.first, -1); state.deprecate();}, ButtonOption()),
            Button("Details", [c, this]{current_comm = c; details_render_state = COMM;}, ButtonOption()),
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
                return text(fmti(game->getModel().get_amount_of_commodity(commodity.first)));
            }),
            Renderer([&]{return filler();}),
            Renderer([&]{
                return text(fmti(commodity.second.price) + "cred");
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

ftxui::Component Trade(Game& game, state::StateManager& state) {
  return ftxui::Make<TradeBase>(game, state);
}

}