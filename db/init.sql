INSERT INTO corporation(name) VALUES ("G.H.O.S.T");
INSERT INTO corporation(name) VALUES ("Better World");
INSERT INTO corporation(name) VALUES ("Yareli");
INSERT INTO corporation(name) VALUES ("ReVolt Inc.");


INSERT INTO commodity_type(name) VALUES ("essential");
INSERT INTO commodity_type(name) VALUES ("illegal");
INSERT INTO commodity_type(name) VALUES ("industrial");
INSERT INTO commodity_type(name) VALUES ("commodity");
INSERT INTO commodity_type(name) VALUES ("ore");

INSERT INTO commodity(type_id, manufacturer_id, name) VALUES (1, 1, "Medical supplies");
INSERT INTO commodity(type_id, manufacturer_id, name) VALUES (2, 1, "Organs");
INSERT INTO commodity(type_id, manufacturer_id, name) VALUES (4, 1, "Luxury");

INSERT INTO frame_class(name) VALUES ("interceptor");
INSERT INTO frame_class(name) VALUES ("fighter");
INSERT INTO frame_class(name) VALUES ("trader");
INSERT INTO frame_class(name) VALUES ("aviso");
INSERT INTO frame_class(name) VALUES ("corvette");
INSERT INTO frame_class(name) VALUES ("destroyer");

INSERT INTO frame(
    class_id, manufacturer_id, 
    name,
    weap_slots, armr_slots, supp_slots,
    energy, inventory_size,
    structure_points, speed, evasion)
VALUES(
    5,1,
    "Dark Angel",
    4,6,6,
    200,40,
    600,100,10
);

INSERT INTO module_type(name) VALUES ("weapon");
INSERT INTO module_type(name) VALUES ("armor");
INSERT INTO module_type(name) VALUES ("support");

INSERT INTO element(name) VALUES ("solar");
INSERT INTO element(name) VALUES ("arc");
INSERT INTO element(name) VALUES ("void");

INSERT INTO module(
    type_id, manufacturer_id,
    name,
    element_id,energy_cost,initial_cost,
    damage,accuracy,cooldown,
    structure_points,
    speed_modifier, evasion_modifier, energy_modifier,
    inventory_modifier, drill_profit_modifier
)
VALUES(
    1,1,
    "Pulse laser",
    1,20,100,
    40,85,5,
    0,
    0,0,0,
    0,0
);

INSERT INTO module(
    type_id, manufacturer_id,
    name,
    element_id,energy_cost,initial_cost,
    damage,accuracy,cooldown,
    structure_points,
    speed_modifier, evasion_modifier, energy_modifier,
    inventory_modifier, drill_profit_modifier
)
VALUES(
    2,1,
    "Delta shield",
    2,100,1000,
    0,0,0,
    100,
    20,0,0,
    0,0
);

INSERT INTO module(
    type_id, manufacturer_id,
    name,
    element_id,energy_cost,initial_cost,
    damage,accuracy,cooldown,
    structure_points,
    speed_modifier, evasion_modifier, energy_modifier,
    inventory_modifier, drill_profit_modifier
)
VALUES(
    3,1,
    "External cargo bay",
    3,0,100,
    0,0,0,
    0,
    -10,0,0,
    40,0
);

--- Nodes 1 - 5 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Eternity",
    2,2,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Arcadia",
    2,2,10,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Radiance",
    4,2,8,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Remgolia",
    5,2,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Saidai",
    1,2,2,10
);

--- Nodes 6 - 10 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Pranelius",
    1,4,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Taxopia",
    3,1,10,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Nadorkon",
    3,1,8,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Wunarnia",
    3,3,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Korog",
    3,1,2,10
);

--- Nodes 11 - 15 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Tau Naraka",
    4,1,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Aviz",
    4,3,10,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Darkumi",
    1,3,8,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Kuorkon",
    2,3,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Ganeaux",
    2,3,2,10
);

--- Nodes 16 - 20 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Zeta",
    5,3,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Longpid",
    5,3,10,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Noella",
    2,3,8,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Carankor",
    2,4,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Farenella",
    2,1,2,10
);

--- Nodes 21 - 25 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Paplos",
    4,1,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Satacan",
    5,4,10,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Vullak",
    5,4,8,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Sizeonon",
    5,4,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Scarva",
    1,4,2,10
);

--- Nodes 25 - 30 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Baniru",
    4,4,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Ceti",
    4,4,10,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Nitkail",
    4,2,8,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Durreus",
    3,2,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Funfiner",
    3,4,2,10
);




INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    1,2,10,"TRUE"
);

INSERT INTO encounter(name, weight)
    VALUES("Pirate attack", 10);
INSERT INTO encounter(name, weight)
    VALUES("Corporation war", 10);
INSERT INTO encounter(name, weight)
    VALUES("Resourse shortage", 5);
INSERT INTO encounter(name, weight)
    VALUES("Miners strike", 10);
INSERT INTO encounter(name, weight)
    VALUES("Solar blast", 1);
INSERT INTO encounter(name, weight)
    VALUES("Relay sabotage", 3);

INSERT INTO modificator_type(name)
    VALUES("System");
INSERT INTO modificator_type(name)
    VALUES("Neighbouring systems");
INSERT INTO modificator_type(name)
    VALUES("Corporation-owned");

INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    1,1,
    "Pirates defeated",
    4,2,0
);

INSERT INTO saved_game(name, date)
    VALUES("Test_game", "2022-03-26 14:44:33");

INSERT INTO saved_commodities(save_id, comm_id, amount)
    VALUES(1,1,10);
INSERT INTO saved_commodities(save_id, comm_id, amount)
    VALUES(1,2,20);
INSERT INTO saved_commodities(save_id, comm_id, amount)
    VALUES(1,3,30);

INSERT INTO saved_modules(save_id, mod_id, amount)
    VALUES(1,1,1);
INSERT INTO saved_modules(save_id, mod_id, amount)
    VALUES(1,2,2);