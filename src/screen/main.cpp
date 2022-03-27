#include "main.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

#include "model/model.hpp"
#include "screen/inventory.hpp"
#include "database.hpp"

using namespace sc;
using namespace ftxui;

void Main::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    auto option = ButtonOption();
    option.border = false;

    ftxui::Component renderer;

    auto start_button = Button("New game", [&]{game.start(); System::show(game);}, &option);
    auto save_button = Button("Save game", []{}, &option);
    auto load_button = Button("Load game", [&]{Load::show(game);}, &option);
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
    
    auto logo = Renderer([] {return text("logo") | center;});

    int left_size = 20;

    auto container = renderer;
    container = ResizableSplitLeft(container, logo, &left_size);



    auto final_container = CatchEvent(container, [&](Event event) {
    
    if (event == Event::Character('q') || event == Event::Escape) {
        screen.ExitLoopClosure()();
        return true;
    }
    return false;
    });

    screen.Loop(final_container);
}

Component RenderSave(ent::SavedGame& game, std::function<void()> on_click){
    return Container::Horizontal({
        Button(game.name, on_click),
        Renderer([&]{return text(game.date);})
    });
}

void Load::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    auto option = ButtonOption();
    option.border = false;

    ftxui::Components children;

    auto saved_games = db::Connector::select_saved_game();

    for(auto& i: (*saved_games.get())){
        children.push_back(RenderSave(i, [&]{
            screen.ExitLoopClosure();
             game.getModel().load_game(i.id);
              game.start();
               System::show(game);
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

    auto final_container = CatchEvent(container, [&](Event event) {
    
    if (event == Event::Character('q') || event == Event::Escape) {
        screen.ExitLoopClosure()();
        return true;
    }
    return false;
    });

    screen.Loop(final_container);
}

Component spinner_tab_renderer(){
    return Renderer([&] {
    Elements entries;
    int shift = 0;
    for (int i = 0; i < 22; ++i) {
        entries.push_back(spinner(i, shift / 2) | bold |
                    size(WIDTH, GREATER_THAN, 2) | border);
    }
    return hflow(std::move(entries)) | border;
    });
}

Component time_renderer(Game& game){
    return Renderer([&]{ 
        return hflow({text(game.getModel().get_time())}) | border;
        });
}

Component navigation_renderer(Game& game){
    return time_renderer(game);
}



Component inventory_renderer(Game& game){
    auto module_container = Container::Vertical({});
    auto commodity_container = Container::Vertical({});
    auto container = Container::Vertical({
        std::move(module_container),
        std::move(commodity_container)
    });
    return Renderer(container, [&]{
        return vbox({
            text(L" Inventory "),
            separator(),
            module_container->Render(),
            separator(),
            commodity_container->Render()
        });
    });
}

Component trade_renderer(Game& game){
    return time_renderer(game);
}

void System::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

///// placeholder

    auto spinner_tab_renderer2 = Renderer([&] {
    Elements entries;
    int shift = 0;
    for (int i = 0; i < 10; ++i) {
        entries.push_back(spinner(i, shift / 2) | bold |
                    size(WIDTH, GREATER_THAN, 2) | border);
    }
    return hflow(std::move(entries)) | border;
    });

    auto spinner_tab_renderer3 = Renderer([&] {
    Elements entries;
    int shift = 0;
    for (int i = 0; i < 5; ++i) {
        entries.push_back(spinner(i, shift / 2) | bold |
                    size(WIDTH, GREATER_THAN, 2) | border);
    }
    return hflow(std::move(entries)) | border;
    });

////

    int tab_index = 0;
    std::vector<std::string> tab_entries = {
        "Navigation", "Inventory", "Trade"
    };
    auto tab_selection = Toggle(&tab_entries, &tab_index);
    auto tab_content = Container::Tab(
    {
        navigation_renderer(game),
        sc::Inventory(game),
        trade_renderer(game)
    },
    &tab_index);

    auto main_container = Container::Vertical({
        tab_selection,
        tab_content,
    });

    auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("lancer") | bold | hcenter,
        tab_selection->Render() | hcenter,
        tab_content->Render() | flex,
    });
    });
 
    auto final_container = CatchEvent(main_renderer, [&](Event event) {
    
    if (event == Event::Character('q') || event == Event::Escape) {
        //TODO ask to save?
        screen.ExitLoopClosure()();
        return true;
    }
    return false;
    });

    screen.Loop(final_container);
}