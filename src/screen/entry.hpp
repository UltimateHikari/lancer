#ifndef ENTRY_SCREEN_HPP
#define ENTRY_SCREEN_HPP

#include <iostream>

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>

#include "ftxui/component/screen_interactive.hpp"


namespace sc{
    struct Entry{
        std::string content;
        std::function<void ()> callback;
    };

    namespace entries{
        struct Start : Entry{
            Start(){
                content = "start";
                callback = [&]{std::cerr << "started";};
            }
        };

        struct Exit : Entry{
            Exit(ftxui::ScreenInteractive& screen){
                content = "exit";
                callback = screen.ExitLoopClosure();
            }
        };
    }

    std::unique_ptr<std::vector<std::string>> entries_to_string(const std::vector<Entry>& entries);
}

#endif
