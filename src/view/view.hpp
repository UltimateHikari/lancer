#ifndef VIEW_HPP
#define VIEW_HPP

#include "game.hpp"
#include "ticker.hpp"
#include <functional>

class View{
private:
    Ticker ticker;
public:
    std::function<void()> onExit;
    void show(Game& game);
};

#endif
