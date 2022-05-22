INSERT INTO corporation(name) VALUES ("G.H.O.S.T");
INSERT INTO corporation(name) VALUES ("Better World");
INSERT INTO corporation(name) VALUES ("Yareli");
INSERT INTO corporation(name) VALUES ("ReVolt Inc.");


INSERT INTO commodity_type(name) VALUES ("essential");
INSERT INTO commodity_type(name) VALUES ("illegal");
INSERT INTO commodity_type(name) VALUES ("industrial");
INSERT INTO commodity_type(name) VALUES ("commodity");
INSERT INTO commodity_type(name) VALUES ("ore");

INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (4, 3, "Alien Cats", 2000);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (1, 1, "Chemicals", 150);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (4, 3, "Collectibles", 50);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (2, 1, "Drugs", 80);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (3, 2, "Energy Contours", 120);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (4, 1, "Files", 10);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (2, 4, "Ghost Organs", 18000);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (4, 1, "Luxury", 1000);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (1, 3, "Medicine", 20);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (3, 1, "Nanotech", 800);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (5, 2, "Noble Gas", 200);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (2, 4, "Organs", 10000);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (3, 1, "Plastics", 250);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (4, 4, "Rare Food", 1500);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (4, 4, "Rare Plants", 2000);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (1, 3, "Soap", 15);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (1, 1, "Towels", 10);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (3, 2, "Transformators", 500);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (1, 2, "Water", 5);
INSERT INTO commodity(type_id, manufacturer_id, name, initial_cost) VALUES (2, 1, "Weapons", 1000);

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
    1,20,1000,
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
    3,0,5000,
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
    2,2,5,1
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Arcadia",
    2,2,5,2
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Radiance",
    4,2,5,3
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Remgolia",
    5,2,5,4
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Saidai",
    1,2,4,8
);

--- Nodes 6 - 10 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Pranelius",
    1,4,2,4
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Taxopia",
    3,1,3,6
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Nadorkon",
    3,1,3,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Wunarnia",
    3,3,5,1
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Korog",
    3,1,1,10
);

--- Nodes 11 - 15 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Tau Naraka",
    4,1,1,8
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Aviz",
    4,3,2,3
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Darkumi",
    1,3,3,2
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Kuorkon",
    2,3,4,7
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Ganeaux",
    2,3,2,1
);

--- Nodes 16 - 20 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Zeta",
    5,3,1,4
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Longpid",
    5,3,5,2
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Noella",
    2,3,4,9
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Carankor",
    2,4,1,1
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Farenella",
    2,1,3,7
);

--- Nodes 21 - 25 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Paplos",
    4,1,2,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Satacan",
    5,4,4,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Vullak",
    5,4,5,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Sizeonon",
    5,4,5,2
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Scarva",
    1,1,5,2
);

--- Nodes 25 - 30 ---

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Baniru",
    4,4,5,3
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Ceti",
    4,4,1,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Nitkail",
    4,2,2,6
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Durreus",
    3,2,3,4
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Funfiner",
    3,1,5,10
);

-- Lanes 1-5 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    24,30,5,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    25,24,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    23,24,12,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    26,25,8,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    27,26,20,"TRUE"
);

-- Lanes 6-10 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    22,26,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    22,23,14,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    19,22,32,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    21,20,12,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    21,19,13,"TRUE"
);

-- Lanes 11-15 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    20,19,6,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    4,19,20,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    5,4,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    3,4,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    3,5,10,"TRUE"
);

-- Lanes 16-20 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    1,2,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    2,3,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    2,28,20,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    28,29,20,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    29,20,10,"TRUE"
);

-- Lanes 21-25 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    1,5,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    5,6,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    6,7,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    7,8,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    7,9,10,"TRUE"
);

-- Lanes 26-30 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    9,11,2,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    10,11,15,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    11,12,44,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    12,13,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    12,14,10,"TRUE"
);

-- Lanes 31-35 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    14,16,20,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    13,15,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    14,18,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    15,18,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    16,17,10,"TRUE"
);

-- Lanes 36-37 --

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    17,18,10,"TRUE"
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    18,2,10,"TRUE"
);

-- bad conditions change pref, pref = high price
-- TODO change corp affinity
INSERT INTO encounter(name, weight)
    VALUES("Pirate attack", 10);
INSERT INTO encounter(name, weight)
    VALUES("Corporation war", 10);
INSERT INTO encounter(name, weight)
    VALUES("Resource shortage", 5);
INSERT INTO encounter(name, weight)
    VALUES("Miners strike", 10);
INSERT INTO encounter(name, weight)
    VALUES("Solar blast", 1);
INSERT INTO encounter(name, weight)
    VALUES("Relay sabotage", 3);
INSERT INTO encounter(name, weight)
    VALUES("Lucky year", 3);

INSERT INTO modificator_type(name)
    VALUES("LEVELS");
INSERT INTO modificator_type(name)
    VALUES("PREFS");

--Pirate attack-1
INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    2,1,
    "Crime uprise",
    2,0,0
);

--Corporation war-2
INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    1,2,
    "Attrition",
    1,-2,-2
);

--Resource shortage-3
INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    2,3,
    "Traders pact",
    4,0,0
);

--Miners strike-4
INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    2,4,
    "Miners frenzy",
    5,0,0
);

--Solar blast-5
INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    2,5,
    "Tech outage",
    1,0,0
);

--Relay sabotage-6
INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    2,6,
    "Relay repair order",
    3,0,0
);

--Lucky year-7
INSERT INTO modificator(
    type_id, encounter_id,
    name,
    pref_id, order_delta, tech_delta
)
VALUES(
    1,7,
    "Prosperity",
    1,1,2
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