#include "db/database.hpp"

#include "model/ship.hpp"

using namespace md;

// ----- Ship ----- //

Ship::Ship(){
    frame = db::Connector::select_single_frame(1);
    auto mod = db::Connector::select_module();
    equipped.push_back((*mod)[0]);
    equipped.push_back((*mod)[1]);
    equipped.push_back((*mod)[2]);
}

bool Ship::max_armr_slots(int id, int cur_slots){
    return (id == 1 && frame->slots.armr_slots == cur_slots);
}


bool Ship::max_weap_slots(int id, int cur_slots){
    return (id == 1 && frame->slots.weap_slots == cur_slots);
}

bool Ship::max_supp_slots(int id, int cur_slots){
    return (id == 1 && frame->slots.supp_slots == cur_slots);
}

bool Ship::can_equip_another(ent::Module& mod){
    int cur_slots;
    for(auto& i : equipped){
        if(i.type.id == mod.type.id){
            cur_slots++;
        }
    }
    int id = mod.type.id;
    if(max_armr_slots(id, cur_slots) || max_weap_slots(id, cur_slots) || max_supp_slots(id, cur_slots)){
        return false;
    }
    return true;
}

void Ship::equip(ent::Module& mod){
    equipped.push_back(mod);
}
ent::Module Ship::unequip(ent::Module& mod){
    ent::Module res = mod; //copy before erasing
    auto it = std::find_if(equipped.begin(), equipped.end(), 
                        [&](const auto& p){return p.id == mod.id;});
    if(it != equipped.end()){
        equipped.erase(it);
    }
    return res;
}
