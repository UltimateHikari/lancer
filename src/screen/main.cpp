#include "main.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

using namespace sc;
using namespace ftxui;


void Main::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    auto option = ButtonOption();
    option.border = false;

    auto start_button = Button("Start game", [&]{game.start();}, &option);
    auto lead_button = Button("Leaderboards", []{}, &option);
    auto setting_button = Button("Settings", []{}, &option);
    auto exit_button = Button("Exit", screen.ExitLoopClosure(), &option);

    auto layout = Container::Vertical({
        start_button,
        lead_button,
        setting_button,
        exit_button
    });

    auto renderer = Renderer(layout, [&]{
        return vbox({
            text(L" lancer "),
            separator(),
            start_button->Render(),
            separator(),
            lead_button->Render(),
            separator(),
            setting_button->Render(),
            separator(),
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

    start_button->TakeFocus();

    screen.Loop(final_container);
}