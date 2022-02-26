--scrapped plural forms in favour of simplicity
DROP TABLE IF EXISTS corporation;
DROP TABLE IF EXISTS commodity_type;
DROP TABLE IF EXISTS commodity;

DROP TABLE IF EXISTS frame_class;
DROP TABLE IF EXISTS frame;

DROP TABLE IF EXISTS element;
DROP TABLE IF EXISTS module_type;
DROP TABLE IF EXISTS module;

--DROP TABLE IF EXISTS frame_preset;


--planetary system->node
--event->encounter
DROP TABLE IF EXISTS node;
DROP TABLE IF EXISTS lane;

--DROP TABLE IF EXISTS encounter;
--DROP TABLE IF EXISTS modificator;

--DROP TABLE IF EXISTS bots;

CREATE TABLE corporation(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE commodity_type(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE commodity(
    id integer PRIMARY KEY NOT NULL,
    type_id integer REFERENCES commodity_type(id) NOT NULL,
    manufacturer_id integer REFERENCES corporation(id) NOT NULL,
    name text NOT NULL
);

--TODO: speed/energy/slots modifiers for creation
CREATE TABLE frame_class(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE frame(
    id integer PRIMARY KEY NOT NULL,
    class_id integer REFERENCES frame_class(id) NOT NULL,
    manufacturer_id integer REFERENCES corporation(id) NOT NULL,
    name text NOT NULL,

    weap_slots integer NOT NULL,
    armr_slots integer NOT NULL,
    supp_slots integer NOT NULL,

    energy integer NOT NULL,
    inventory_size integer NOT NULL,

    structure_points integer NOT NULL,
    speed integer NOT NULL,
    evasion integer NOT NULL
);

CREATE TABLE module_type(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE element(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL
);

CREATE TABLE module(
    id integer PRIMARY KEY NOT NULL,
    type_id integer REFERENCES module_type(id) NOT NULL,
    manufacturer_id integer REFERENCES corporation(id) NOT NULL,
    name text NOT NULL,
    element_id integer REFERENCES element(id) NOT NULL,
    energy_cost integer NOT NULL,
    initial_cost integer NOT NULL,

    damage integer NOT NULL,
    accuracy integer NOT NULL,
    cooldown integer NOT NULL,

    structure_points integer NOT NULL,

    speed_modifier integer NOT NULL,
    evasion_modifier integer NOT NULL,
    energy_modifier integer NOT NULL,
    inventory_modifier integer NOT NULL,
    drill_profit_modifier integer NOT NULL
);

CREATE TABLE node(
    id integer PRIMARY KEY NOT NULL,
    name text NOT NULL,

    pref_id integer REFERENCES commodity_type(id) NOT NULL,
    corp_affinity integer REFERENCES corporation(id) NOT NULL,
    order_level integer NOT NULL,
    tech_level integer NOT NULL
);

CREATE TABLE lane(
    id integer PRIMARY KEY NOT NULL,
    start_node_id integer NOT NULL,
    end_node_id integer NOT NULL,
    traverse_time integer NOT NULL,
    initial_stability boolean NOT NULL
);