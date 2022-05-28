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
    container->Add(sc::System(game, state));

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