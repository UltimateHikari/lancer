INSERT INTO corporation(name) VALUES ("Giperion");

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


INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Eternity",
    2,1,2,10
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Arcadia",
    4,1,10,5
);

INSERT INTO node(
    name,
    pref_id,corp_affinity,
    order_level,tech_level
)
VALUES(
    "Radiance",
    3,1,8,8
);

INSERT INTO lane(
    start_node_id, end_node_id,
    traverse_time,initial_stability
)
VALUES(
    1,2,10,"TRUE"
);