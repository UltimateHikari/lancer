#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include "screen/entry.hpp"
#include "game.hpp"
#include "ftxui/component/screen_interactive.hpp"

namespace sc{

    class System{
        public:
            static void show(Game& game);
    };

    class Main{
        public:
            static void show(Game& game);
    };

}

#endif
