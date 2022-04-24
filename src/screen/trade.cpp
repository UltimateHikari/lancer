#include "screen/trade.hpp"

namespace sc {
class TradeBase : public ftxui::ComponentBase{
public:
    Game* game;
    TradeBase(Game& game_){
        this->game = &game_;
    }
};

ftxui::Component Trade(Game& game) {
  return ftxui::Make<TradeBase>(game);
}

}