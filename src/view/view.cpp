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

#include "easyloggingpp/easylogging++.h"

using namespace sc;
using namespace ftxui;

//  FTXUI/examples/dom/graph.cpp 

enum refresh{CONTINUE,PAUSE,STOP};

bool isExitEvent(Event event){
    return event == Event::Character('q') || event == Event::Escape;
}


void View::show(Game& game){
    auto screen = ScreenInteractive::Fullscreen();

    //game.setTicker([&]{screen.PostEvent(Event::Custom);});

    onExit = [&]{game.getTicker().stop(); screen.ExitLoopClosure()(); };
    game.onEnd = onExit;

    state::StateManager state;
    state.stateChangeEvent = [&]{screen.PostEvent(Event::Custom);};
    // auto container = ftxui::Renderer([&]{return flexbox({})})

    auto container = ftxui::Container::Horizontal({});
    container->Add(sc::Menu(game, state));

    auto event_container = CatchEvent(container, 
        [&](Event event) {
            if(event == Event::Custom){
                ///LOG(INFO) << "custom seen";
                container->DetachAllChildren();
                container->Add(ScreenFactory::getScreenForState(game, state));
                return true;
            }
            if (isExitEvent(event)) {
                if(state.getCurrent() == state::Menu){
                    screen.ExitLoopClosure()();
                    return true;
                }
                state.onStateChange(state::Back);
                container->DetachAllChildren();
                container->Add(ScreenFactory::getScreenForState(game, state));
                return true;
            }
            if(event == ftxui::Event::Character('o')){
                game.getModel().cheat_victory();
                screen.PostEvent(Event::Custom);
                return true;
            }
            return false;
        }
    );

    screen.Loop(event_container);
}