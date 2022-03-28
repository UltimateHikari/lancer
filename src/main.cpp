#include <sqlite_orm/sqlite_orm.h>

#include <string>
#include <iostream>
#include <cassert>
#include "lancer.hpp"
#include "path.hpp"
#include "database.hpp"
#include <type_traits>


#include "ftxui/component/component.hpp"  // for Renderer, Button, CatchEvent, Checkbox, Horizontal, Menu, ResizableSplitLeft, Vertical
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/event.hpp"               // for Event
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/deprecated.hpp"                // for text
#include "ftxui/dom/elements.hpp"  // for operator|, text, separator, vbox, Element, Elements, bgcolor, size, xflex, color, filler, hbox, dim, EQUAL, WIDTH, flex, yflex
#include "ftxui/screen/color.hpp"  // for Color, Color::Black, Color::White
#include "scroller.hpp"            // for Scroller

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include "screen/main.hpp"
#include "game.hpp"

using namespace sqlite_orm;

using std::cout;
using std::cerr;
using std::endl;

struct RapArtist {
    int id;
    std::string name;
};

void orm_test(){
    auto storage = make_storage(":memory:",
                                make_table("rap_artists",
                                           make_column("id", &RapArtist::id, primary_key()),
                                           make_column("name", &RapArtist::name)));
    cout << "in memory db opened" << endl;
    storage.sync_schema();

    assert(!storage.count<RapArtist>());

    storage.insert(RapArtist{-1, "The Weeknd"});

    storage.transaction([&] {
        storage.insert(RapArtist{-1, "Drake"});
        return true;
    });

    cout << "rap artists count = " << storage.count<RapArtist>() << endl;

    //  transaction also work in memory..
    storage.transaction([&] {
        storage.insert(RapArtist{-1, "Kanye West"});
        return false;
    });

    cout << "rap artists count = " << storage.count<RapArtist>() << " (no Kanye)" << endl;
}

void lancer_test(){
    db::Connector::sync();
    db::Connector::select_corporation();
    auto comm = db::Connector::select_commodity();
    db::Connector::select_commodity_type();
    db::Connector::select_frame_class();
    db::Connector::select_frame();
    db::Connector::select_module_type();
    db::Connector::select_element();
    db::Connector::test_select_module();
    auto mod = db::Connector::select_module();
    auto gam = db::Connector::select_saved_game();
    auto smod = db::Connector::select_saved_module(1);
    auto scom = db::Connector::select_saved_commodity(1);
}

void ftxtest(){
    using namespace ftxui;

    auto summary = [&] {
        auto content = vbox({
            hbox({text(L"- done:   "), text(L"3") | bold}) | color(Color::Green),
            hbox({text(L"- active: "), text(L"2") | bold}) | color(Color::RedLight),
            hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
        });
        return window(text(L" Summary "), content);
    };

    auto document =  //
        vbox({
            hbox({
                summary(),
                summary(),
                summary() | flex,
            }),
            summary(),
            summary(),
        });

    // Limit the size of the document to 80 char.
    document = document | size(WIDTH, LESS_THAN, 80);

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);

    std::cout << screen.ToString() << std::endl;

}

void ftxtest2(){
    using namespace ftxui;

    auto button_option = ButtonOption();
    button_option.border = false;

    // File menu.
    int menu_selected = 0;
    std::vector<std::string> menu_entries = {"Entry 1", "Entry 2", "Entry 3"};
    auto file_menu = Menu(&menu_entries, &menu_selected);

    auto screen = ScreenInteractive::Fullscreen();
    
    auto file_menu_renderer = Renderer(file_menu, [&] {
    return vbox({
        text(L" Front "),
        separator(),
        file_menu->Render(),
    });
    });

    auto file_renderer = Renderer(file_menu, [&, file_menu] {
    //const File& file = files[file_menu_selected];
    return vbox({
                text(L" Back "),
                separator(),
                /*text(file.left_file + " -> " + file.right_file),
                separator(),*/
                file_menu->Render(),
            }) |
            flex;
    });

    int file_menu_width = 30;
    auto layout =
        ResizableSplitLeft(file_menu_renderer, file_renderer, &file_menu_width);

    auto layout_renderer = Renderer(layout, [&] {
    return layout->Render() | yflex;
    });

    auto main_container = Container::Vertical({
        layout_renderer,
    });

    auto final_container = CatchEvent(main_container, [&](Event event) {
    
    if (event == Event::Character('q') || event == Event::Escape) {
        screen.ExitLoopClosure()();
        return true;
    }

    return false;
    });

    file_menu->TakeFocus();

    screen.Loop(final_container);
}

int main(int, char**) {
    orm_test();
    lancer_test();
    sc::Main* screen = new sc::Main();

    Game* game = new Game();

    screen->show(*game);
    return 0;
}