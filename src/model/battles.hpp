#ifndef BATTLES_HPP
#define BATTLES_HPP

#include <string>
#include <random> 

#include "model/entities.hpp"
#include "model/oututil.hpp"

#include "easyloggingpp/easylogging++.h"

namespace md{

enum BotType {
    NONE = 0,
    WEAK_BOT = 1,
    MIDDLE_BOT = 3,
    TOUGH_BOT = 5
};

class BattleResult{
public:
    std::string log;
    bool has_occured = false;
    bool was_won = true;
    BattleResult(){};
    BattleResult(std::string log_, bool was_won_): 
        log(log_), 
        was_won(was_won_) 
    {has_occured = true;};
};

class BattleRepresentation{
public:
    size_t attackRating = 0;
    size_t defenseRating = 0;
    BotType bot = NONE;
    static const int BOT_BASE = 10;
    BattleRepresentation(ent::ShipFrame& frame, std::vector<ent::Module>& modules){
        defenseRating = frame.params.evasion/10 + frame.params.structure/10 + frame.params.speed/10;
        for(auto& i: modules){
            if(i.type.name == "weapon"){
                attackRating += BOT_BASE;
            }
        }
    }
    BattleRepresentation(BotType type){
        bot = NONE;
        attackRating = BOT_BASE*type;
        defenseRating = BOT_BASE*type;
    }
};

class BattleStage{
public:
    static const int MAX_THRESHOLD = 60;
    static const int WEAK_BOT_THRESHOLD = 30;
    static const int MIDDLE_BOT_THRESHOLD = 45;
    static const int TOUGH_BOT_THRESHOLD = 55;
    static BattleResult getRandomizedBattleEncounter(ent::ShipFrame& frame, std::vector<ent::Module>& modules){ 
        std::random_device rd; 
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, MAX_THRESHOLD);
        int res = distrib(gen);
        LOG(INFO) << "battle num:" << res;
        if(res >= TOUGH_BOT_THRESHOLD){
            return getBattleResult({frame, modules}, {BotType::TOUGH_BOT});
        }
        if(res >= TOUGH_BOT_THRESHOLD){
            return getBattleResult({frame, modules}, {BotType::MIDDLE_BOT});
        }
        if(res >= TOUGH_BOT_THRESHOLD){
            return getBattleResult({frame, modules}, {BotType::WEAK_BOT});
        }
        return {};
    }
    static BattleResult getBattleResult(BattleRepresentation you, BattleRepresentation enemy){
        size_t yourWinTime = enemy.defenseRating/you.attackRating;
        size_t enemyWinTime = you.defenseRating/enemy.attackRating;
        if(enemyWinTime > yourWinTime) return {"Win with bot type " + fmti(enemy.bot), true};
        return {"Loss from bot type "+ fmti(enemy.bot), false};
    }
};

}

#endif
