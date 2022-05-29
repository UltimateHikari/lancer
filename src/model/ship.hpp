#ifndef LANCER_MODEL_SHIP_HPP
#define LANCER_MODEL_SHIP_HPP

#include "model/entities.hpp"
#include "model/battles.hpp"

namespace md{

class Ship {
private:
    bool max_armr_slots(int id, int cur_slots);
    bool max_weap_slots(int id, int cur_slots);
    bool max_supp_slots(int id, int cur_slots);
public:
    std::shared_ptr<ent::ShipFrame> frame = {};
    std::vector<ent::Module> equipped;
    Ship();
    bool can_equip_another(ent::Module& mod);
    void equip(ent::Module& mod);
    ent::Module unequip(ent::Module& mod);
};

};
#endif