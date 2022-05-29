#ifndef VIEW_HPP
#define VIEW_HPP

#include "game.hpp"
#include <functional>

class View{
public:
    std::function<void()> onExit;
    void show(Game& game);
};

#endif
