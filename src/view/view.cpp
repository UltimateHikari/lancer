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

#include <cmath>
#include <chrono>
#include <thread>

using namespace sc;
using namespace ftxui;

//  FTXUI/examples/dom/graph.cpp 

enum refresh{CONTINUE,PAUSE,STOP};

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

void Main_show(Game& game);
void Load_show(Game& game);
void System_show(Game& game);

void Main_show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    auto option = ButtonOption();
    option.border = false;

    auto refresh_ui_continue = CONTINUE;


    ftxui::Component renderer;

    auto start_button = Button("New game", [&]{game.start(); refresh_ui_continue=STOP; System_show(game);}, &option);
    auto save_button = Button("Save game", []{}, &option);
    auto load_button = Button("Load game", [&]{Load_show(game);}, &option);
    auto lead_button = Button("Leaderboards", []{}, &option);
    auto setting_button = Button("Settings", []{}, &option);
    auto exit_button = Button("Exit", screen.ExitLoopClosure(), &option);

    renderer =  Renderer(
        Container::Vertical({
            start_button,
            save_button,
            load_button,
            lead_button,
            setting_button,
            exit_button
        }),  
        [&]{return vbox({
            text(L" lancer "),
            separator(),
            start_button->Render(),
            save_button->Render(),
            load_button->Render(),
            lead_button->Render(),
            setting_button->Render(),
            exit_button->Render(),
        }) |
            border;
    });
    
    Graph logo_graph;

    const int min_width = 40;

    auto logo = Renderer([&] {
        return graph(std::ref(logo_graph)) 
        | center | color(Color::BlueLight) | xflex_grow | yflex_grow | bgcolor(Color::White);} );

    std::thread refresh_ui([&] {
        while (refresh_ui_continue != STOP) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s);
            if(refresh_ui_continue == CONTINUE){
                logo_graph.shift++;
                screen.PostEvent(Event::Custom);
            }
        }
    });

    int left_size = 20;

    auto container = renderer;
    container = Container::Horizontal({container, logo});



    auto final_container = CatchEvent(container, [&](Event event) {
        if (event == Event::Character('q') || event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }
        
        return false;
    });

    screen.Loop(final_container);
    refresh_ui_continue=STOP;
    refresh_ui.join();
}

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