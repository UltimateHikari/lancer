#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP

#include "screen/entry.hpp"
#include "ftxui/component/screen_interactive.hpp"

namespace sc{

    class Main{
        private:
            std::vector<Entry> entries;
            std::unique_ptr<std::vector<std::string>> entries_content;
            //ftxui::ScreenInteractive screen;
            int menu_selected = 0;
        public:
            Main();
            void show();
    };

}

#endif
