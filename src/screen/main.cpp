#include "main.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"

using namespace sc;
using namespace ftxui;

Main::Main(){
    ftxui::ScreenInteractive screen = ScreenInteractive::Fullscreen();
    entries = std::vector<Entry>{
        entries::Start()/*,
        entries::Exit(&screen)*/
    };
    entries_content = entries_to_string(entries);
}

void Main::show(){
    auto screen = ScreenInteractive::Fullscreen();

    auto main_menu = Menu(entries_content.get(), &menu_selected);

    auto renderer = Renderer(main_menu, [&]{
        return vbox({
            text(L" lancer "),
            separator(),
            main_menu->Render(),
        }) |
            border;
    });

    auto final_container = CatchEvent(renderer, [&](Event event) {
    
    if (event == Event::Character('q') || event == Event::Escape) {
        screen.ExitLoopClosure()();
        return true;
    }

    return false;
    });

    main_menu->TakeFocus();

    screen.Loop(final_container);
}