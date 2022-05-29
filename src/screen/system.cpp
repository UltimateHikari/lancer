#include "system.hpp"

#include "model/entities.hpp"
#include "model/model.hpp"
#include "model/oututil.hpp"

#include "graph.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

#include "system/inventory.hpp"
#include "system/navigation.hpp"
#include "system/ship.hpp"
#include "system/trade.hpp"
#include <functional>

namespace sc{

class SystemBase: public ftxui::ComponentBase{
public:
    Game& game;
    state::StateManager& state;
    int depth = 0;
    md::BattleResult last_result;
    int tab_index = 0;
    std::vector<std::string> tab_entries = {
        "Ship", "Navigation", "Inventory", "Trade", "Test"
    };
    ftxui::Component tab_selection = ftxui::Toggle(&tab_entries, &tab_index);
    ftxui::Component tab_content;
    ftxui::Component footer;
    ftxui::Component main_container;
    ftxui::Component main_renderer;
    ftxui::Component depth_1_container;
    ftxui::Component depth_1_renderer;
    ftxui::Component layered_container;
    ftxui::Component layered_renderer;

    std::function<void(md::BattleResult)> onEncounter = 
        [&](md::BattleResult r){if(r.has_occured){depth = 1;} last_result = r;};

    Graph logo_graph;

    SystemBase(Game& game_, state::StateManager& state_):
        game(game_), state(state_)
    {
        using namespace ftxui;
        tab_content = ftxui::Container::Tab(
        {
            sc::Ship(game),
            sc::Navigation(game, onEncounter, state),
            sc::Inventory(game),
            sc::Trade(game),
            ftxui::Button("ovelray", [&]{depth = 1;})
        },
        &tab_index);

        footer = renderFooter();

        main_container = Container::Vertical({
            tab_selection,
            tab_content,
            footer
        });

        main_renderer = Renderer(main_container, [&] {
            return vbox({
                text("lancer") | bold | hcenter,
                tab_selection->Render() | hcenter,
                tab_content->Render() | flex,
                footer->Render() 
            }) | xflex_grow;
        });

        depth_1_container = Container::Horizontal({
            Button("ok", [&] {depth = 0;}),
        });

        depth_1_renderer = Renderer(depth_1_container, [&] {
            return vbox({
                    text(last_result.log),
                    separator(),
                    hbox(depth_1_container->Render()),
                }) |
                border;
        });

        layered_container = Container::Tab(
            {
                main_renderer,
                depth_1_renderer,
            },
            &depth);

        layered_renderer = Renderer(layered_container, [&] {
            ftxui::Element document = main_renderer->Render();

            if (depth == 1) {
            document = dbox({
                document,
                depth_1_renderer->Render() | clear_under | center,
            }) | xflex_grow | yflex_grow;
            }
            return document;
        });
        Add(layered_renderer);
    };

    ftxui::Element Render() override {
        using namespace ftxui;
        return layered_renderer->Render();
    }

    ftxui::Component renderFooter(){
    using namespace ftxui;
    return Container::Vertical({
        Container::Horizontal({
            Renderer([]{return filler();}),
            Renderer([&]{return text("Current time: " + fmti(game.getModel().get_time()) + "day") | flex | hcenter;}),
            Renderer([]{return filler();}),
            Renderer([&]{return text("Current balance: " + fmti(game.getModel().get_balance()) + "credits") | flex | hcenter;}),
            Renderer([]{return filler();}),
            Renderer([&]{return text("Battles won: " + fmti(game.getModel().get_battles_won()) + "battles") | flex | hcenter;}),
            Renderer([]{return filler();})
        }),
        Container::Horizontal({
            Renderer([]{return filler();}),
            Renderer([&]{return text(game.getModel().last_log.out()) | flex | hcenter;}),
            Renderer([]{return filler();}),
        })
    });
}
    
};

ftxui::Component System(Game& game, state::StateManager& state) {
  return ftxui::Make<SystemBase>(game, state);
}

}