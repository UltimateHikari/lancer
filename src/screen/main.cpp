#include "main.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

#include "model/model.hpp"

using namespace sc;
using namespace ftxui;


void Main::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    auto option = ButtonOption();
    option.border = false;

    Model& model = game.getModel();

    auto start_button = Button("New game", [&]{game.start(); System::show(game);}, &option);
    auto save_button = Button("Save game", []{}, &option);
    auto load_button = Button("Load game", []{}, &option);
    auto lead_button = Button("Leaderboards", []{}, &option);
    auto setting_button = Button("Settings", []{}, &option);
    auto exit_button = Button("Exit", screen.ExitLoopClosure(), &option);

    Component first_button, second_button;

    //TODO not working as intended (change after going back)

    if(!model.is_game_active()){
        first_button = start_button;
        second_button = load_button;
    }else{
        first_button = save_button;
        second_button = load_button;
    }

    auto renderer = Renderer(
        Container::Vertical({
            first_button,
            second_button,
            lead_button,
            setting_button,
            exit_button
        }), 
        [&]{return vbox({
            text(L" lancer "),
            separator(),
            first_button->Render(),
            second_button->Render(),
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

    first_button->TakeFocus();

    screen.Loop(final_container);
}


void System::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

///// placeholder

    auto spinner_tab_renderer = Renderer([&] {
    Elements entries;
    int shift = 0;
    for (int i = 0; i < 22; ++i) {
        entries.push_back(spinner(i, shift / 2) | bold |
                    size(WIDTH, GREATER_THAN, 2) | border);
    }
    return hflow(std::move(entries)) | border;
    });

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
        spinner_tab_renderer,
        spinner_tab_renderer2,
        spinner_tab_renderer3
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