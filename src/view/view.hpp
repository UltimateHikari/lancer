#ifndef VIEW_HPP
#define VIEW_HPP

#include "game.hpp"
#include "ticker.hpp"

class View{
private:
    Ticker ticker;
public:
    View();
    void show(Game& game){};
};

#endif
