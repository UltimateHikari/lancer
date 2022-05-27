#include "view.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include "model/model.hpp"
#include "model/oututil.hpp"

#include "screen/system/ship.hpp"
#include "screen/system/inventory.hpp"
#include "screen/system/navigation.hpp"
#include "screen/system/trade.hpp"

#include "view/state.hpp"
#include "view/screenfactory.hpp"

#include <cmath>
#include <chrono>
#include <thread>

using namespace sc;
using namespace ftxui;

//  FTXUI/examples/dom/graph.cpp 

enum refresh{CONTINUE,PAUSE,STOP};

bool isExitEvent(Event event){
    return event == Event::Character('q') || event == Event::Escape;
}

void View::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    onExit = [&]{ticker.stop(); screen.ExitLoopClosure()(); };
    game.onEnd = onExit;
    
    ticker = Ticker([&]{screen.PostEvent(Event::Custom);});
    // TODO pass him inside;
    state::StateManager state;

    auto container = ftxui::Container::Horizontal({});
    container->Add(sc::Menu(game, state));

    auto event_container = CatchEvent(container, 
        [&](Event event) {
            if(event == Event::Custom){
                container->DetachAllChildren();
                container->Add(ScreenFactory::getScreenForState(game, state));
                return true;
            }
            if (state.getCurrent() == state::Menu && isExitEvent(event)) {
                screen.ExitLoopClosure()();
                return true;
            }
            return false;
        }
    );

    screen.Loop(event_container);
}

namespace sc{

ftxui::Component Footer(Game& game){
    return Container::Vertical({
        Container::Horizontal({
            Renderer([]{return filler();}),
            Renderer([&]{return text("Current time: " + fmti(game.getModel().get_time()) + "day") | flex | hcenter;}),
            Renderer([]{return filler();}),
            Renderer([&]{return text("Current balance: " + fmti(game.getModel().get_balance()) + "credits") | flex | hcenter;}),
            Renderer([]{return filler();}),
        }),
        Container::Horizontal({
            Renderer([]{return filler();}),
            Renderer([&]{return text(game.getModel().last_log.out()) | flex | hcenter;}),
            Renderer([]{return filler();}),
        })
    });
}

}



void Main_show(Game& game){};
void Load_show(Game& game);
void System_show(Game& game);


Component RenderSave(ent::SavedGame& game, std::function<void()> on_click){
    return Container::Horizontal({
        Button(game.name, on_click),
        Renderer([&]{return text(game.date);})
    });
}

void Load_show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    auto option = ButtonOption();
    option.border = false;

    ftxui::Components children;

    auto saved_games = game.get_saved_games();

    for(auto& i: (*saved_games.get())){
        children.push_back(RenderSave(i, [&]{
            screen.ExitLoopClosure();
             game.getModel().load_game(i.id);
              game.start();
               System_show(game);
               }));
    }

    auto containerb = Container::Vertical(std::move(children));

    auto renderer = Renderer(containerb, [&]{
        return vbox({
            text(L" load game "),
            separator(),
            containerb->Render()
        });
    });

    auto logo = Renderer([] {return text("logo") | center;});

    int left_size = 20;

    auto container = renderer;
    container = ResizableSplitLeft(container, logo, &left_size);

    auto final_container = CatchEvent(container, 
        [&](Event event) {
            if (event == Event::Character('q') || event == Event::Escape) {
                screen.ExitLoopClosure()();
                return true;
            }
            return false;
        }
    );

    screen.Loop(final_container);
}

void System_show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    int depth = 0;
    int tab_index = 0;
    std::vector<std::string> tab_entries = {
        "Ship", "Navigation", "Inventory", "Trade", "Test"
    };
    auto tab_selection = Toggle(&tab_entries, &tab_index);
    
    auto tab_content = Container::Tab(
    {
        sc::Ship(game),
        sc::Navigation(game),
        sc::Inventory(game),
        sc::Trade(game),
        ftxui::Button("ovelray", [&]{depth = 1;})
    },
    &tab_index);

    auto footer = sc::Footer(game);

    auto main_container = Container::Vertical({
        tab_selection,
        tab_content,
        footer
    });

    auto main_renderer = Renderer(main_container, [&] {
        return vbox({
            text("lancer") | bold | hcenter,
            tab_selection->Render() | hcenter,
            tab_content->Render() | flex,
            footer->Render() 
        });
    });

    // At depth=1, The "modal" window.
    std::vector<std::string> rating_labels = {
        "1/5 stars", "2/5 stars", "3/5 stars", "4/5 stars", "5/5 stars",
    };
    auto depth_1_container = Container::Horizontal({
        Button(&rating_labels[0], [&] {depth = 0;}),
        Button(&rating_labels[1], [&] {depth = 0;}),
        Button(&rating_labels[2], [&] {depth = 0;}),
        Button(&rating_labels[3], [&] {depth = 0;}),
        Button(&rating_labels[4], [&] {depth = 0;}),
    });

    auto depth_1_renderer = Renderer(depth_1_container, [&] {
        return vbox({
                text("Do you like FTXUI?"),
                separator(),
                hbox(depth_1_container->Render()),
            }) |
            border;
    });

    auto layered_container = Container::Tab(
        {
            main_renderer,
            depth_1_renderer,
        },
        &depth);

    auto layered_renderer = Renderer(layered_container, [&] {
        ftxui::Element document = main_renderer->Render();

        if (depth == 1) {
        document = dbox({
            document,
            depth_1_renderer->Render() | clear_under | center,
        });
        }
        return document;
    });
 
    auto final_container = CatchEvent(layered_renderer, [&](Event event) {
    
    if (event == Event::Character('q') || event == Event::Escape) {
        //TODO ask to save?
        screen.ExitLoopClosure()();
        return true;
    }
    return false;
    });

    screen.Loop(final_container);
}